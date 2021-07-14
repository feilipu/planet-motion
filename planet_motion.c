/*

    build with:

    zcc +rc2014 -subtype=cpm -clib=new -v -m --list -O2 -lm -llib/rc2014/regis @planet_motion.lst -o motionnew_cpm -create-app

    zcc +rc2014 -subtype=cpm -v -m --list  -lm -llib/rc2014/regis --max-allocs-per-node100000 @planet_motion.lst -o motion48_cpm -create-app
    zcc +rc2014 -subtype=cpm -v -m --list --math32 -llib/rc2014/regis --max-allocs-per-node100000 @planet_motion.lst -o motion32_cpm -create-app

    zcc +rc2014 -subtype=cpm -v -m --list --am9511 -llib/rc2014/regis --max-allocs-per-node100000 @planet_motion.lst -o motionapu_cpm -create-app

*/


#include <stdint.h>
#include <stdio.h>
#include <math.h>
#include <z80.h>

#include <lib/rc2014/regis.h>

#include "planet_motion.h"
#include "multi_apu.h"

// pragmas

#pragma printf = "%s %c %d %f"     // enables %s, %c, %d, %f only

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
    FLOAT d;
    FLOAT sun_x;
    FLOAT sun_y;

    for (d = 7865.0; d < (7865.0+(2*365.25)); d+=1.0)
    {
        window_new( &mywindow, 768, 480 );

        theSun.day = d;

        sunEclipticCartesianCoordinates ( &theSun);

        sun_x = 384+(int16_t)(theSun.x*48);
        sun_y = 240+(int16_t)(theSun.y*48);

        draw_abs( &mywindow, 384, 240 );                                                        // draw earth
        draw_intensity( &mywindow, B );
        draw_circle_fill( &mywindow, 8 );

        draw_intensity( &mywindow, Y );                                                         // draw sun orbit around earth
        draw_circle( &mywindow, (uint16_t)(theSun.au*48) );

        draw_abs( &mywindow, sun_x, sun_y );                                                    // draw sun
        draw_circle_fill( &mywindow, 20 );

        thePlanet.day = d;
        planetEclipticCartesianCoordinates( &thePlanet, &moon );

        draw_abs( &mywindow, 384, 240 );;                                                       // draw moon orbit
        draw_intensity( &mywindow, W );
        draw_circle( &mywindow, (uint16_t)(thePlanet.au*4800) );

        draw_abs( &mywindow, 384+(int16_t)(thePlanet.x*4800), 240+(int16_t)(thePlanet.y*4800) );// draw moon
        draw_circle_fill( &mywindow, 3 );

        planetEclipticCartesianCoordinates( &thePlanet, &mercury );
        addCartesianCoordinates( &thePlanet, &theSun );

        draw_abs( &mywindow, sun_x, sun_y );                                                    // draw mercury orbit
        draw_intensity( &mywindow, R );
        draw_circle( &mywindow, (uint16_t)(thePlanet.au*48) );

        draw_abs( &mywindow, 384+(int16_t)(thePlanet.x*48), 240+(int16_t)(thePlanet.y*48) );    // draw mercury
        draw_circle_fill( &mywindow, 4 );

        planetEclipticCartesianCoordinates( &thePlanet, &venus );
        addCartesianCoordinates( &thePlanet, &theSun );

        draw_abs( &mywindow, sun_x, sun_y );                                                    // draw venus orbit
        draw_intensity( &mywindow, C );
        draw_circle( &mywindow, (uint16_t)(thePlanet.au*48) );

        draw_abs( &mywindow, 384+(int16_t)(thePlanet.x*48), 240+(int16_t)(thePlanet.y*48) );    // draw venus
        draw_circle_fill( &mywindow, 8 );

        planetEclipticCartesianCoordinates( &thePlanet, &mars );
        addCartesianCoordinates( &thePlanet, &theSun );

        draw_abs( &mywindow, sun_x, sun_y );                                                    // draw mars orbit
        draw_intensity( &mywindow, R );
        draw_circle( &mywindow, (uint16_t)(thePlanet.au*48) );

        draw_abs( &mywindow, 384+(int16_t)(thePlanet.x*48), 240+(int16_t)(thePlanet.y*48) );    // draw mars
        draw_circle_fill( &mywindow, 6 );

        planetEclipticCartesianCoordinates( &thePlanet, &jupiter );
        addCartesianCoordinates( &thePlanet, &theSun );

        draw_abs( &mywindow, sun_x, sun_y );                                                    // draw jupiter orbit
        draw_intensity( &mywindow, Y );
        draw_circle( &mywindow, (uint16_t)(thePlanet.au*48) );

        draw_abs( &mywindow, 384+(int16_t)(thePlanet.x*48), 240+(int16_t)(thePlanet.y*48) );    // draw jupiter
        draw_circle_fill( &mywindow, 24 );

        window_write( &mywindow );              // write out window to screen
        window_close( &mywindow );              // close command list
    }
    return 0;
}

