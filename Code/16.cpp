//插入排序(折半插入排序)
//空间复杂度为O(1)
//O(n^2)(但是比较元素的次数减少到了O(nlnn)
#include <iostream>
using namespace std;
template <class T>
void binaryinsertsearch(T a[], int n)
{
    T temp;
    int i, j, low, mid, high;
    for (i = 1; i < n; i++)
    {
        temp = a[i];
        low = 0;
        high = i - 1;
        while (low <= high)
        {
            mid = (low + high) / 2;
            if (a[i] < a[mid])
            {
                high = mid - 1;
            }
            else
            {
                low = mid + 1;
            }
        }
        for (j = i - 1; j >= mid; j--)
        {
            a[j + 1] = a[j];
        }
        a[high + 1] = temp;
    }
}
int main()
{
    int a[] = {1, 3, 2, 4, 5, 7, 8, 6};
    binaryinsertsearch(a, 8);
    for (int i = 0; i < 8; i++)
    {
        cout << a[i] << " ";
    }
    return 0;
}