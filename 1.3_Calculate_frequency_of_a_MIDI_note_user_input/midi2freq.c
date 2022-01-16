#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <ctype.h>

int main()
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
    printf("Enter MIDI note (0 - 127): ");
    result = gets(message);
    if (result == NULL)
    {
        printf("There was an error reading the input.\n");
        return 1;
    }
    if (message[0] == '\0')
    {
        printf("Have a nice day!\n");
        return 1;
    }
    int length = strlen(message);
    while (length--)
    {
        if (message[length] == '.')
        {
            printf("MIDI note cannot be a float");
            return 1;
        }
    }

    midinote = atoi(message);
    if (!isdigit(*message))
    {
        printf("Input %s is not a MIDI note", message);
        return 1;
    }
    if (midinote < 0)
    {
        printf("Sorry - %s is a bad MIDI note number\n", message);
        return 1;
    }
    if (midinote > 127)
    {
        printf("Sorry - %s is beyond the MIDI dange\n", message);
    }
    frequency = c0 * pow(semitone_ratio, midinote);
    printf("MIDI Note %d has frequency %f\n", midinote, frequency);

    return 0;
}