//线性表(顺序存储)
#include <iostream>
#include <cassert>
using namespace std;
template <class T>
class list
{
private:
    T *head;    //指向存储空间
    int length; //长度
    int size;   //存储容量
public:
    list(int s);
    ~list();
    bool empty();               //判断数组是否为空
    bool full();                //判断数组是否为满
    int getlength();            //获取数组长度
    int getsize();              //获取内存长度
    int exist(T elem);          //判断数组内是否有该元素,有则返回第一个出现位置，无则返回-1
    T getelem(int i);           //获取第i个元素
    T getelemfront(int i);      //获取i个元素的前一个元素，若为第一个元素则返回-1
    T getelemnext(int i);       //获取i个元素的下一个元素,若为最后一个元素则返回-1
    void insert(int i, T elem); //在第i个位置插入元素,如果内存不足则申请翻倍内存
    void mydelete(int i);       //删除第i个位置的元素
    void mycout();              //输出所有元素
};
template <class T>
list<T>::list(int s)
{
    size = s;           //初始化容量为s
    head = new T[size]; //申请容量为s的数组
    length = 0;         //初始化长度为0
}
template <class T>
list<T>::~list()
{
    delete[] head; //释放动态内存
    head = NULL;
}
template <class T>
bool list<T>::empty()
{
    if (length == 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}
template <class T>
bool list<T>::full()
{
    if (length == size)
    {
        return true;
    }
    else
    {
        return false;
    }
}
template <class T>
int list<T>::getlength()
{
    return length;
}
template <class T>
int list<T>::getsize()
{
    return size;
}
template <class T>
int list<T>::exist(T elem)
{
    for (int i = 0; i < length; i++)
    {
        if (head[i] == elem)
        {
            return i + 1;
        }
    }
    return -1;
}
template <class T>
T list<T>::getelem(int i)
{
    return head[i-1];
}
template <class T>
T list<T>::getelemfront(int i)
{
    if (i == 1)
    {
        cout << "this is the first element" << endl;
        return -1;
    }
    else
    {
        return head[i - 2];
    }
}
template <class T>
T list<T>::getelemnext(int i)
{
    if (i == length)
    {
        cout << "this is the last element" << endl;
        return -1;
    }
    else
    {
        return head[i];
    }
}
template <class T>
void list<T>::insert(int i, T elem)
{
    if (length == size)
    {
        T *a=new T[size];
        for (int j = 0; j < length; j++)
        {
            a[j] = head[j];
        }
        delete[] head;
        head = new T[2 * size];
        for (int j = 0; j < length; j++)
        {
            head[j] = a[j];
        }
        size *= 2;
        delete[] a;
    }
    for (int n = length; n >= i - 1; n--)
    {
        head[n] = head[n-1];
    }
    head[i - 1] = elem;
    length++;
}
template <class T>
void list<T>::mydelete(int i)
{
    for (int j = i - 1; j < length; j++)
    {
        head[j] = head[j + 1];
    }
    length--;
}
template <class T>
void list<T>::mycout()
{
    for (int i = 0; i < length; i++)
    {
        cout << head[i] << " ";
    }
    cout << endl;
}
int main()
{
    list<int> list1(10);
    list<int> list2(5);
    int a[] = {1, 2, 3, 4, 5};
    cout << list1.empty() << endl;
    cout << list1.full() << endl;
    for (int i = 1; i <= 10; i++)
    {
        list1.insert(i, i);
    }
    list1.mycout();
    cout << list1.getlength() << endl;
    cout << list1.getsize() << endl;
    cout << list1.empty() << endl;
    cout << list1.full() << endl;
    list1.mydelete(9);
    list1.mycout();
    cout << list1.getelem(2) << endl;
    cout << list1.getelemfront(2) << endl;
    cout << list1.getelemfront(1) << endl;
    cout << list1.getelemnext(2) << endl;
    cout << list1.getelemnext(9) << endl;
    list1.insert(2, 2);
    list1.mycout();
    cout << list1.exist(9) << endl;
    cout << list1.exist(3) << endl;
    for (int i = 1; i <= 5; i++)
    {
        list2.insert(i, a[i - 1]);
    }
    list2.mycout();
    list2.insert(6, 6);
    list2.mycout();
    cout << list2.getsize() << endl;
    cout << list2.getlength();
    return 0;
}
