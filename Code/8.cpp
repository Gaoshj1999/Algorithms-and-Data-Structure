//顺序栈
#include <iostream>
using namespace std;
template <class T>
class stack
{
private:
    T *base;    //指向存储空间
    T *top;     //指向栈顶的下一个元素,这里默认存储空间最后一个位置不能放元素，如果length==size-1，则认为为满
    int size;   //存储空间大小
    int length; //长度
public:
    stack(int s);      //初始化存储空间为s
    stack();           //初始化内存空间为1
    ~stack();          //析构栈
    bool empty();      //判断栈是否为空
    bool full();       //判断栈是否为满
    int mysize();      //返回当前内存大小
    int mylength();    //返回当前长度
    void push(T data); //将顶部元素压入栈
    T pop();           //将顶部元素弹出栈
    void create();     //创建一个栈，并按压入顺序读入数据
    void mycout();     //按弹出栈顺序输出所有元素
    T mytop();         //返回栈顶元素
};
template <class T>
stack<T>::stack(int s)
{
    base = new T[s];
    size = s;
    top = base;
    length = 0;
}
template <class T>
stack<T>::stack()
{
    base = new T;
    size = 1;
    top = base;
    length = 0;
}
template <class T>
stack<T>::~stack()
{
    delete[] base;
}
template <class T>
bool stack<T>::empty()
{
    return length == 0 ? true : false;
}
template <class T>
bool stack<T>::full()
{
    return length == size - 1 ? true : false;
}
template <class T>
int stack<T>::mysize()
{
    return size;
}
template <class T>
int stack<T>::mylength()
{
    return length;
}
template <class T>
void stack<T>::push(T data)
{
    if (length == size - 1)
    {
        T *temp = new T[size];
        for (int i = 0; i < size; i++)
        {
            temp[i] = base[i];
        }
        delete[] base;
        base = new T[2 * size];
        top = base;
        for (int i = 0; i < size; i++)
        {
            base[i] = temp[i];
            top++;
        }
        size *= 2;
    }
    *top++ = data;
    length++;
}
template <class T>
T stack<T>::pop()
{
    if (length == 0)
    {
        cout << "there is no element in the stack";
        return static_cast<T>(NULL);
    }
    else
    {
        top--;
        length--;
        return *top;
    }
}
template <class T>
void stack<T>::create()
{
    int i;
    cout << "please enter the size of the stack you want to create" << endl;
    cin >> i;
    while (i >= size)
    {
        size *= 2;
        delete[] base;
        base = new T[size];
    }
    top = base + i;
    length += i;
    for (int j = 0; j < i; j++)
    {
        cout << "please enter the"
             << " " << j + 1 << " "
             << "element" << endl;
        cin >> base[j];
    }
}
template <class T>
void stack<T>::mycout()
{
    if (length == 0)
    {
        cout << "there is no element in the stack" << endl;
    }
    else
    {
        for (int i = length - 1; i >= 0; i--)
        {
            cout << base[i] << " ";
        }
        cout << endl;
    }
}
template <class T>
T stack<T>::mytop()
{
    return *(top - 1);
}
int main()
{
    stack<int> stack1(5);
    stack<int> stack2;
    int a[] = {1, 2, 3, 4};
    for (int i = 0; i < 4; i++)
    {
        stack1.push(a[i]);
    }
    stack1.mycout();
    cout << stack1.mytop() << endl;
    cout << stack1.mysize() << endl;
    cout << stack1.mylength() << endl;
    cout << stack1.full() << endl;
    cout << stack1.pop() << endl;
    cout << stack1.mytop() << endl;
    cout << stack1.mysize() << endl;
    cout << stack1.mylength() << endl;
    stack1.push(4);
    stack1.push(5);
    cout << stack1.mylength() << endl;
    cout << stack1.mysize() << endl;
    cout << stack2.empty() << endl;
    stack2.create();
    stack2.mycout();
    cout << stack2.mylength() << endl;
    cout << stack2.mysize() << endl;
    return 0;
}
