//插入排序(希尔排序)
//空间复杂度为O(1)
//当n处于某个特定范围时，时间复杂度约为O(n^1.3),最坏情况为O(n^2)
//适用性:仅适用于顺序存储的情况
//稳定性:相同元素相对位置在排序中不会发生变化
#include <iostream>
using namespace std;
template <class T>
void shellsort(T a[], int n)
{
    T temp;
    int i, j;
    for (int d = n / 2; d >= 1; d /= 2)
    {
        for (i = d; i <= n; i++)
        {
            if (a[i] < a[i - d])
            {
                temp = a[i];
                for (j = i - d; temp < a[j] && j >= 0; j -= d)
                {
                    a[j + d] = a[j];
                }
                a[j + d] = temp;
            }
        }
    }
}
int main()
{
    int a[] = {49, 38, 65, 97, 76, 13, 27, 49};
    shellsort(a, 8);
    for (int i = 0; i < 8; i++)
    {
        cout << a[i] << " ";
    }
    cout << endl;
    return 0;
}