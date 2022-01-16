/* sinetext.c */
/* write sinewave as text */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#ifndef M_PI
#define M_PI (3.141592654)
#endif
enum
{
    ARG_NAME,
    ARG_NSAMPS,
    ARG_FREQ,
    ARG_SAMPLERATE,
    ARG_NARGS
};
int main(int argc, char const *argv[])
{

    double samp;
    double twopi = 2.0 * M_PI;

    if (argc != ARG_NARGS)
    {
        fprintf(stderr, "Usage: sinetext nsamps freq srate\n");
        return 1;
    }
    int nsamps = atoi(argv[ARG_NSAMPS]);
    double freq = atof(argv[ARG_FREQ]);
    double srate = atof(argv[ARG_SAMPLERATE]);

    double angleincr = twopi * freq / srate;
    for (size_t i = 0; i < nsamps; i++)
    {
        samp = sin(angleincr * i);
        fprintf(stdout, "%.8lf\n", samp);
    }
    
    fprintf(stderr, "done\n");

    return 0;
}
