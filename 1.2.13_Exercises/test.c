#include <stdio.h>

int main(int argc, char const *argv[])
{
    printf("Size of\nint: %d\nchar: %d\nshort: %d\nlong: %d\nfloat: %d\ndouble: %d\n",
           sizeof(int), sizeof(char), sizeof(long), sizeof(float), sizeof(double));

    return 0;
}
