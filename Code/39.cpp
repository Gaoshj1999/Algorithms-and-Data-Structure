//图的存储结构(邻接表，一种链式存储结构)(有无向图均适用)(此处为无向图)
//包括DFS和BFS的实现
#include <iostream>
using namespace std;
const int maxsize = 20; //节点的最大数
template<class T>
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
class adjvertex //弧
{
public:
    int adjvex;         //邻接点的下标
    adjvertex *nextadj; //指向下一个节点
    adjvertex();
};
adjvertex::adjvertex()
{
    adjvex = NULL;
    nextadj = nullptr;
}
template <class T>
class vertex
{
public:
    T data;
    adjvertex *firstadj;
    vertex();
};
template <class T>
vertex<T>::vertex()
{
    firstadj = nullptr;
    data = NULL;
}
template <class T>
class graph
{
public:
    vertex<T> vex[maxsize];
    int vexsize, arcsize;
    graph();
    ~graph() {}
    void create(int vexsize, int arcsize); //构造一张图(无向图)
    int locate(T data);                    //找到该顶点的编号
    void DFStraverse();                    //深度优先遍历
    void DFS(bool visited[], int v);       //单个点的完全遍历
    void BFStraverse();                    //广度优先遍历
};
template <class T>
graph<T>::graph()
{
    vexsize = 0;
    arcsize = 0;
}
template <class T>
int graph<T>::locate(T data)
{
    for (int i = 0; i < vexsize; i++)
    {
        if (vex[i].data == data)
        {
            return i;
        }
    }
    return NULL;
}
template <class T>
void graph<T>::create(int vexsize, int arcsize)
{
    this->vexsize = vexsize;
    this->arcsize = arcsize;
    cout << "please enter the vertex" << endl;
    for (int i = 0; i < vexsize; i++)
    {
        cin >> vex[i].data;
        vex[i].firstadj = nullptr;
    }
    for (int n = 0; n < arcsize; n++) //无向图两个节点背后均要插入
    {
        T t1, t2;
        int i, j;
        cout << "please enter the name of two vertex" << endl;
        cin >> t1 >> t2;
        i = locate(t1);
        j = locate(t2);
        adjvertex *temp = new adjvertex;
        temp->adjvex = j;
        temp->nextadj = vex[i].firstadj;
        vex[i].firstadj = temp;
        adjvertex *temp2 = new adjvertex;
        temp2->adjvex = i;
        temp2->nextadj = vex[j].firstadj;
        vex[j].firstadj = temp2;
    }
}
template <class T>
void graph<T>::DFS(bool visited[], int v)
{
    visited[v] = true;
    cout << vex[v].data << " ";
    for (adjvertex *w = vex[v].firstadj; w; w = w->nextadj)
    {
        if (!visited[w->adjvex])
        {
            DFS(visited, w->adjvex);
        }
    }
}
template <class T>
void graph<T>::DFStraverse()
{
    bool visited[vexsize];
    for (int i = 0; i < vexsize; i++)
    {
        visited[i] = false;
    }
    for (int i = 0; i < vexsize; i++)
    {
        if (!visited[i])
        {
            DFS(visited, i);
        }
    }
}
template <class T>
void graph<T>::BFStraverse()
{
    bool visited[vexsize];
    queue<int> tempqueue;
    for (int i = 0; i < vexsize; i++)
    {
        visited[i] = false;
    }
    for (int i = 0; i < vexsize; i++)
    {
        if (!visited[i])
        {
            visited[i] = true;
            cout << vex[i].data << " ";
            tempqueue.enqueue(i);
            while (!tempqueue.empty())
            {
                int temp = tempqueue.dequeue();
                for (adjvertex *w = vex[temp].firstadj; w; w = w->nextadj)
                {
                    if (!visited[w->adjvex])
                    {
                        visited[w->adjvex] = true;
                        cout << vex[w->adjvex].data << " ";
                        tempqueue.enqueue(w->adjvex);
                    }
                }
            }
        }
    }
}
int main()
{
    graph<char> graph1;
    graph1.create(6, 5);
    graph1.BFStraverse();
    return 0;
}