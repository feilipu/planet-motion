/*
 * planet_motion.c
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
 
/*

    build with:

    zcc +rc2014 -subtype=cpm -clib=new -v -m --list -O2 --opt-code-speed=all -lm -llib/rc2014/regis @planet_motion.lst -o motion_new -create-app

    zcc +rc2014 -subtype=cpm -v -m --list -lm -llib/rc2014/regis --max-allocs-per-node100000 @planet_motion.lst -o motion_48 -create-app
    zcc +rc2014 -subtype=cpm -v -m --list --math32 -llib/rc2014/regis --max-allocs-per-node100000 @planet_motion.lst -o motion_32 -create-app

    zcc +rc2014 -subtype=cpm -v -m --list --am9511 -llib/rc2014/regis --max-allocs-per-node100000 @planet_motion.lst -o motion_apu -create-app

 */

/*
    zcc +yaz180 -subtype=cpm -v -m --list --math32 -llib/yaz180/regis --max-allocs-per-node100000 @planet_motion.lst -o motion_32 -create-app
 */

/*
    zcc +cpm -clib=sdcc_iy -v -m --list -lm -llib/cpm/regis --max-allocs-per-node100000 @planet_motion.lst -o motion_48 -create-app
    zcc +cpm -clib=sdcc_iy -v -m --list --math32 -llib/cpm/regis --max-allocs-per-node100000 @planet_motion.lst -o motion_32 -create-app

    zcc +cpm -clib=new -v -m --list -O2 --opt-code-speed=all --math32 -llib/cpm/regis @planet_motion.lst -o motion_new -create-app

    zcc +cpm -clib=sdcc_iy -v -m --list --am9511 -llib/cpm/regis --max-allocs-per-node100000 @planet_motion.lst -o motion_apu -create-app

    zcc +cpm -clib=8085 -v -m --list -O2 -DAMALLOC --am9511 -l../../libsrc/_DEVELOPMENT/lib/sccz80/lib/cpm/regis_8085 @planet_motion.lst -o motion85 -create-app
 */

#include <stdint.h>
#include <stdio.h>
#include <math.h>

#if __8085
#include <_DEVELOPMENT/sccz80/lib/cpm/regis.h>
#elif __RC2014
#include <lib/rc2014/regis.h>
#elif __YAZ180
#include <lib/yaz180/regis.h>
#elif __CPM
#include <lib/cpm/regis.h>
#endif

#include "planet_motion.h"
#include "multi_apu.h"

#pragma printf = "%s %c %u %0d"     // enables %s, %c, %u, %d (formatted) only

#define SCALE_AU            48

// planetary constants

const planet_t sun =      { "Sun", \
                            0.0, 0.0, \
                            0.0, 0.0, \
                            282.9404, 4.70935E-5, \
                            1.0, 0.0, \
                            0.016709, -1.151E-9, \
                            356.0470, 0.9856002585, \
                            (695500/6378) };

const planet_t moon =     { "Moon", \
                            125.1228, -0.0529538083, \
                            5.1454, 0.0, \
                            318.0634, 0.1643573223, \
                            60.2666/EARTH_RADII_PER_ASTRONOMICAL_UNIT, 0.0, \
                            0.054900, 0.0, \
                            115.3654, 13.0649929509, \
                            (1738/6378) };

const planet_t mercury =  { "Mercury", \
                            48.3313, 3.24587e-5, \
                            7.0047, 5.0e-8, \
                            29.1241, 1.01444e-5, \
                            0.387098, 0.0, \
                            0.205635, 5.59e-10, \
                            168.6562, 4.0923344368, \
                            (2440/6378) };

const planet_t venus =    { "Venus", \
                            76.6799, 2.46590e-5, \
                            3.3946, 2.75e-8, \
                            54.8910, 1.38374e-5, \
                            0.723330, 0.0, \
                            0.006773, -1.302e-9, \
                            48.0052, 1.6021302244, \
                            (6052/6378) };

const planet_t mars =     { "Mars", \
                            49.5574, 2.11081e-5, \
                            1.8497, -1.78e-8, \
                            286.5016, 2.92961e-5, \
                            1.523688, 0.0, \
                            0.093405, 2.516e-9, \
                            18.6021, 0.5240207766, \
                            (3390/6378) };

const planet_t jupiter =  { "Jupiter", \
                            100.4542, 2.76854E-5, \
                            1.3030, - 1.557E-7, \
                            273.8777, 1.64505E-5, \
                            5.20256, 0.0, \
                            0.048498, 4.469E-9, \
                            19.8950, 0.0830853001, \
                            (69911/6378) };

const planet_t saturn =   { "Saturn", \
                            113.6634, 2.3898e-5, \
                            2.4886, -1.081e-7, \
                            339.3939, 2.97661e-5, \
                            9.55475, 0.0, \
                            0.055546, -9.499e-9, \
                            316.9670, 0.0334442282, \
                            (58232/6378) };

const planet_t uranus =   { "Uranus", \
                            74.0005, 1.3978E-5, \
                            0.7733, 1.9E-8, \
                            96.6612, 3.0565E-5, \
                            19.18171, - 1.55E-8, \
                            0.047318, 7.45E-9, \
                            142.5905, 0.011725806, \
                            (25362/6378) };

const planet_t neptune =  { "Neptune", \
                            131.7806, 3.0173e-5, \
                            1.7700, -2.55e-7, \
                            272.8461, -6.027e-6, \
                            30.05826, 3.313e-8, \
                            0.008606, 2.15e-9, \
                            260.2471, 0.005995147, \
                            (24622/6378) };


window_t mywindow;

cartesian_coordinates_t theSun, thePlanet;

int main()
{
    uint16_t d;
    uint16_t sun_x;
    uint16_t sun_y;
    char s[10];

    for (d = 8766; d < (8766+(1*365)+1); ++d)                                       // January 1st, 2024 + 1 year
//  for (d = 8766; d < (8766+20); ++d)                                               // January 1st, 2024 + 20 days
    {
        window_new( &mywindow, 768, 480, stdout);                                   // open command list
        window_clear( &mywindow );

        theSun.day = (float)d;

        sunEclipticCartesianCoordinates ( &theSun);

        sun_x = 384+(int16_t)(theSun.x*SCALE_AU);
        sun_y = 240-(int16_t)(theSun.y*SCALE_AU);

        draw_abs( &mywindow, 384, 240 );
        draw_intensity( &mywindow, _B );
        draw_circle_fill( &mywindow, 8 );                                           // draw earth

        draw_intensity( &mywindow, _Y );
        draw_circle( &mywindow, (uint16_t)(theSun.au*SCALE_AU) );                   // draw sun orbit around earth

        draw_abs( &mywindow, sun_x, sun_y );
        draw_circle_fill( &mywindow, 18 );                                          // draw sun

        thePlanet.day = d;
        planetEclipticCartesianCoordinates( &thePlanet, &moon );

        draw_abs( &mywindow, 384, 240 );
        draw_intensity( &mywindow, _W );
        draw_circle( &mywindow, (uint16_t)(thePlanet.au*(100*SCALE_AU)) );          // draw moon orbit

        draw_abs( &mywindow, 384+(int16_t)(thePlanet.x*(100*SCALE_AU)), 240-(int16_t)(thePlanet.y*(100*SCALE_AU)) );
        draw_circle_fill( &mywindow, 3 );                                           // draw moon

        planetEclipticCartesianCoordinates( &thePlanet, &mercury );
        addCartesianCoordinates( &thePlanet, &theSun );

        draw_abs( &mywindow, sun_x, sun_y );
        draw_intensity( &mywindow, _R );
        draw_circle( &mywindow, (uint16_t)(thePlanet.au*SCALE_AU) );                // draw mercury orbit

        draw_abs( &mywindow, 384+(int16_t)(thePlanet.x*SCALE_AU), 240-(int16_t)(thePlanet.y*SCALE_AU) );
        draw_circle_fill( &mywindow, 4 );                                           // draw mercury

        planetEclipticCartesianCoordinates( &thePlanet, &venus );
        addCartesianCoordinates( &thePlanet, &theSun );

        draw_abs( &mywindow, sun_x, sun_y );
        draw_intensity( &mywindow, _C );
        draw_circle( &mywindow, (uint16_t)(thePlanet.au*SCALE_AU) );                // draw venus orbit

        draw_abs( &mywindow, 384+(int16_t)(thePlanet.x*SCALE_AU), 240-(int16_t)(thePlanet.y*SCALE_AU) );
        draw_circle_fill( &mywindow, 8 );                                           // draw venus

        planetEclipticCartesianCoordinates( &thePlanet, &mars );
        addCartesianCoordinates( &thePlanet, &theSun );

        draw_abs( &mywindow, sun_x, sun_y );
        draw_intensity( &mywindow, _R );
        draw_circle( &mywindow, (uint16_t)(thePlanet.au*SCALE_AU) );                // draw mars orbit

        draw_abs( &mywindow, 384+(int16_t)(thePlanet.x*SCALE_AU), 240-(int16_t)(thePlanet.y*SCALE_AU) );
        draw_circle_fill( &mywindow, 6 );                                           // draw mars

        planetEclipticCartesianCoordinates( &thePlanet, &jupiter );
        addCartesianCoordinates( &thePlanet, &theSun );

        draw_abs( &mywindow, sun_x, sun_y );
        draw_intensity( &mywindow, _C );
        draw_circle( &mywindow, (uint16_t)(thePlanet.au*SCALE_AU) );                // draw jupiter orbit

        draw_abs( &mywindow, 384+(int16_t)(thePlanet.x*SCALE_AU), 240-(int16_t)(thePlanet.y*SCALE_AU) );
        draw_circle_fill( &mywindow, 16 );                                          // draw jupiter

        planetEclipticCartesianCoordinates( &thePlanet, &saturn );
        addCartesianCoordinates( &thePlanet, &theSun );

        draw_abs( &mywindow, sun_x, sun_y );
        draw_intensity( &mywindow, _W );
        draw_circle( &mywindow, (uint16_t)(thePlanet.au*SCALE_AU) );                // draw saturn orbit

        draw_abs( &mywindow, 384+(int16_t)(thePlanet.x*SCALE_AU), 240-(int16_t)(thePlanet.y*SCALE_AU) );
        draw_circle_fill( &mywindow, 12 );                                          // draw saturn
        draw_circle( &mywindow, 14 );                                               // draw saturn's rings
        draw_circle( &mywindow, 16 );
        draw_circle( &mywindow, 18 );

        sprintf(s, "Day: %.4d", d);
        draw_abs( &mywindow, 10, 450 );
        draw_text( &mywindow, s, 2);                                                // draw date

        window_close( &mywindow );                                                  // close window command list
    }

    return 0;
}
