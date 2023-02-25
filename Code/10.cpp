//通过栈进行数制转换
//除a取反序即可得a进制数
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
class stack
{
public:
    node<T> *head;     //链栈表的头指针，指向头节点
    int size;          //链栈长度(不包括头节点)
    stack();           //初始化链栈，头节点内数据为空，并指向指针
    ~stack();          //释放头节点
    int getsize();     //获取链表长度
    void push(T elem); //将元素压入栈
    T pop();           //将元素弹出栈
    T top();           //返回栈顶元素
    void create();     //创建一个链栈，按压入顺序依次插入元素
    bool empty();      //判断链栈是否为空
    void mycout();     //按弹出顺序输出链栈内所有节点的元素
};
template <class T>
stack<T>::stack()
{
    head = new node<T>;
    head->data = -1;
    head->next = nullptr;
    size = 0;
}
template <class T>
stack<T>::~stack()
{
    delete head;
}
template <class T>
int stack<T>::getsize()
{
    return size;
}
template <class T>
void stack<T>::push(T elem)
{
    node<T> *newnode = new node<T>;
    newnode->data = elem;
    newnode->next = head->next;
    head->next = newnode;
    size++;
}
template <class T>
T stack<T>::pop()
{
    if (head->next == nullptr)
    {
        cout << "there is no element in the stack" << endl;
        return static_cast<T>(NULL);
    }
    else
    {
        node<T> *temp = head->next;
        head->next = head->next->next;
        size--;
        return temp->data;
    }
}
template <class T>
T stack<T>::top()
{
    if (head->next == nullptr)
    {
        cout << "there is no element in the stack" << endl;
        return static_cast<T>(NULL);
    }
    else
    {
        return head->next->data;
    }
}
template <class T>
void stack<T>::create()
{
    int i;
    cout << "please enter the size of the stack you want to create" << endl;
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
        temp->next = newnode;
        temp = newnode;
    }
}
template <class T>
bool stack<T>::empty()
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
void stack<T>::mycout()
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
    stack<int> stack1;
    int a;
    int i;
    cout << "请输入数字" << endl;
    cin >> a;
    cout << "请输入想要转换几进制的数(不允许超过十进制)" << endl;
    cin >> i;
    while (a != 0)
    {
        stack1.push(a % i); //取余
        a /= i;             //取商
    }
    stack1.mycout();
    return 0;
}