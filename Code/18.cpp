//交换排序(冒泡排序)
//空间复杂度为O(1)
//最好和最坏时间复杂度均为O(n^2)，因此平均复杂度也为O(n^2)
//稳定性:稳定的
#include <iostream>
using namespace std;
template <class T>
void bubblesort(T a[], int n)
{
    T temp;
    for (int i = n - 1; i > 0; i--)
    {
        for (int j = 0; j < i; j++)
        {
            if (a[j + 1] < a[j])
            {
                temp = a[j];
                a[j] = a[j + 1];
                a[j + 1] = temp;
            }
        }
    }
}
int main()
{
    int a[] = {49, 38, 65, 97, 76, 13, 27, 49};
    bubblesort(a, 8);
    for (int i = 0; i < 8; i++)
    {
        cout << a[i] << " ";
    }
    cout << endl;
    return 0;
}