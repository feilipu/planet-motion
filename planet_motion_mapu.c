
#include <stdint.h>
#include <math.h>

#include "planets.h"
#include "multi_apu.h"

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
    //FLOAT C = rev((1.914600 - 0.004817 * T - 0.000014 * T_SQR) * SIN(RAD(M0)) + (0.01993 - 0.000101 * T) * SIN(RAD(2*M0)) + 0.000290 * SIN(RAD(3*M0)));

    rad_1(M0);
    rad_2(M0);
    rad_3(M0);

    sin_1();
    mul_2(2);
    mul_3(3);

    sin_2();
    sin_3();

    FLOAT C = rev((1.914600 - 0.004817 * T - 0.000014 * T_SQR) * pop_1() + (0.01993 - 0.000101 * T) * pop_2() + 0.000290 * pop_3());

    push_1(M0);
    add_1(C);

    FLOAT LS = rev(L0 + C);                                         // true ecliptical longitude of Sun

    mul_1(M_PI/180.0);

    FLOAT e = 0.016708617 - T * (0.000042037 + T * 0.0000001236);   // The eccentricity of the Earth's orbit.

    cos_1();

    FLOAT distanceInAU = (1.000001018 * (1 - SQR(e))) / (1 + e * pop_1()); // distance from Sun to Earth in astronomical units (AU)

    rad_0(LS);
    rad_1(LS);
    cos_0();
    sin_1();
    mul_0(distanceInAU);
    mul_1(distanceInAU);
    
    sun->x = pop_0();
    sun->y = pop_1();
    sun->z = 0.0;                                                   // the Earth's center is always on the plane of the ecliptic (z=0), by definition!
}


void planetEclipticCartesianCoordinates ( cartesian_coordinates_t * location, const planet_t * planet ) __z88dk_callee
{
    FLOAT day = location->day;

    push_0(day);
    push_1(day);
    push_2(day);
    push_3(day);

    mul_0(planet->Nc);
    mul_1(planet->ic);
    mul_2(planet->ec);
    mul_3(planet->Mc);

    add_0(planet->N0);
    add_1(planet->i0);
    add_2(planet->e0);
    add_3(planet->M0);

    FLOAT N = pop_0();
    FLOAT i = pop_1();
    FLOAT e = pop_2();
    FLOAT M = pop_3();

    push_2(day);
    push_3(day);

    mul_2(planet->wc);
    mul_3(planet->ac);

    N = rev( N );

    add_2(planet->w0);
    add_3(planet->a0);

    FLOAT w = pop_2();
    FLOAT a = pop_3();

    rad_2(N);
    rad_3(N);
    cos_2();
    sin_3();

    i = rev( i );

    rad_0(i);
    rad_1(i);
    cos_0();
    sin_1();

    FLOAT cosN = pop_2();
    FLOAT sinN = pop_3();

    FLOAT cosi = pop_0();
    FLOAT sini = pop_1();

    e = rev(e);
    M = rev(M);

    FLOAT E = eccentricAnomaly (e, M);

    // Calculate the body's position in its own orbital plane, and its distance from the thing it is orbiting
    rad_2(E);
    rad_3(E);
    cos_2();
    sin_3();

    mul_3(SQRT(1.0 - SQR(e)));          // use 0 for math while 2 & 3 are doing trigonometry
    add_2(-e);
    mul_3(a);
    mul_2(a);

    FLOAT yv = pop_3();
    FLOAT xv = pop_2();

    FLOAT v = DEG(ATAN2(yv, xv));       // True anomaly in degrees: the angle from perihelion of the body as seen by the Sun

    rad_2(v+w);
    rad_3(v+w);
    cos_2();
    sin_3();

    FLOAT r = HYPOT(xv, yv);            // Distance from the Sun to the planet in AU.

    FLOAT cosVW = pop_2();
    FLOAT sinVW = pop_3();

    // Now we are ready to calculate (unperturbed) ecliptic cartesian heliocentric coordinates
    push_0(cosN); 
    push_3(cosN); 
    push_1(sinN);
    push_2(-sinN);

    mul_0(cosVW);
    mul_1(cosVW);
    mul_2(sinVW);
    mul_3(sinVW);

    FLOAT cosNcosVW = pop_0();
    FLOAT sinNcosVW = pop_1();

    push_1(sinVW);

    mul_2(cosi);
    mul_3(cosi);

    mul_1(sini);

    add_2(cosNcosVW);
    add_3(sinNcosVW);

    mul_1(r);
    mul_2(r);
    mul_3(r);

    location->z = pop_1();
    location->x = pop_2();
    location->y = pop_3();
}


FLOAT eccentricAnomaly (FLOAT e, FLOAT M) __z88dk_callee
{
    FLOAT E, error;

    rad_0(M);
    rad_1(M);

    cos_0();
    sin_1();

    mul_0(e);
    mul_1(e);

    add_0(1.0);
    mul_0(pop_1());
    add_0(M);
    E = pop_0();

    // E = M + (e * SIN(RAD(M)) * (1.0 + (e * COS(RAD(M)))));

    do {
        rad_0(E);
        rad_1(E);

        cos_0();
        sin_1();

        mul_0(e);
        mul_1(e);

        push_2(E);
        push_3(1);

        deg_1();

        add_3(-pop_0());
        add_2(-pop_1());

        add_2(-M);
        div_2(pop_3());

        error = pop_2();
        E -= error;
        error = FABS(error);

    } while (error >= 1.0e-3);          // the angle is good enough for our purposes

    return E;
}


void addCartesianCoordinates ( cartesian_coordinates_t * base, const cartesian_coordinates_t * addend ) __z88dk_callee
{
    push_0(base->x);
    push_1(base->y);
    push_2(base->z);
    add_0(addend->x);
    add_1(addend->y);
    add_2(addend->z);
    base->x = pop_0();
    base->y = pop_1();
    base->z = pop_2();
}

