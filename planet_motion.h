/*
 * planet_motion.h
 *
 * Copyright (c) 2021 Phillip Stevens
 * Create Time: July 2021
 *
 * The MIT License (MIT)
 *
 * Permission is hereby granted,free of charge,to any person obtaining a copy
 * of this software and associated documentation files (the "Software"),to deal
 * in the Software without restriction,including without limitation the rights
 * to use,copy,modify,merge,publish,distribute,sublicense,and/or sell
 * copies of the Software,and to permit persons to whom the Software is
 * furnished to do so,subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS",WITHOUT WARRANTY OF ANY KIND,EXPRESS OR
 * IMPLIED,INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,DAMAGES OR OTHER
 * LIABILITY,WHETHER IN AN ACTION OF CONTRACT,TORT OR OTHERWISE,ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */
 

#ifndef _PLANET_MOTION_H
#define _PLANET_MOTION_H

#ifdef __cplusplus
extern "C" {
#endif

// numeric constants...

#define METERS_PER_ASTRONOMICAL_UNIT        1.4959787e+11
#define METERS_PER_EARTH_EQUATORIAL_RADIUS  6378160.0
#define EARTH_RADII_PER_ASTRONOMICAL_UNIT   (METERS_PER_ASTRONOMICAL_UNIT/METERS_PER_EARTH_EQUATORIAL_RADIUS)

// macros

#define FLOAT       float_t

#define FABS        fabs
#define FLOOR       floor

#define SQRT        sqrt
#define HYPOT       hypot

#define COS         cos
#define SIN         sin
#define TAN         tan
#define ACOS        acos
#define ASIN        asin
#define ATAN        atan
#define ATAN2       atan2

#if defined(__MATH_MATH32)
    #define SQR(x)  sqr(x)
#else
    #define SQR(x)  ((x)*(x))
#endif

#define RAD(x)      ((x)*(M_PI/180.0))
#define DEG(x)      ((x)*(180.0/M_PI))

// type definitions

typedef struct cartesian_coordinates_s {
    FLOAT x;
    FLOAT y;
    FLOAT z;
    FLOAT au;               // radius in AU
    FLOAT day;
} cartesian_coordinates_t;

typedef struct planet_s {
    char * name;            // name of the object, e.g. "Mars".
    FLOAT N0, Nc;           // N0 = longitude of the ascending node (deg).  Nc = rate of change in deg/day.
    FLOAT i0, ic;           // inclination to the ecliptic (deg).
    FLOAT w0, wc;           // argument of perihelion (deg).
    FLOAT a0, ac;           // semi-major axis, or mean distance from Sun (AU).
    FLOAT e0, ec;           // eccentricity (0=circle, 0..1=ellipse, 1=parabola).
    FLOAT M0, Mc;           // M0 = mean anomaly (deg) (0 at perihelion; increases uniformly with time).  Mc ("mean motion") = rate of change in deg/day = 360/period.
    FLOAT radius;           // radius proportional to earth's radius (earth = 1.0)
} planet_t;

// utility functions (C)

void sunEclipticCartesianCoordinates ( cartesian_coordinates_t * sun ) __z88dk_fastcall;
void planetEclipticCartesianCoordinates ( cartesian_coordinates_t * location, const planet_t * planet ) __z88dk_callee;
FLOAT eccentricAnomaly (FLOAT e, FLOAT M) __z88dk_callee;
void addCartesianCoordinates ( cartesian_coordinates_t * base, const cartesian_coordinates_t * addend ) __z88dk_callee;

// utility functions (C or assembly)

FLOAT rev (FLOAT x) __z88dk_fastcall;

#ifdef __cplusplus
}
#endif

#endif  /* _PLANET_MOTION_H  */

