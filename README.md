# the-audio-programming-book

##

### Table 0.2 - The ANSI C format specifiers

| Specifier | Type                | Print                    |
| :-------- | ------------------- | ------------------------ |
| %c        | char                | Single character         |
| %d (%i)   | int                 | Signed integer           |
| %e (%E)   | float or double     | Exponential format       |
| %f        | float or double     | Signed decimal           |
| %g (%G)   | float or double     | Use %f or %e as required |
| %o        | int                 | Unsigned octal value     |
| %s        | string (char array) | Sequence of characters   |
| %u        | int                 | Unsigned decimal         |
| %x (%X)   | int                 | Unsigned hex value       |

### Table 0.6 - Some of the more popular functions from the standard C library

|                     |                                                               |
| ------------------- | ------------------------------------------------------------- |
| **stdio.h**         | **I/O functions**                                             |
| getchar()           | Returns next character typed on keyboard                      |
| putchar()           | Outputs a single character to screen                          |
| printf()            | Outputs to stdout                                             |
| scanf()             | Reads data from stdin                                         |
| <br /> **string.h** | <br /> **String functions**                                   |
| strcat()            | Concatenates a copy of str2 to str1                           |
| strcmp())           | Compares two strings                                          |
| strcpy()            | Copies contents of str2 to str1                               |
| <br /> **ctype.h**  | <br /> **Character functions**                                |
| isdigit()           | Returns non-0 if arg is digit from 0 to 9                     |
| isalpha())          | Returns non-0 if arg is a letter of alphabet                  |
| isalnum()           | Returns non-0 if arg is a letter or digit                     |
| islower())          | Returns non-0 if arg is a lowercase letter                    |
| isupper()           | Returns non-0 if arg is a uppercase letter                    |
| <br /> **math.h**   | <br /> **Mathematic functions**                               |
| acos()              | Returns arc cosine of arg                                     |
| asin())             | Returns arc sine of arg                                       |
| atan()              | Returns arc tangent of arg                                    |
| cos())              | Returns cosine of arg                                         |
| sin()               | Returns sine of arg                                           |
| exp())              | Returns natural logaritm _e_                                  |
| fabs()              | Returns absolute value of num                                 |
| sqrt()              | Returns square root of num                                    |
| <br /> **time.h**   | <br /> **Time and date functions**                            |
| time()              | Returns current calender time of system                       |
| difftime())         | Returns difference in secs between two times                  |
| clock()             | Returns number of system clock cycles since program execution |
| <br /> **stdlib.h** | <br /> **Miscellaneous functions**                            |
| malloc()            | Returns current calender time of system                       |
| rand()              | Returns difference in secs between two times                  |
| srand()             | Returns number of system clock cycles since program execution |
