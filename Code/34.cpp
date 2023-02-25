//最小优先队列(基于最小堆实现)(就函数less变为more就结束了)
#include <iostream>
using namespace std;
template <class T>
class minpriorityqueue
{
private:
    T *head;
    int n; //数组元素个数
public:
    minpriorityqueue(int s);
    ~minpriorityqueue() {}
    bool empty();                //判断队列是否为空
    bool more(int i, int j);     //判断索引i处元素是否大于j处
    void exchange(int i, int j); //交换i和j处的元素
    void insert(T elem);         //插入一个元素
    void swim(int i);            //通过上浮使i处的元素能处于正确的位置并使队列的逻辑正确
    T delmin();                  //删除堆中最大的元素,并返回删除的最小元素
    void sink(int i);            //通过下沉使i处元素能处于正确的位置并使队列的逻辑正确
};
template <class T>
minpriorityqueue<T>::minpriorityqueue(int s)
{
    head = new T[s + 1]; //和堆一致即头不放数据
    n = 0;
}
template <class T>
bool minpriorityqueue<T>::empty()
{
    return n == 0 ? true : false;
}
template <class T>
bool minpriorityqueue<T>::more(int i, int j)
{
    return head[i] > head[j] ? true : false;
}
template <class T>
void minpriorityqueue<T>::exchange(int i, int j)
{
    T temp = head[i];
    head[i] = head[j];
    head[j] = temp;
}
template <class T>
void minpriorityqueue<T>::swim(int i) //通过循环比较当前节点和其父节点的值如果父节点小于则交换
{
    while (more(i / 2, i) && i > 1)
    {
        exchange(i, i / 2);
        i /= 2;
    }
}
template <class T>
void minpriorityqueue<T>::insert(T data)
{
    head[++n] = data; //元素个数自增1然后在该位置插入新元素
    swim(n);
}
template <class T>
void minpriorityqueue<T>::sink(int i) //通过循环比较当前节点和其子节点的值如果小于则与较大节点交换
{
    while (2 * i <= n)
    {
        int min;
        if (2 * i + 1 <= n)
        {
            if (more(2 * i, 2 * i + 1))
            {
                min = 2 * i + 1;
            }
            else
            {
                min = 2 * i;
            }
        }
        else
        {
            min = 2 * i;
        }
        if (more(i, min))
        {
            exchange(i, min);
            i = min;
        }
        else
        {
            break;
        }
    }
}
template <class T>
T minpriorityqueue<T>::delmin()
{
    T temp = head[1];
    exchange(1, n);
    head[n--] = NULL;
    sink(1);
    return temp;
}
int main()
{
    minpriorityqueue<char> minpriorityqueue1(10);
    minpriorityqueue1.insert('A');
    minpriorityqueue1.insert('B');
    minpriorityqueue1.insert('C');
    minpriorityqueue1.insert('D');
    minpriorityqueue1.insert('E');
    minpriorityqueue1.insert('F');
    minpriorityqueue1.insert('G');
    while (minpriorityqueue1.empty()!=true)
    {
        cout << minpriorityqueue1.delmin();
    }
    return 0;
}