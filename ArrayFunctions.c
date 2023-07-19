#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int IndexArray(int o_Element, int *i_Array, int i_Index);
int ReplaceSubsetArray(int *o_Array, int *i_Array, int i_Index, int i_NewElement);
int InsertIntoArray(int *o_Array, int *i_Array, int i_Index, int i_NewElement);
int DeleteFromArray(int *o_SubsetDeleted, int *o_DeletedPortion, int *i_Array, int i_Index, int i_Length);
int BuildArray(int *o_AppendedArray, int *i_Array);
int ArraySubset(int *o_SubArray, int *i_Array, int i_Index, int i_Length);
int ArrayMaxAndMin(int *o_MaxValue, int o_MaxIndex, int *o_MinValue, int o_MinIndex, int *i_Array);
int Sort1DArray(int *o_SortedArray, int *i_Array);

int main(int argc, char *argv[])
{
    char *arr[10] = {"alma", "banan", "citrom", "narancs", "kalacs"};
    printf("Size of the array: %d\n", sizeof(arr)/sizeof(*arr));

    return 0;
}