#include <stdio.h>
#include <stdlib.h>

/**
·*·Note:·The·returned·array·must·be·malloced,·assume·cal
·*/
int* dailyTemperatures(int *T, int TSize, int *returnSize)
{
    int i = 0;
    *returnSize = TSize;
    int *returnData = (int *)malloc(sizeof(int) * TSize);

    for (i=0; i<TSize; i++)
    {
        for (int j=i+1; j<TSize; j++)
        {
            if (T[j] > T[i]) {
                returnData[i] = j - i;
                break;
            }
        }
    }
    returnData[TSize-1] = 0;

    return returnData;
}

int test_dailyTemperatures()
{
    int temp[4096] = {0};
    int returnSize;
    int *returnData = NULL;

    for(int i=0; i<4096; i++)
        temp[i] = 76;

    returnData = dailyTemperatures(temp, 4096, &returnSize);

    for (int i=0; i<returnSize; i++)
    {
        printf("i %d, %d\n", i, returnData[i]);
    }

    return 0;
}