
#include <stdint.h>
#include <math.h>

#include "planet_motion.h"

void sunEclipticCartesianCoordinates ( cartesian_coordinates_t * sun) __z88dk_fastcall
{
    // We use formulas for finding the Sun as seen from Earth, 
    // then negate the (x,y,z) coordinates obtained to get the Earth's position 
    // from the Sun's perspective.

    // http://www.astro.uio.no/~bgranslo/aares/calculate.html
    // http://www.meteorobs.org/maillist/msg09197.html              <== Correct formulas, more accurate (complex)

    // These formulas use 'd' based on days since 1/Jan/2000 12:00 UTC ("J2000.0"), instead of 0/Jan/2000 0:00 UTC ("day value").
    // Correct by subtracting 1.5 days...
    FLOAT T = (sun->day - 1.5) * 0.0000273785;                      // 36525.0 Julian centuries since J2000.0

    FLOAT T_SQR = SQR(T);

    FLOAT L0 = rev(280.46645 + (36000.76983 * T) + (0.0003032 * T_SQR));                            // Sun's mean longitude, in degrees
    FLOAT M0 = rev(357.52910 + (35999.05030 * T) - (0.0001559 * T_SQR) - (0.00000048 * T * T_SQR));     // Sun's mean anomaly, in degrees

                                                                    // Sun's equation of center in degrees
    FLOAT C = rev((1.914600 - 0.004817 * T - 0.000014 * T_SQR) * SIN(RAD(M0)) + (0.01993 - 0.000101 * T) * SIN(RAD(2*M0)) + 0.000290 * SIN(RAD(3*M0)));

    FLOAT LS = rev(L0 + C);                                         // true ecliptical longitude of Sun

    FLOAT e = 0.016708617 - T * (0.000042037 + T * 0.0000001236);   // The eccentricity of the Earth's orbit.
    FLOAT distanceInAU = (1.000001018 * (1 - SQR(e))) / (1 + e * COS(RAD(M0 + C))); // distance from Sun to Earth in astronomical units (AU)
    sun->x = distanceInAU * COS(RAD(LS));
    sun->y = distanceInAU * SIN(RAD(LS));
    sun->z = 0.0;                                                   // the Earth's center is always on the plane of the ecliptic (z=0), by definition!

    sun->au = distanceInAU;
}


void planetEclipticCartesianCoordinates ( cartesian_coordinates_t * location, const planet_t * planet ) __z88dk_callee
{
    FLOAT day = location->day;

    FLOAT N = rev( planet->N0 + (day * planet->Nc) );
    FLOAT i = rev( planet->i0 + (day * planet->ic) );
    FLOAT w = rev( planet->w0 + (day * planet->wc) );
    FLOAT a = rev( planet->a0 + (day * planet->ac) );

    FLOAT e = rev( planet->e0 + (day * planet->ec) );
    FLOAT M = rev( planet->M0 + (day * planet->Mc) );

    FLOAT E = rev(eccentricAnomaly (e, M));

    // Calculate the body's position in its own orbital plane, and its distance from the thing it is orbiting.
    FLOAT xv = a * (COS(RAD(E)) - e);
    FLOAT yv = a * SQRT(1.0 - SQR(e)) * SIN(RAD(E));

    FLOAT v = DEG(ATAN2(yv, xv));       // True anomaly in degrees: the angle from perihelion of the body as seen by the Sun.
    FLOAT r = HYPOT(xv, yv);            // Distance from the Sun to the planet in AU

    FLOAT cosN  = COS(RAD(N));
    FLOAT sinN  = SIN(RAD(N));
    FLOAT cosi  = COS(RAD(i));
    FLOAT sini  = SIN(RAD(i));
    FLOAT cosVW = COS(RAD(v+w));
    FLOAT sinVW = SIN(RAD(v+w));

    // Now we are ready to calculate (unperturbed) ecliptic cartesian heliocentric coordinates.
    location->x = r * (cosN*cosVW - sinN*sinVW*cosi);
    location->y = r * (sinN*cosVW + cosN*sinVW*cosi);
    location->z = r * sinVW * sini;

    // save the radius from the sun in AU
    location->au = r;
}


FLOAT eccentricAnomaly (FLOAT e, FLOAT M) __z88dk_callee
{
    FLOAT E, error;

    E = M + (e * SIN(RAD(M)) * (1.0 + (e * COS(RAD(M)))));

    do {
        error = (E - DEG(e * SIN(RAD(E))) - M) / (1 - e * COS(RAD(E)));
        E -= error;
        error = FABS(error);
    } while (error >= 1.0e-3);          // the angle is good enough for our purposes

    return E;
}

void addCartesianCoordinates ( cartesian_coordinates_t * base, const cartesian_coordinates_t * addend ) __z88dk_callee
{
    base->x += addend->x;
    base->y += addend->y;
    base->z += addend->z;
}

#if ! defined(__MATH_MATH32) && ! defined(__MATH_AM9511)
FLOAT rev (FLOAT x) __z88dk_fastcall
{
    return x - FLOOR(x*(1/360.0))*360.0;
}
#endif

