//链式队列
#include <iostream>
using namespace std;
template <class T>
class node
{
public:
    node<T> *next;
    T data;
};
template <class T>
class queue
{
public:
    node<T> *front;       //链式队列的头指针，指向头节点
    node<T> *rear;        //链式队列的尾指针，指向尾节点
    int size;             //链表长度(不包括头节点)
    queue();              //初始化链式队列，头节点内数据为空，并指向指针
    ~queue();             //释放头节点和尾节点
    int getsize();        //获取链式队列长度
    void enqueue(T elem); //元素从尾入队
    T dequeue();          //元素从头出队
    void create();        //创建一个链表，依次插入元素
    bool empty();         //判断链式队列是否为空
    void mycout();        //输出链式队列内所有节点的元素
};
template <class T>
queue<T>::queue()
{
    front = new node<T>;
    front->data = NULL;
    front->next = nullptr;
    rear = front;
    size = 0;
}
template <class T>
queue<T>::~queue()
{
    delete front;
}
template <class T>
int queue<T>::getsize()
{
    return size;
}
template <class T>
void queue<T>::enqueue(T elem)
{
    node<T> *newnode = new node<T>;
    newnode->data = elem;
    newnode->next = rear->next;
    rear->next = newnode;
    rear = newnode;
    size++;
}
template <class T>
T queue<T>::dequeue()
{
    if (size == 0)
    {
        cout << "there is no element in the queue" << endl;
        return static_cast<T>(NULL);
    }
    else
    {
        node<T> *temp1 = front->next;
        if (front->next->next != nullptr)
        {
            front->next = front->next->next;
        }
        else
        {
            front->next = front->next->next;
            rear = front; //这里如果不对rear重新赋值的话,rear就丢失了,这会在如果队列在执行程序时出现过无元素的情况就会出问题
        }
        size--;
        return temp1->data;
    }
}
template <class T>
void queue<T>::create()
{
    int i;
    cout << "please enter the size of the linklist you want to create" << endl;
    cin >> i;
    size = i;
    for (int j = 0; j < size; j++)
    {
        node<T> *newnode = new node<T>;
        int newdata;
        cout << "the data of the"
             << " " << j << " "
             << "node is:" << endl;
        cin >> newdata;
        newnode->data = newdata;
        newnode->next = rear->next;
        rear->next = newnode;
        rear = newnode;
    }
}
template <class T>
bool queue<T>::empty()
{
    if (size == 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}
template <class T>
void queue<T>::mycout()
{
    node<T> *temp = front;
    for (int i = 0; i < size; i++)
    {
        cout << temp->next->data << " ";
        temp = temp->next;
    }
    cout << endl;
}
int main()
{
    queue<int> queue1;
    queue<int> queue2;
    queue<int> queue3;
    cout << queue1.empty() << endl;
    cout << queue1.getsize() << endl;
    queue1.dequeue();
    int a[] = {1, 2, 3, 4, 5};
    for (int i = 0; i < 5; i++)
    {
        queue1.enqueue(a[i]);
    }
    cout << queue1.empty() << endl;
    cout << queue1.getsize() << endl;
    queue1.mycout();
    cout << queue1.dequeue() << endl;
    cout << queue1.getsize() << endl;
    queue2.create();
    queue2.mycout();
    cout << queue2.getsize() << endl;
    cout << queue2.dequeue() << endl;
    cout << queue2.getsize() << endl;
    queue3.enqueue(1);
    cout << queue3.dequeue();
    return 0;
}
