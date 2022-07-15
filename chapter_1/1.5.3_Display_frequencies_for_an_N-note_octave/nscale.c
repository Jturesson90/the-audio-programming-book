/* nscale.c: Display E.T frequencies for an N-note octave, from a given MIDI note */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(int argc, char const *argv[])
{
    int notes, midinote;
    double frequency, ratio, interval;
    double c0, c5;
    double intervals[24];

    if (argc != 4)
    {
        printf("Usage: nscale notes midinote interval\n");
        return 1;
    }
    notes = atoi(argv[1]);

    if (notes < 1 || 24 < notes)
    {
        printf("Error: notes must be 1 - 24");
        return 1;
    }
    midinote = atoi(argv[2]);
    if (midinote < 0 || midinote > 127)
    {
        printf("Error: midinote must be 0 - 127");
        return 1;
    }
    interval = atof(argv[3]);
    if (interval <= 1)
    {
        printf("Error: interval must be > 1");
        return 1;
    }
    /*** find the frequency of the MIDI note ***/

    /* calc standard E.T semitone ratio */
    ratio = pow(2.0, 1.0 / 12.0);
    /* find Middle C, three semitones above low A = 220 */
    c5 = 220.0 * pow(ratio, 3);
    /* MIDI note 0 is C, 5 octaves below Middle C */
    c0 = c5 * pow(0.5f, 5);
    frequency = c0 * pow(ratio, midinote);
    /* using the interval, calc ratio from notes, and fill the frequency array */
    ratio = pow(interval, 1.0 / notes);
    int i = 0;
    /*do
    {
        // notes must be above 0
        intervals[i++] = frequency;
        frequency *= ratio;
    } while (i < notes);*/
    /*while (i < notes)
    {
        intervals[i++] = frequency;
        frequency *= ratio;
    }*/
    int len = notes + 1;
    for (int i = 0; i < len; i++)
    {
        intervals[i] = frequency;
        frequency *= ratio;
    }
    /* finally, read array, write to screen */
    for (int i = 0; i < len; i++)
    {
        printf("%i: %f\n", (i + 1), intervals[i]);
    }

    return 0;
}
