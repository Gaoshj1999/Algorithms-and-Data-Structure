//线性表(链式存储结构)(双向链表)
#include <iostream>
using namespace std;
template <class T>
class node
{
public:
    node<T> *next;
    node<T> *prior;
    T data;
};
template <class T>
class linklist
{
public:
    node<T> *head;                    //链表的头指针，指向头节点
    int size;                         //链表长度(不包括头节点)
    linklist();                       //初始化链表，头节点内数据为空，并指向指针
    ~linklist();                      //释放头节点
    int getsize();                    //获取链表长度
    node<T> *locate(int i);           //返回第i个节点的地址
    void insertbefore(int i, T elem); //在指定位置前插入一个元素
    void insertafter(int i, T elem);  //在指定位置后插入一个元素
    void create();                    //创建一个链表，依次插入元素
    void mydelete(int i);             //删除指定节点
    bool empty();                     //判断链表是否为空
    void mycout();                    //输出链表内所有节点的元素
};
template <class T>
linklist<T>::linklist()
{
    head = new node<T>;
    head->data = -1;
    head->next = nullptr;
    head->prior = nullptr; //这边不是一个空指针
    size = 0;
}
template <class T>
linklist<T>::~linklist()
{
    delete head;
}
template <class T>
int linklist<T>::getsize()
{
    return size;
}
template <class T>
node<T> *linklist<T>::locate(int i)
{
    node<T> *temp = head;
    for (int j = 0; j < i; j++)
    {
        temp = temp->next;
    }
    return temp;
}
template <class T>
void linklist<T>::insertbefore(int i, T elem)
{
    node<T> *newnode = new node<T>;
    newnode->data = elem;
    if (size == 0 && i == 1)
    {
        newnode->next = head->next;
        newnode->prior = head;
        head->next = newnode;
    }
    else if (i > size)
    {
        cout << "i is bigger than size" << endl;
    }
    else
    {
        node<T> *temp = locate(i);
        newnode->next = temp;
        newnode->prior = temp->prior;
        temp->prior->next = newnode;
        temp->prior = newnode;
    }
    size += 1;
}
template <class T>
void linklist<T>::insertafter(int i, T elem)
{
    node<T> *newnode = new node<T>;
    newnode->data = elem;
    if (size == 0 && i == 1)
    {
        newnode->next = head->next;
        newnode->prior = head;
        head->next = newnode;
    }
    else if (i > size)
    {
        cout << "i is bigger than size" << endl;
    }
    else if (i == size)
    {
        node<T> *temp = locate(i);
        newnode->next = temp->next;
        newnode->prior = temp;
        temp->next = newnode;
    }
    else
    {
        node<T> *temp = locate(i);
        newnode->next = temp->next;
        newnode->prior = temp;
        temp->next->prior = newnode;
        temp->next = newnode;
    }
    size += 1;
}
template <class T>
void linklist<T>::create()
{
    int i;
    cout << "please enter the size of the linklist you want to create" << endl;
    cin >> i;
    size = i;
    node<T> *temp = head;
    for (int j = 1; j <= i; j++)
    {
        int newdata;
        cout << "the data of the"
             << " " << j << " "
             << "node is:" << endl;
        cin >> newdata;
        node<T> *newnode = new node<T>;
        newnode->data = newdata;
        newnode->next = temp->next;
        newnode->prior = temp;
        temp->next = newnode;
        temp = newnode;
    }
}
template <class T>
void linklist<T>::mydelete(int i)
{
    if (size == 0)
    {
        cout << "the linklist is already empty" << endl;
    }
    else if (i > size)
    {
        cout << "there is no node" << endl;
    }
    else
    {
        node<T> *temp1 = locate(i - 1);
        node<T> *temp2 = locate(i);
        temp1->next = temp1->next->next;
        free(temp2);
    }
    size -= 1;
}
template <class T>
bool linklist<T>::empty()
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
void linklist<T>::mycout()
{
    node<T> *temp = head;
    for (int i = 0; i < size; i++)
    {
        cout << temp->next->data << " ";
        temp = temp->next;
    }
    cout << endl;
}
int main()
{
    linklist<int> linklist1;
    linklist<int> linklist2;
    cout << linklist1.empty() << endl;
    cout << linklist1.getsize() << endl;
    int a[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    for (int i = 0; i < 10; i++)
    {
        linklist1.insertafter(i, a[i]);
    }
    cout << linklist1.empty() << endl;
    cout << linklist1.getsize() << endl;
    linklist1.mycout();
    cout << linklist1.locate(3)->data << endl;
    linklist1.mydelete(4);
    linklist1.mycout();
    cout << linklist1.getsize() << endl;
    linklist1.insertafter(3, 4);
    linklist1.mycout();
    cout << linklist1.getsize() << endl;
    linklist1.insertbefore(1, 0);
    linklist1.mycout();
    cout << linklist1.getsize() << endl;
    linklist2.create();
    linklist2.mycout();
    cout << linklist2.getsize();
    return 0;
}
