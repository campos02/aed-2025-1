#include <stdio.h>

void Quicksort(int *arr, int left, int right) {
    int i = left;
    int j = right;
    int mid = arr[(left + right) / 2];

    do {
        while (arr[i] < mid)
            i++;

        while (mid < arr[j])
            j--;
        
        if (i <= j) {
            int tmp = arr[i];
            arr[i] = arr[j];
            arr[j] = tmp;
            i++;
            j--;
        }
    } while (i <= j);

    if (left < j)
        Quicksort(arr, left, j);

    if (i < right)
        Quicksort(arr, i, right);
}

int *Merge(int *nums1, int nums1Size, int m, int *nums2, int nums2Size, int n)
{
    for (int i = m; i < nums1Size; i++) {
        nums1[i] = nums2[i - m];
    }

    Quicksort(nums1, 0, nums1Size - 1);
    return nums1;
}

int main()
{
    int nums1arr[6] = {0, 0, 0, 0, 0, 0};
    int nums2arr[6] = {1, 2, 3, 4, 5, 6};
    int *nums1 = nums1arr;
    int *nums2 = nums2arr;

    nums1 = Merge(nums1, 6, 0, nums2, 6, 6);
    for (int i = 0; i < 6; i++)
    {
        printf("%d ", nums1[i]);
    }

    printf("%n");
}