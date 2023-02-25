//顺序队列(循环队列)(用下标实现访问元素)(带长度)
#include <iostream>
using namespace std;
template <class T>
class circlequeue
{
private:
    T *head;   //指向存储空间
    int front; //指向对头元素
    int rear;  //指向队尾元素的下一个位置
    int size;  //存储容量
    int length;
public:
    circlequeue(int s); //初始化存储空间
    ~circlequeue();
    int getsize();        //返回存储容量
    bool empty();         //判断是否为空
    bool full();          //判断是否为满
    void enqueue(T elem); //元素从尾入队
    T dequeue();          //元素从头出队
    void mycout();        //按队列要求输出元素
};
template <class T>
circlequeue<T>::circlequeue(int s)
{
    size = s;
    head = new T[size];
    front = 0;
    rear = 0;
    length=0;
}
template <class T>
circlequeue<T>::~circlequeue()
{
    delete[] head;
}
template <class T>
int circlequeue<T>::getsize()
{
    return size;
}
template <class T>
bool circlequeue<T>::empty()
{
    return length==0 ? true : false;
}
template <class T>
bool circlequeue<T>::full()
{
    return length==size-1?true:false;
}
template <class T>
void circlequeue<T>::enqueue(T elem)
{
    if (length==size-1)
    {
        cout << "the queue is full and you can't enqueue element any more" << endl;
    }
    else
    {
        head[rear] = elem;
        rear = (rear + 1) % size;
        length++;
    }
}
template <class T>
T circlequeue<T>::dequeue()
{
    if (length==0)
    {
        cout << "the queue is empty" << endl;
        return static_cast<T>(NULL);
    }
    else
    {
        int temp = front;
        front = (front + 1) % size;
        length--;
        return head[temp];
    }
}
template <class T>
void circlequeue<T>::mycout()
{
    if (length==0)
    {
        cout << "there is no element in the queue" << endl;
    }
    else
    {
        int temp = front;
        for(int i=0;i<length;i++)
        {
            cout << head[temp] << " ";
            temp = (temp + 1) % size;
        }
        cout << endl;
    }
}
int main()
{
    circlequeue<int> circlequeue1(10);
    cout << circlequeue1.getsize() << endl;
    cout << circlequeue1.empty() << endl;
    cout << circlequeue1.full() << endl;
    int a[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    for (int i = 0; i < 9; i++)
    {
        circlequeue1.enqueue(a[i]);
    }
    cout << circlequeue1.getsize() << endl;
    cout << circlequeue1.empty() << endl;
    cout << circlequeue1.full() << endl;
    circlequeue1.enqueue(10);
    circlequeue1.mycout();
    cout << circlequeue1.dequeue() << endl;
    cout << circlequeue1.full() << endl;
    circlequeue1.mycout();
    circlequeue1.enqueue(10);
    circlequeue1.mycout();
    return 0;
}