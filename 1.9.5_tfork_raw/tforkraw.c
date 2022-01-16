/* tforkraw.c gen raw sound file with native endianness */
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
    ARG_MIDINOTE,
    ARG_SR,
    ARG_AMP,
    ARG_TYPE,
    ARG_NARGS
};
enum samptype
{
    RAWSAMP_SHORT,
    RAWSAMP_FLOAT
};
int byte_order()
{
    unsigned int i = 1;
    char *c = (char *)&i;
    if (*c)
        return 1;
    else
        return 0;
}
const char *endianness[2] = {"big_endian", "little_endian"};

int main(int argc, char const *argv[])
{
    unsigned int i, nsamps;
    unsigned int maxframe = 0;
    unsigned int samptype, endian, bitreverse;
    double samp, dur, freq, srate, amp, step;
    double start, end, fac, maxsamp;
    double twopi = 2.0 * M_PI;
    double angleincr;
    FILE *fp = NULL;
    float fsamp;
    short ssamp;
    double c5, c0;
    int midinote;

    if (argc != ARG_NARGS)
    {
        printf("Usage: tforkraw outfile.raw dur midinote srate amp isfloat\n");
        return 1;
    }

    dur = atof(argv[ARG_DUR]);
    midinote = atoi(argv[ARG_MIDINOTE]);
    srate = atof(argv[ARG_SR]);
    amp = atof(argv[ARG_AMP]);
    samptype = (unsigned int)atoi(argv[ARG_TYPE]);

    double semitone_ratio = pow(2, 1 / 12.0);
    c5 = 220.0 * pow(semitone_ratio, 3);
    c0 = c5 * pow(0.5, 5);
    freq = c0 * pow(semitone_ratio, midinote);

    if (!(samptype == 1 || samptype == 0))
    {
        printf("error: sampletype can be only 1 or 0\n");
        return 1;
    }
    fp = fopen(argv[ARG_OUTFILE], "wb");
    if (fp == NULL)
    {
        fprintf(stderr, "Error creating output file %s\n", argv[ARG_OUTFILE]);
        return 1;
    }

    nsamps = (int)(dur * srate);
    angleincr = twopi * freq / nsamps;
    step = dur / nsamps;
    start = 1.0;
    end = 1.0e-4; /* = -80dB */
    maxsamp = 0.0;
    fac = pow(end / start, 1.0 / nsamps);
    endian = byte_order();
    printf("Writing %d %s samples\n", nsamps, endianness[endian]);
    for (i = 0; i < nsamps; i++)
    {
        samp = amp * sin(angleincr * i);
        samp *= start;
        start *= fac;
        if (samptype == RAWSAMP_SHORT)
        {
            ssamp = (short)(samp * 32767.0);
            if (fwrite(&ssamp, sizeof(short), 1, fp) != 1)
            {
                printf("Error writing data to file\n");
                return 1;
            }
        }
        else
        {
            fsamp = (float)samp;
            if (fwrite(&fsamp, sizeof(short), 1, fp) != 1)
            {
                printf("Error writing data to file\n");
                return 1;
            }
        }
        if (fabs(samp) > maxsamp)
        {
            maxsamp = fabs(samp);
            maxframe = i;
        }
    }
    fclose(fp);
    printf("done. Maximum sample value = %.8lf\n", maxsamp);

    return 0;
}
