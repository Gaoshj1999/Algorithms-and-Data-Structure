//无向图路径查找(基于DFS实现)
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
const int maxsize = 20; //节点的最大数
class adjvertex         //弧
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
class DFSpath
{
public:
    graph<T> graphforpath;
    bool *mark;                                                       //标记当前顶点是否已经被搜索过
    T start;                                                          //标记起点
    int *edgeto;                                                      //索引代表顶点，值代表从起点到当前顶点路径上的最后一个顶点
    DFSpath(graph<T> graphforpath, T start);                          //传入图以及搜索的起点
    void DFS(graph<T> &tempgraph, bool visited[], int edge[], int v); //单个顶点的深度优先遍历
    bool haspathto(T end);                                            //判断与start是否有路径
    void pathto(T end);                                               //输出从start到end的路径
};
template <class T>
DFSpath<T>::DFSpath(graph<T> tempgraphforpath, T start)
{
    graphforpath = tempgraphforpath;
    this->start = start;
    mark = new bool[graphforpath.vexsize];
    edgeto = new int[graphforpath.vexsize];
    for (int i = 0; i < graphforpath.vexsize; i++)
    {
        mark[i] = false;
    }
    DFS(graphforpath, mark, edgeto, graphforpath.locate(start));
}
template <class T>
void DFSpath<T>::DFS(graph<T> &tempgraph, bool visited[], int edge[], int v)
{
    visited[v] = true;
    for (adjvertex *w = tempgraph.vex[v].firstadj; w; w = w->nextadj)
    {
        if (!visited[w->adjvex])
        {
            edgeto[w->adjvex] = v;
            DFS(tempgraph, visited, edgeto, w->adjvex);
        }
    }
}
template <class T>
bool DFSpath<T>::haspathto(T end)
{
    return mark[graphforpath.locate(end)];
}
template <class T>
void DFSpath<T>::pathto(T end)
{
    if (haspathto(end))
    {
        stack<T> tempstack;
        for (int x = graphforpath.locate(end); x != graphforpath.locate(start); x = edgeto[x])
        {
            tempstack.push(graphforpath.vex[x].data);
        }
        tempstack.push(graphforpath.vex[graphforpath.locate(start)].data);
        for (T temp; !tempstack.empty();)
        {
            temp = tempstack.pop();
            cout << temp;
            if (!tempstack.empty())
            {
                cout<< "-->";
            }
        }
    }
}
int main()
{
    graph<char> graph1;
    graph1.create(9,12);
    DFSpath<char> DFSpath(graph1, 'a');
    DFSpath.pathto('i');
    return 0;
}