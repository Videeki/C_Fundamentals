#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int Sort1DArray(char *input[]);

int main(int argc, char *argv[])
{
    char *arr[10] = {"alma", "banan", "citrom", "narancs", "kalacs"};
    printf("Size of the array: %d\n", sizeof(arr)/sizeof(*arr));
    Sort1DArray(arr);
    return 0;
}

int Sort1DArray(char *input[])
{
    printf("%d\n", sizeof(input)/sizeof(*input));
    int size = sizeof(input)/sizeof(*input);
    for(int i = 0; i < size; i++)
    {
        printf("%s\n", input[i]);
    }
    return 0;
}