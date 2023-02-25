//二叉堆(堆)之最大堆(即根节点元素最大)
#include <iostream>
using namespace std;
template <class T>
class heap
{
public:
    T *root;
    int size;
    int n; //数组元素个数
    heap(int s);
    ~heap() {}
    bool less(int i, int j);     //判断索引i处元素是否小于j处
    void exchange(int i, int j); //交换i和j处的元素
    void insert(T elem);         //插入一个元素
    void swim(int i);            //通过上浮使i处的元素能处于正确的位置并使堆的逻辑正确
    T delmax();                  //删除堆中最大的元素,并返回删除的最大元素
    void sink(int i);            //通过下沉使i处元素能处于正确的位置并使堆的逻辑正确
};
template <class T>
heap<T>::heap(int s)
{
    size = s;
    root = new T[size];
    root[0] = NULL;
    n = 0;
}
template <class T>
bool heap<T>::less(int i, int j)
{
    return root[i] < root[j] ? true : false;
}
template <class T>
void heap<T>::exchange(int i, int j)
{
    T temp = root[i];
    root[i] = root[j];
    root[j] = temp;
}
template <class T>
void heap<T>::swim(int i) //通过循环比较当前节点和其父节点的值如果父节点小于则交换
{
    while (less(i / 2, i) && i > 1)
    {
        exchange(i, i / 2);
        i /= 2;
    }
}
template <class T>
void heap<T>::insert(T data)
{
    root[++n] = data; //元素个数自增1然后在该位置插入新元素
    swim(n);
}
template <class T>
void heap<T>::sink(int i) //通过循环比较当前节点和其子节点的值如果小于则与较大节点交换
{
    while (2 * i <= n)
    {
        int max;
        if (2 * i + 1 <= n)
        {
            if (less(2 * i, 2 * i + 1))
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
        if (less(i, max))
        {
            exchange(i, max);
            i = max;
        }
        else
        {
            break;
        }
    }
}
template <class T>
T heap<T>::delmax()
{
    T temp = root[1];
    exchange(1, n);
    root[n--] = NULL;
    sink(1);
    return temp;
}
int main()
{
    heap<char> heap1(10);
    heap1.insert('A');
    heap1.insert('B');
    heap1.insert('C');
    heap1.insert('D');
    heap1.insert('E');
    heap1.insert('F');
    heap1.insert('G');
    char temp;
    while (temp = heap1.delmax())
    {
        cout << temp;
    }
    return 0;
}
