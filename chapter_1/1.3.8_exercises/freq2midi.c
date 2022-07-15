#include <stdio.h>
#include <math.h>
#include <stdlib.h>

double midi2freq(int midinote, double c0, double semitone_ratio)
{
    double frequency;
    frequency = c0 * pow(semitone_ratio, midinote);

    return frequency;
}

int freq2midi(double frequency, double c0, double semitone_ratio)
{
    double fracmidi;
    int midinote;
    fracmidi = log(frequency / c0) / log(semitone_ratio);
    /* round fracmidi to the nearest whole number */
    midinote = (int)(fracmidi + 0.5);

    return midinote;
}

int main()
{
    double c0, c5, frequency;
    int midinote;
    char message[256];
    char *result;

    double foundMidinoteFrequency, deviation, otherFoundMidinoteFrequency;
    /* calculate required numbers */

    double semitone_ratio = pow(2, 1 / 12.0); /* approx. 1.0594631 
    /* find Middle C, three semitones above low A = 220 */
    c5 = 220.0 * pow(semitone_ratio, 3);
    /* MIDI Note 0 is C, 5 octaves below Middle C */
    c0 = c5 * pow(0.5, 5);

    printf("Enter a frequency: ");
    result = gets(message);
    if (result == NULL)
    {
        printf("Bad input!\n");
        return 1;
    }
    if (message[0] == '\0')
    {
        printf("Have a nice day!\n");
        return 1;
    }
    frequency = atoi(message);
    if (frequency <= 0)
    {
        printf("Could not find frequency %s", message);
        return 1;
    }
    /* calculate a frequency for a given MIDI Note Number */
    midinote = freq2midi(frequency, c0, semitone_ratio);

    foundMidinoteFrequency = midi2freq(midinote, c0, semitone_ratio);
    if (foundMidinoteFrequency > frequency)
    {
        otherFoundMidinoteFrequency = midi2freq(midinote - 1, c0, semitone_ratio);
        deviation = (int)(-(100 * (10 / (foundMidinoteFrequency - otherFoundMidinoteFrequency))) + 0.5);
    }
    else
    {
        otherFoundMidinoteFrequency = midi2freq(midinote + 1, c0, semitone_ratio);
        deviation = (int)(100 * (10 / (otherFoundMidinoteFrequency - foundMidinoteFrequency)) + 0.5);
    }

    printf("The nearest MIDI Note to the frequency %f is %d\nWith the deviation of %d%%\n", frequency, midinote, (int)deviation);

    return 0;
}
