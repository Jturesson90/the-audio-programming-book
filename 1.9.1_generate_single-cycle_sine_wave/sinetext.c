/* sinetext.c */
/* write sinewave as text */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#ifndef M_PI
#define M_PI (3.141592654)
#endif

int main(int argc, char const *argv[])
{
    int nsamps = 50;
    double samp;
    double twopi = 2.0 * M_PI;
    double angleincr = twopi / nsamps;
    for (size_t i = 0; i < nsamps; i++)
    {
        samp = sin(angleincr * i);
        fprintf(stdout, "%.8lf\n", samp);
    }
    fprintf(stderr, "done\n");

    return 0;
}
