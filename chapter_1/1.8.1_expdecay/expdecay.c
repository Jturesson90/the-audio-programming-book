/* expdecay.c */
/* implement formula x[t] = a * exp(-k / T) */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

enum
{
    ARG_NAME,
    ARG_DUR,
    ARG_T,
    ARG_STEPS,
    ARG_NARGS
};

int main(int argc, char **argv)
{
    int i, nsteps;
    double step, x, a, T, k;
    double dur;
    if (argc != ARG_NARGS)
    {
        printf("usage: expdecay dur T steps\n");
        return 1;
    }
    dur = atof(argv[1]);
    T = atof(argv[2]);
    nsteps = atoi(argv[3]);

    k = dur / nsteps; /* the constant time increment */
    a = exp(-k / T);  /* calc the constant ratio value */
    x = 1.0;          /* Starting value */
    step = 0.0;
    for (i = 0; i < nsteps; i++)
    {
        printf("%.4lf\t%.8lf\n", step, x);
        x = a * x;
        step += k;
    }

    return 0;
}