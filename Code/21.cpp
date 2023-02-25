//交换排序(交替冒泡排序)
//标记冒泡排序和限域冒泡排序的平均时间n+3d(经验分析)
//交替冒泡排序为n+1.5d(经验分析)
//插入排序为n+d(经验分析)
#include <iostream>
using namespace std;
template <class T>
void myswap(int &a, int &b)
{
    int temp = a;
    a = b;
    b = temp;
}
template <class T>
void alternatingbubblesort(T *array, int n)
{
    int lower = 0;
    int upper = n - 1;
    while (true)
    {
        int new_upper = lower;
        for (int i = lower; i < upper; ++i)
        {
            if (array[i] > array[i + 1])
            {
                T tmp = array[i];
                array[i] = array[i + 1];
                array[i + 1] = tmp;
                new_upper = i;
            }
        }
        upper = new_upper;
        if (lower == upper)
        {
            break;
        }
        int new_lower = upper;
        for (int i = upper; i > lower; --i)
        {
            if (array[i - 1] > array[i])
            {
                T tmp = array[i];
                array[i] = array[i - 1];
                array[i - 1] = tmp;
                new_lower = i;
            }
        }
        lower = new_lower;
        if (lower == upper)
        {
            break;
        }
    }
}
int main()
{
    int a[] = {49, 38, 65, 97, 76, 13, 27, 49};
    alternatingbubblesort(a, 8);
    for (int i = 0; i < 8; i++)
    {
        cout << a[i] << " ";
    }
    cout << endl;
    return 0;
}