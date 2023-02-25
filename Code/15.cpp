//插入排序(直接插入排序)(排序的默认顺序是从小到大输出)
//适用性:链表和顺序存储均适用(注大部分排序算法都仅适用于顺序存储的线性表)
//稳定性:相同元素相对位置在排序中不会发生变化
//空间复杂度为O(1)
//O(n^2)(平均情况下比较次数和移动次数均为(n^2/4)
//比较次数最优为正序O(n),最劣为反序O(n(n+1)/2)
#include <iostream>
using namespace std;
template <class T>
void directinsertsort(T a[], int n)
{
    T temp;
    int i, j;
    for (i = 1; i < n; i++)
    {
        if (a[i] < a[i - 1])
        {
            temp = a[i];
            for (j = i - 1; temp < a[j] && j >= 0; j--) //这里如果不加到头停止则会冲出数组边界，因为默认a[-1]=0,所以在所有元素均大于0时不会报错，要小心
            {
                a[j + 1] = a[j];
            }
            a[j + 1] = temp; //这里是因为j会在不符合要求的元素停下来，应该插入的位置就是这个元素的下一个位置
        }
    }
}
int main()
{
    int a[] = {49, 38, 65, 97, 76, 13, 27, 49};
    directinsertsort(a, 8);
    for (int i = 0; i < 8; i++)
    {
        cout << a[i] << " ";
    }
    cout << endl;
    return 0;
}