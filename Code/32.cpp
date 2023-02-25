//堆排序
//空间效率为O(1)
//时间效率:建堆时间复杂度为O(n),调整为O(h)(即下沉),故最好最坏平均复杂度均为O(nln)
//不稳定
#include <iostream>
using namespace std;
template <class T>
bool heapless(T *heap, int i, int j)
{
    return heap[i] < heap[j] ? true : false;
}
template <class T>
void exchange(T *heap, int i, int j)
{
    T temp = heap[i];
    heap[i] = heap[j];
    heap[j] = temp;
}
template <class T>
void sink(T *heap, int i, int n) //通过循环比较当前节点和其子节点的值如果小于则与较大节点交换
{
    while (2 * i <= n)
    {
        int max;
        if (2 * i + 1 <= n)
        {
            if (heapless(heap, 2 * i, 2 * i + 1))
            {
                max = 2 * i + 1;
            }
            else
            {
                max = 2 * i;
            }
        }
        else
        {
            max = 2 * i;
        }
        if (heapless(heap, i, max))
        {
            exchange(heap, i, max);
            i = max;
        }
        else
        {
            break;
        }
    }
}
template <class T>
void createheap(T *heap, T *array, int n) //降低复杂度的构造方式
{
    for (int i = 0; i < n; i++) //首先先把元素直接拷贝过去
    {
        heap[i + 1] = array[i];
    }
    for (int i = n / 2; i >= 1; i--) //然后从中间开始至开头元素依次执行下沉//一定要从下往上，因为可以直观理解为石头下沉，只有下层理顺了，上层在下沉的过程中才不会卡壳
    {
        sink(heap, i, n);
    }
}
template <class T>
void heapsort(T *array, int n)
{
    T heap[n + 1];
    createheap(heap, array, n);
    int m = n;
    while (m != 1)
    {
        exchange(heap, 1, m);
        m--;
        sink(heap, 1, m);
    }
    for (int i = 0; i < n; i++)
    {
        array[i] = heap[i + 1];
    }
}
int main()
{
    int a[] = {1, 5, 6, 2, 4, 3, 7, 8, 9};
    heapsort(a, 9);
    for (int i = 0; i < 9; i++)
    {
        cout << a[i] << " ";
    }
    return 0;
}