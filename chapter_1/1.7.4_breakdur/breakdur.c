#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    double time;
    double value;
} BREAKPOINT;
BREAKPOINT maxpoint(const BREAKPOINT *points, long npoints);
BREAKPOINT *get_breakpoints(FILE *fp, long *psize)
{
    int got;
    long npoints = 0, size = 64;
    double lasttime = 0.0;
    BREAKPOINT *points = NULL;
    char line[80];
    if (fp == NULL)
    {
        return NULL;
    }
    points = (BREAKPOINT *)malloc(sizeof(BREAKPOINT) * size);
    if (points == NULL)
    {
        return NULL;
    }
    while (fgets(line, 80, fp))
    {
        got = sscanf(line, "%lf%lf", &points[npoints].time, &points[npoints].value);
        if (got < 0)
            continue;
        if (got == 0)
        {
            printf("Line %d has non-numeric data\n", npoints + 1);
            break;
        }
        if (got == 1)
        {
            printf("Incomplete breakpoint found at point %d\n", npoints + 1);
            break;
        }
        if (points[npoints].time < lasttime)
        {
            printf("data error at point %d: time not increasing\n", npoints + 1);
            break;
        }

        lasttime = points[npoints].time;
        if (++npoints == size)
        {
            BREAKPOINT *tmp;
            size += npoints;
            tmp = (BREAKPOINT *)realloc(points, sizeof(BREAKPOINT) * size);
            if (tmp == NULL)
            {
                npoints = 0;
                free(points);
                points = NULL;
                break;
            }
            points = NULL;
        }
    }
    if (npoints)
    {
        *psize = npoints;
    }
    return points;
}
int main(int argc, char const *argv[])
{
    long size;
    double dur;
    BREAKPOINT point, *points;
    FILE *fp;
    if (argc < 2)
    {
        return 0;
    }
    fp = fopen(argv[1], "r");
    if (fp == NULL)
        return 0;

    size = 0;
    points = get_breakpoints(fp, &size);
    if (points == NULL || size < 2 || points[0].time != 0.0)
    {
        free(points);
        fclose(fp);
        return 1;
    }
    printf("read %d breakpoints\n", size);
    dur = points[size - 1].time;
    printf("duration: %f seconds\n", dur);
    point = maxpoint(points, size);
    printf("maximum value: %f at %f seconds\n", point.value, point.time);
    free(points);
    fclose(fp);

    return 0;
}

BREAKPOINT maxpoint(const BREAKPOINT *points, long npoints)
{
    int i;
    BREAKPOINT point;
    point.time = points[0].time;
    point.value = points[0].value;
    for (i = 0; i < npoints; i++)
    {
        if (point.value < points[i].value)
        {
            point.value = points[i].value;
            point.time = points[i].time;
        }
        /* code */
    }
    return point;
}