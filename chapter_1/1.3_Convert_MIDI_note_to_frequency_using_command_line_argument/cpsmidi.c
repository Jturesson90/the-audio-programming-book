#include <stdio.h>
#include <stdlib.h>
#include <math.h>
int main(int argc, char const *argv[])
{
    double c0, c5, frequency;
    int midinote;
    char message[256];
    char *result;
    double semitone_ratio = pow(2, 1 / 12.0); /* approx. 1.0594631 
    /* find Middle C, three semitones above low A = 220 */
    c5 = 220.0 * pow(semitone_ratio, 3);
    /* MIDI Note 0 is C, 5 octaves below Middle C */
    c0 = c5 * pow(0.5, 5);

    /* if the program is not called cpsmidi, 
    either change the lines below, 
    or use the argv[0] system, shown commented out below */

    if (argc != 2)
    {
        printf("\n%s : converts MIDI note to frequency.\n", argv[0]);
        printf("usage: %s MIDInote\n", argv[0]);
        printf(" range: 0 <= MIDInote <= 127 \n");
        return 1;
    }
    midinote = atoi(argv[1]);
    /* use argv[1] to echo a bad argument string to the user */
    if (midinote < 0 || midinote > 127)
    {
        printf("BAD MIDI NOTE");
        return 1;
    }
    frequency = c0 * pow(semitone_ratio, midinote);
    printf("frequency of MIDI note %d = %f\n", midinote, frequency);
    return 0;
}
