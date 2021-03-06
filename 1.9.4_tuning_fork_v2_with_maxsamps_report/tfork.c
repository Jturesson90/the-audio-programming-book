/* tfork.c virtual tuning fork comingin sinetext.c and expdecay.c */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#ifndef M_PI
#define M_PI (3.141592654)
#endif

enum
{
    ARG_NAME,
    ARG_OUTFILE,
    ARG_DUR,
    ARG_HZ,
    ARG_SR,
    ARG_AMP,
    ARG_NARGS
};
int main(int argc, char const *argv[])
{
    int i, sr, nsamps;
    double samp, dur, freq, srate, amp, maxsamp;
    double start, end, fac, angleincr;
    double twopi = 2.0 * M_PI;
    FILE *fp = NULL;

    if (argc != ARG_NARGS)
    {
        printf("Usage: tfork outfile.txt dur freq srate amp\n");
        return 1;
    }
    fp = fopen(argv[ARG_OUTFILE], "w");
    if (fp == NULL)
    {
        fprintf(stderr, "Error creating output file %s\n", argv[ARG_OUTFILE]);
        return 1;
    }

    dur = atof(argv[ARG_DUR]);
    freq = atof(argv[ARG_HZ]);
    srate = atof(argv[ARG_SR]);
    amp = atof(argv[ARG_AMP]);
    nsamps = (int)(dur * srate);
    angleincr = twopi * freq / srate;

    start = 1.0;
    end = 1.0e-4; /* = -80dB */
    maxsamp = 1.0;
    fac = pow(end / start, 1.0 / nsamps);

    for (i = 0; i < nsamps; i++)
    {
        samp = amp * sin(angleincr * i);
        samp *= start;
        start *= fac;
        fprintf(fp, "%.8lf\n", samp);
        if (fabs(samp) > maxsamp)
        {
            maxsamp = fabs(samp);
        }
    }
    fclose(fp);
    printf("done. Maximum sample value = %.8lf\n", maxsamp);

    return 0;
}
