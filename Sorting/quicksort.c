#include <stdio.h>
#include <stdlib.h>

void _qsort(int *arr, int begin, int end)
{
    if (begin >= end - 1)
        return;

    int lbound = begin + 1;
    int rbound = end - 1;
    int pivot = begin;
    int temp;

    while (lbound <= rbound)
    {
        while (lbound < end && arr[lbound] <= arr[pivot])
            lbound++;
        while (rbound > begin && arr[rbound] > arr[pivot])
            rbound--;
        if (lbound <= rbound)
        {
            temp = arr[lbound];
            arr[lbound] = arr[rbound];
            arr[rbound] = temp;
            lbound++;
            rbound--;
        }
    }
    temp = arr[rbound];
    arr[rbound] = arr[pivot];
    arr[pivot] = temp;

    _qsort(arr, begin, rbound + 1);
    _qsort(arr, rbound + 1, end);
}

void quick_sort(int *arr, int len)
{
    _qsort(arr, 0, len);
}

void print_arr(int *arr, int len)
{
    printf("> { ");
    for (int i = 0; i < len; i++)
        printf("%d ", arr[i]);
    printf("}\n");
}

int main()
{
    int num[10] = {2, 5, 3, 9, 6, 1, 8, 4, 0, 7};

    print_arr(num, 10);
    quick_sort(num, 10);
    print_arr(num, 10);

    return 0;
}