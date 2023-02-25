//二叉树(用栈实现遍历)+(用队列实现层次遍历)（层次遍历的拓展其实就是图的广度搜索)
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
    head->data = NULL;
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
            rear = front;
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
template <class T>
class bitreenode
{
public:
    T data;
    bitreenode<T> *leftchild, *rightchild;
    bitreenode();
    ~bitreenode() {}
};
template <class T>
bitreenode<T>::bitreenode()
{
    data = NULL;
    leftchild = nullptr;
    rightchild = nullptr;
}
template <class T>
void insert(bitreenode<T> &tree, T elem) //按大小(左中右)插入数据
{
    bitreenode<T> *temp = &tree;
    bitreenode<T> *beforetemp;
    if (temp->data == NULL)
    {
        temp->data = elem;
    }
    else
    {
        while (temp != nullptr)
        {
            if (elem <= temp->data)
            {
                beforetemp = temp;
                temp = temp->leftchild;
            }
            else
            {
                beforetemp = temp;
                temp = temp->rightchild;
            }
        }
        if (beforetemp->data >= elem)
        {
            beforetemp->leftchild = new bitreenode<T>;
            beforetemp->leftchild->data = elem;
        }
        else
        {
            beforetemp->rightchild = new bitreenode<T>;
            beforetemp->rightchild->data = elem;
        }
    }
}
template <class T>
void create(bitreenode<T> &tree, T *array, int n) //按大小创建树
{
    for (int i = 0; i < n; i++)
    {
        insert(tree, array[i]);
    }
}
template <class T>
void inordertraverse(bitreenode<T> *tree) //用栈实现中序遍历并输出每个点的值
{
    stack<bitreenode<T> *> tempstack; //记得这里的栈不是T类型了
    bitreenode<T> *temp = tree;
    while (temp || tempstack.empty() != true)
    {
        if (temp)
        {
            tempstack.push(temp); //这里实际入栈的其实是指针
            temp = temp->leftchild;
        }
        else
        {
            temp = tempstack.pop();
            cout << temp->data << " ";
            temp = temp->rightchild;
        }
    }
}
template <class T>
void preordertraverse(bitreenode<T> *tree) //用栈实现先序遍历并输出每个点的值
{
    stack<bitreenode<T> *> tempstack; //记得这里的栈不是T类型了
    bitreenode<T> *temp = tree;
    while (temp || tempstack.empty() != true)
    {
        if (temp)
        {
            cout << temp->data << " ";
            tempstack.push(temp); //这里实际入栈的其实是指针
            temp = temp->leftchild;
        }
        else
        {
            temp = tempstack.pop();
            temp = temp->rightchild;
        }
    }
}
template <class T>
void postordertraverse(bitreenode<T> *tree) //用栈实现先序遍历并输出每个点的值
{
    stack<bitreenode<T> *> tempstack; //记得这里的栈不是T类型了
    bitreenode<T> *temp = tree;
    bitreenode<T> *p = nullptr;
    while (temp || tempstack.empty() != true)
    {
        if (temp)
        {
            tempstack.push(temp); //这里实际入栈的其实是指针
            temp = temp->leftchild;
        }
        else
        {
            temp = tempstack.top();                        //读取栈顶元素，非出栈
            if (temp->rightchild && temp->rightchild != p) //如果右子树存在且未被访问过
            {
                temp = temp->rightchild;
                tempstack.push(temp);
                temp = temp->leftchild;
            }
            else
            {
                temp = tempstack.pop();
                cout << temp->data << " ";
                p = temp;
                temp = nullptr;
            }
        }
    }
}
template <class T>
void leveltraverse(bitreenode<T> *tree) //队列层次遍历
{
    bitreenode<T> *temp = tree;
    queue<bitreenode<T> *> tempqueue;
    tempqueue.enqueue(tree);
    while (tempqueue.empty() != true)
    {
        temp = tempqueue.dequeue();
        cout << temp->data << " ";
        if (temp->leftchild != nullptr)
        {
            tempqueue.enqueue(temp->leftchild);
        }
        if (temp->rightchild != nullptr)
        {
            tempqueue.enqueue(temp->rightchild);
        }
    }
}
int main()
{
    bitreenode<int> tree1;
    int a[] = {4, 1, 2, 3, 5, 6, 7, 8};
    create(tree1, a, 8);
    inordertraverse(&tree1);
    cout << endl;
    preordertraverse(&tree1);
    cout << endl;
    postordertraverse(&tree1);
    cout << endl;
    leveltraverse(&tree1);
    cout << endl;
    return 0;
}
