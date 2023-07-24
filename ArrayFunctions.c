#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int IndexArray(int *o_Element, int *i_Array, int i_Index);
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

    int intArray[] = {0,1,2,3,4,5,6,7,8,9};
    int element;
    
    IndexArray(&element, intArray, 7);
    
    printf("IndexArray result: %d\n", element);

    return 0;
}

int IndexArray(int *o_Element, int *i_Array, int i_Index)
{
    *o_Element = i_Array[i_Index];
    return 0;
}

int ReplaceSubsetArray(int *o_Array, int *i_Array, int i_Index, int i_NewElement)
{

    return 0;
}

int InsertIntoArray(int *o_Array, int *i_Array, int i_Index, int i_NewElement)
{
    
    return 0;
}

int DeleteFromArray(int *o_SubsetDeleted, int *o_DeletedPortion, int *i_Array, int i_Index, int i_Length)
{

    return 0;
}

int BuildArray(int *o_AppendedArray, int *i_Array)
{

    return 0;
}

int ArraySubset(int *o_SubArray, int *i_Array, int i_Index, int i_Length)
{

    return 0;
}

int ArrayMaxAndMin(int *o_MaxValue, int o_MaxIndex, int *o_MinValue, int o_MinIndex, int *i_Array)
{

    return 0;
}

int Sort1DArray(int *o_SortedArray, int *i_Array)
{

    return 0;
}