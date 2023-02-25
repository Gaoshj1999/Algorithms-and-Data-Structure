//线性表(链式存储结构)(单链表网上例子)
#include <iostream>
using namespace std;
template <class T>
struct LinkNode
{
    T data;         //数据域
    LinkNode *link; //虽然我觉习惯next了，但好像书上都是link，那就link吧..
    LinkNode(LinkNode<T> *ptr = NULL)
    {
        link = ptr; //创建一个结点，默认其指针域指向空
    }               //没有data的构造函数->其实就是头结点
    LinkNode(const T &item, LinkNode<T> *ptr = NULL)
    {
        data = item;
        link = ptr;
    } //有data的构造函数
};

template <class T>
class List
{
protected:
    LinkNode<T> *first; //链表的头指针，指向头结点。
public:
    List() { first = new LinkNode<T>; }

    List(const T &x) { first = new LinkNode<T>(x); } //两个构造函数

    List(List<T> &L); //拷贝构造函数

    ~List() { Make_empty(); } //析构函数

    void Make_empty(); //将链表删除

    int Length(); //求链表长度

    LinkNode<T> *Get_head() { return first; } //返回头指针

    bool Is_empty() { return first->link == NULL ? true : false; } //判断链表是否为空

    LinkNode<T> *Locate(int i); //搜索第i个元素的地址

    bool Get_data(int i, T &x); //取出第i个元素的数据

    bool Insert(int i, T &x); //在第i个结点前插入x，使其成为第i个结点

    bool Remove(int i, T &x); //删除第i个结点，并用x返回其数据

    void Input(); //尾插法输入链表元素

    void Output(); //将链表元素输出

    void Sort(); //对链表排序 其实只要交换数据域就可以啦

    List<T> &operator=(List<T> &L); //重载=，和拷贝构造函数一样
};
template <class T>
List<T>::List(List<T> &L)
{
    T value;
    LinkNode<T> *p1 = first = new LinkNode<T>;
    LinkNode<T> *p2 = L.Get_head();
    while (p2->link != NULL)
    {
        value = p2->link->data;
        p1->link = new LinkNode<T>(value);
        p1 = p1->link;
        p2 = p2->link;
    }
    p1->link = NULL; //创建完毕，链表最后一个结点指针域为空
}

template <class T>
void List<T>::Make_empty()
{
    LinkNode<T> *p;
    while (first->link != NULL)
    {
        p = first->link;
        first->link = first->link->link;
        delete p;
    }
}

template <class T>
int List<T>::Length()
{
    int cnt = 0;
    LinkNode<T> *p = first->link;
    while (p != NULL)
    {
        cnt++;
        p = p->link;
    }
    return cnt;
}

template <class T>
LinkNode<T> *List<T>::Locate(int i)
{
    if (i < 0)
        return NULL;
    else
    {
        LinkNode<T> *p = first;
        int k = 0;
        while (k != i && p != NULL)
        {
            p = p->link;
            k++;
        }
        return p;
    }
}

template <class T>
bool List<T>::Get_data(int i, T &x)
{
    LinkNode<T> *p = Locate(i);
    if (p = NULL) //因为locate（i）直接定位，如果i太小或太大都返回的是NULL
    {
        cout << "所给i数据有误" << endl;
        return false;
    }
    else
    {
        x = p->data;
        return true;
    }
}

template <class T>
bool List<T>::Insert(int i, T &x)
{
    LinkNode<T> *p = Locate(i - 1);
    if (p == NULL)
    {
        cout << "插入失败，所给i数据有误" << endl;
        return false;
    }
    else
    {
        LinkNode<T> *NewNode = new LinkNode<T>(x);
        NewNode->link = p->link;
        p->link = NewNode;
        return true;
    }
}

template <class T>
bool List<T>::Remove(int i, T &x)
{
    LinkNode<T> *p = Locate(i - 1);
    if (p == NULL || p->link == NULL)
    {
        cout << "删除失败，所给i数据有误" << endl;
        return false;
    }
    else
    {
        LinkNode<T> *del = p->link;
        p->link = p->link->link;
        delete del;
    }
}

template <class T>
void List<T>::Input()
{

    Make_empty(); //清空链表
    cout << "请输入你想创造链表的元素个数" << endl;
    int len;
    cin >> len;
    LinkNode<T> *newnode, *last;
    T value;
    last = first;
    while (Length() < len)
    {
        cout << "请输入第" << Length() + 1 << "个结点的值：" << endl; //创建完length才会++
        cin >> value;
        newnode = new LinkNode<T>(value);
        last->link = newnode;
        last = newnode;
    }
    last->link = NULL;
}

template <class T>
void List<T>::Output()
{
    LinkNode<T> *p = first->link;
    while (p != NULL)
    {
        cout << p->data << " ";
        p = p->link;
    }
    cout << endl;
}

template <class T>
void List<T>::Sort()
{
    int len = Length();
    int i, j;
    T x;
    LinkNode<T> *p;
    LinkNode<T> *q;
    for (i = 0, p = first->link; i < len - 1; ++i, p = p->link)
    {
        for (j = i + 1, q = p->link; j < len; ++j, q = q->link)
        {
            if (p->data > q->data) //类似于数组中的:  a[i] > a[j]
            {
                x = p->data;       //类似于数组中的:  x = a[i];
                p->data = q->data; //类似于数组中的:  a[i] = a[j];
                q->data = x;       //类似于数组中的:  a[j] = x;
            }
        }
    }
}

template <class T>
List<T> &List<T>::operator=(List<T> &L) //实现与拷贝构造函数一致
{
    T value;
    LinkNode<T> *p1 = first = new LinkNode<T>;
    LinkNode<T> *p2 = L.Get_head();
    while (p2->link != NULL)
    {
        value = p2->link->data;
        p1->link = new LinkNode<T>(value);
        p1 = p1->link;
        p2 = p2->link;
    }
    p1->link = NULL;
    return *this;
}
int main()
{
    List<int> l1;
    l1.Input();
    l1.Output();
    l1.Sort();
    List<int> l2;
    l2 = l1;
    l2.Output();
    List<char> l3;
    l3.Input();
    l3.Output();
    l3.Sort();
    List<char> l4(l3);
    l4.Output();
}