//优先队列(最大优先队列)maxpriorityqueue+(基于最大堆实现)
//优先队列就是堆的应用，说白了就是堆
#include <iostream>
using namespace std;
template <class T>
class maxpriorityqueue
{
private:
    T *head;
    int n; //数组元素个数
public:
    maxpriorityqueue(int s);
    ~maxpriorityqueue() {}
    bool empty();                //判断队列是否为空
    bool less(int i, int j);     //判断索引i处元素是否小于j处
    void exchange(int i, int j); //交换i和j处的元素
    void insert(T elem);         //插入一个元素
    void swim(int i);            //通过上浮使i处的元素能处于正确的位置并使队列的逻辑正确
    T delmax();                  //删除堆中最大的元素,并返回删除的最大元素
    void sink(int i);            //通过下沉使i处元素能处于正确的位置并使队列的逻辑正确
};
template <class T>
maxpriorityqueue<T>::maxpriorityqueue(int s)
{
    head = new T[s + 1]; //和堆一致即头不放数据
    n = 0;
}
template <class T>
bool maxpriorityqueue<T>::empty()
{
    return n == 0 ? true : false;
}
template <class T>
bool maxpriorityqueue<T>::less(int i, int j)
{
    return head[i] < head[j] ? true : false;
}
template <class T>
void maxpriorityqueue<T>::exchange(int i, int j)
{
    T temp = head[i];
    head[i] = head[j];
    head[j] = temp;
}
template <class T>
void maxpriorityqueue<T>::swim(int i) //通过循环比较当前节点和其父节点的值如果父节点小于则交换
{
    while (less(i / 2, i) && i > 1)
    {
        exchange(i, i / 2);
        i /= 2;
    }
}
template <class T>
void maxpriorityqueue<T>::insert(T data)
{
    head[++n] = data; //元素个数自增1然后在该位置插入新元素
    swim(n);
}
template <class T>
void maxpriorityqueue<T>::sink(int i) //通过循环比较当前节点和其子节点的值如果小于则与较大节点交换
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
T maxpriorityqueue<T>::delmax()
{
    T temp = head[1];
    exchange(1, n);
    head[n--] = NULL;
    sink(1);
    return temp;
}
int main()
{
    maxpriorityqueue<char> maxpriorityqueue1(10);
    maxpriorityqueue1.insert('A');
    maxpriorityqueue1.insert('B');
    maxpriorityqueue1.insert('C');
    maxpriorityqueue1.insert('D');
    maxpriorityqueue1.insert('E');
    maxpriorityqueue1.insert('F');
    maxpriorityqueue1.insert('G');
    while (maxpriorityqueue1.empty()!=true)
    {
        cout << maxpriorityqueue1.delmax();
    }
    return 0;
}