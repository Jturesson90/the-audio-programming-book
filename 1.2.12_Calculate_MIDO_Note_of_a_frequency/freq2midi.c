#include <stdio.h>
#include <math.h>

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
    double foundMidinoteFrequency, deviation, otherFoundMidinoteFrequency;
    /* calculate required numbers */

    double semitone_ratio = pow(2, 1 / 12.0); /* approx. 1.0594631 
    /* find Middle C, three semitones above low A = 220 */
    c5 = 220.0 * pow(semitone_ratio, 3);
    /* MIDI Note 0 is C, 5 octaves below Middle C */
    c0 = c5 * pow(0.5, 5);

    /* calculate a frequency for a given MIDI Note Number */
    frequency = 450.0;
    midinote = freq2midi(frequency, c0, semitone_ratio);

    foundMidinoteFrequency = midi2freq(midinote, c0, semitone_ratio);
    if (foundMidinoteFrequency > frequency)
    {
        otherFoundMidinoteFrequency = midi2freq(midinote - 1, c0, semitone_ratio);
        deviation = -(100 * (10 / (foundMidinoteFrequency - otherFoundMidinoteFrequency)));
    }
    else
    {
        otherFoundMidinoteFrequency = midi2freq(midinote + 1, c0, semitone_ratio);
        deviation = 100 * (10 / (otherFoundMidinoteFrequency - foundMidinoteFrequency));
    }

    printf("The nearest MIDI Note to the frequency %f is %d\nWith the deviation of %f%%\n", frequency, midinote, deviation);

    return 0;
}
