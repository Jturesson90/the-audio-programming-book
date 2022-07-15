/* iscale.c */
/* generate E.T tabled for N-notes to the octave (N <= 24) */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/*  usage iscale [-m] [-i] N startval [outfile.txt]
    -m : sets format of startval as MIDI note
    -i : prints the calculated interval as well as the absolute frequency
    outfile : optional text filename for output data
*/

int main(int argc, char const *argv[])
{
    int ismidi = 0;
    int write_interval = 0;
    int should_append = 0;
    int file_exist = 0;
    int err = 0;
    int notes, i;
    double startval, basefreq, ratio;
    FILE *fp;
    double intervals[25];
    int argv_steppes = 0;

    /* check first arg for flag option: argc at least 2 */
    while (argc > 1)
    {
        if (argv[1][0] == '-')
        {
            char flag = argv[1][1];
            if (flag == 'm')
                ismidi = 1;
            else if (flag == 'i')
                write_interval = 1;
            else if (flag == 'a')
                should_append = 1;
            else
            {
                printf("error: unrecognized option %s\n", argv[1]);
                return 1;
            }
            argc--;
            argv++;
            argv_steppes++;
        }
        else
            break;
    }
    if (argc < 3)
    {
        printf("insufficient arguments\n");
        printf("Usage: iscale [-m] [-i] N startval [outfile.txt]\n");
        printf("-m : sets format of startval as MIDI note\n");
        printf("-i : prints the calculated interval as well as the absolute frequency\n");
        printf("-a : should append the outfile instead of replace\n");
        printf("outfile : optional text filename for output data\n");
        return 1;
    }
    /* now read and check all the arguments */
    /* we now expect argv[1] to hold N and argv[2] startval*/
    notes = atoi(argv[1]);
    if (notes < 1 || notes > 24)
    {
        printf("error: N out of range. Must be between 1 and 24.\n");
        return 1;
    }
    startval = atof(argv[2]);
    if (ismidi)
    {
        if (startval < 0.0 || startval > 127.0)
        {
            printf("error: MIDI startval out of range. Must be between 0 and 127.\n");
            return 1;
        }
    }
    else
    {
        if (startval <= 0.0)
        {
            printf("error: frequency startval out of range. Must be above 0.0.\n");
            return 1;
        }
    }
    fp = NULL;
    if (argc == 4)
    {
        fp = fopen(argv[3], "r");
        if (fp)
        {
            file_exist = 1;
            fclose(fp);
        }
        fp = fopen(argv[3], should_append ? "a" : "w");

        if (fp == NULL)
        {
            printf("WARNING: unable to create file %s\n", argv[3]);
            perror("");
        }
    }
    /* all params ready - fill array and write to file if created */
    /* find basefreq, if val i MIDI */
    if (ismidi)
    {
        double c0, c5;
        ratio = pow(2.0, 1.0 / 12.0);
        /* find Middle C, three semitones above low A = 220 */
        c5 = 220.0 * pow(ratio, 3);
        /* MIDI note 0 is C, 5 octaves below Middle C */
        c0 = c5 * pow(0.5f, 5);
        basefreq = c0 * pow(ratio, startval);
    }
    else
        basefreq = startval;

    /* calc ratio from notes, and fill the array */
    ratio = pow(2.0, 1.0 / notes);
    for (i = 0; i <= notes; i++)
    {
        intervals[i] = basefreq;
        basefreq *= ratio;
    }

    /* finally, read array, write to screen, and optionally to file */
    if (fp)
    {
        argc += argv_steppes;
        argv -= argv_steppes;

        for (int i = 0; i < argc; i++)
        {
            fprintf(fp, "%s ", argv[i]);
        }

        fprintf(fp, "\n");
    }

    for (i = 0; i <= notes; i++)
    {
        double interval = intervals[i];
        double frequency = pow(ratio, i);
        if (write_interval)
            printf("%d:\t%f\t%f\n", i, frequency, interval);
        else
            printf("%d:\t%f\n", i, interval);
        if (fp && err >= 0)
        {
            if (write_interval)
                err = fprintf(fp, "%d:\t%f\t%f\n", i, frequency, interval);
            else
                err = fprintf(fp, "%d:\t%f\n", i, interval);
        }
    }

    if (fp)
        fprintf(fp, "\t\t---------------\t\t\n");
    if (err < 0)
    {
        perror("There was an error writing the file.\n");
    }
    if (fp)
        fclose(fp);

    return 0;
}
