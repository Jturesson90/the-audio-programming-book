/* main.c : extract amplitude envelope from mono soundfile */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <portsf.h>

/* set size of multi-channel frame-buffer */
#define NFRAMES (1024)
#define DEFAULT_WINDOW_MSECS (15)
/* TODO define program argument list, excluding flags */
enum
{
    ARG_PROGNAME,
    ARG_INFILE,
    ARG_OUTFILE,
    ARG_NARGS
};
double maxsamp(const float *buf, unsigned long blocksize);

double maxsamp(const float *buf, unsigned long blocksize)
{
    double absval, peak = 0.0;
    unsigned long i;

    for (i = 0; i < blocksize; i++)
    {
        absval = fabs(buf[i]);
        if (absval > peak)
            peak = absval;
    }
    return peak;
}
int main(int argc, char *argv[])
{
    /* STAGE 1 */
    PSF_PROPS inprops;
    long framesread;
    int infile = -1;
    /* init all dynamic resources to default states */
    int error = 0;
    PSF_CHPEAK *peaks = NULL;
    psf_format outformat = PSF_FMT_UNKNOWN;
    unsigned long nframes = NFRAMES;
    float *inframe = NULL;
    float *outframe = NULL;
    FILE *fp;
    double windowdur = DEFAULT_WINDOW_MSECS; /* duration of the window in msecs */
    unsigned long winsize;
    double brktime; /* holds the time for the current breakpoint time */
    unsigned long npoints;
    /* TODO: define an output frame buffer if channel width different 	*/

    /* STAGE 2 */
    printf("ENVX: extract amplitude envelope from mono soundfile\n");

    /* process any optional flags: remove this block if none used! */
    if (argc > 1)
    {
        char flag;
        while (argv[1][0] == '-')
        {
            flag = argv[1][1];
            switch (flag)
            {
            /*TODO: handle any  flag arguments here */
            case ('\0'):
                printf("Error: missing flag name\n");
                return 1;
            case ('w'):
                windowdur = atof(&argv[1][2]);
                if (windowdur <= 0.0)
                {
                    printf("Error: Bad value for Window Duration. %d"
                           "Must be positive\n",
                           windowdur);
                    return 1;
                }
                break;
            default:
                break;
            }
            argc--;
            argv++;
        }
    }

    /* check rest of commandline */
    if (argc < ARG_NARGS)
    {
        printf("insufficient arguments.\n"
               /* TODO: add required usage message */
               "usage: envx [-wN] insoundfile outfile.brk\n"
               "-wN set extraction window size to N msecs\n"
               "default:15\n");
        return 1;
    }
    /*  always startup portsf */
    if (psf_init())
    {
        printf("unable to start portsf\n");
        return 1;
    }
    /* STAGE 3 */

    infile = psf_sndOpen(argv[ARG_INFILE], &inprops, 0);
    if (infile < 0)
    {
        printf("Error: unable to open infile %s\n", argv[ARG_INFILE]);
        error++;
        goto exit;
    }
    /* TODO: verify infile format for this application */
    if (inprops.chans > 1)
    {
        printf("Soundfile contains %d channels: must be mono\n", inprops.chans);
        error++;
        goto exit;
    }
    windowdur /= 1000.0; /* convert to secs */
    winsize = (unsigned long)(windowdur * inprops.srate);
    /* allocate space for  sample frame buffer ...*/
    inframe = (float *)malloc(windowdur * sizeof(float));
    if (inframe == NULL)
    {
        puts("No memory!\n");
        error++;
        goto exit;
    }
    /* check file extension of outfile name, so we use correct output file format*/

    /* STAGE 4 */
    /* TODO: any other argument processing and setup of variables,
       output buffer, etc., before creating outfile
    */

    /* handle outfile */
    /* TODO:  make any changes to outprops here  */

    /* TODO: if outchans != inchans, allocate outframe, and modify main loop accordingly */

    fp = fopen(argv[ARG_OUTFILE], "w");
    if (fp == NULL)
    {
        printf("envx: unable to create breakpint file %s\n", argv[ARG_OUTFILE]);
        error++;
        goto exit;
    }
    /* STAGE 5 */
    printf("processing....\nWinsize:%d", winsize);
    /* TODO: init any loop-related variables */
    brktime = 0.0;
    npoints = 0;
    while ((framesread = psf_sndReadFloatFrames(infile, inframe, winsize)) > 0)
    {
        printf("Hej");
        double amp;
        amp = maxsamp(inframe, framesread);

        if (fprintf(fp, "%f\t%f\n", brktime, amp) < 0)
        {
            printf("Failed to write to breakpoint file %s\n", argv[ARG_OUTFILE]);
            error++;
            break;
        }
        brktime += windowdur;
        npoints++;

        /* <--------  add buffer processing here ------>  */
    }

    if (framesread < 0)
    {
        printf("Error reading infile. Outfile is incomplete.\n");
        error++;
    }
    else
        printf("Done: %d errors\n", error);
    printf("%d breakpoints written to %s\n", npoints, argv[ARG_OUTFILE]);
    /* STAGE 6 */
    /* report PEAK values to user */
    if (framesread < 0)
    {
        printf("Error reading infile. Outfile is incomplete.\n");
        error++;
    }
    else
    {
        printf("Done: %d errors\n", error);
    }
    printf("%d breakpoints written to %s\n", npoints, argv[ARG_OUTFILE]);
    /* STAGE 7 */
    /* do all cleanup  */
exit:
    if (infile >= 0)
        if (psf_sndClose(infile))
            printf("%s: Warning: error closing infile %s\n", argv[ARG_PROGNAME], argv[ARG_INFILE]);
    if (inframe)
        free(inframe);
    if (fp)
        if (fclose(fp))
            printf("envx: failed to close output file %s\n", argv[ARG_OUTFILE]);

    /*TODO: cleanup any other resources */

    psf_finish();
    return error;
}
