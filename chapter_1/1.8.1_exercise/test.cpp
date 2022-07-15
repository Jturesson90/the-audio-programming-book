#include <math.h>
#include <iostream>

const float sampleRate = 44100;
float coeff;
float currentLevel;

void init(float levelBegin, float levelEnd, float releaseTime)
{
    currentLevel = levelBegin;
    coeff = (log(levelEnd) - log(levelBegin)) /
            (releaseTime * sampleRate);
}

inline void calculateEnvelope(int samplePoints)
{
    for (int i = 0; i < samplePoints; i++)
    {
        currentLevel += coeff * currentLevel;
        printf("%i\t%.8lf\n", i, currentLevel);
        // do something with 'currentLevel' here
    }
}

int main()
{
    init(1.0f, 0.0001f, 2.0f);
    calculateEnvelope(500);
    return 0;
}