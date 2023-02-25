//最短路径Dijkstra算法(加权无向图)(加权有向图算法不需要改变)
//求一个顶点到其他顶点的最短路径的时间复杂度为O(v^2)
//求所有顶点到其他顶点的最短路径的时间复杂度为O(v^3)(每个顶点作为起点)
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
    int weight;
    adjvertex();
};
adjvertex::adjvertex()
{
    adjvex = NULL;
    nextadj = nullptr;
    weight = 0;
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
        int tempweight;
        cout << "please enter the name of two vertex" << endl;
        cin >> t1 >> t2;
        cout << "please enter the weight of the arc" << endl;
        cin >> tempweight;
        i = locate(t1);
        j = locate(t2);
        adjvertex *temp = new adjvertex;
        temp->adjvex = j;
        temp->nextadj = vex[i].firstadj;
        temp->weight = tempweight;
        vex[i].firstadj = temp;
        adjvertex *temp2 = new adjvertex;
        temp2->adjvex = i;
        temp2->nextadj = vex[j].firstadj;
        temp2->weight = tempweight;
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
class Dijkstrasp
{
public:
    graph<T> graphforpath;
    T start;
    int *distto;     //索引代表顶点，值代表从顶点s到当前顶点的最短路径的总权重
    T *edgeto;       //索引代表顶点，值代表从起点到当前顶点路径上的最后一个顶点
    int *recentpath; //索引代表顶点，值代表当前所有可达边的权重
    Dijkstrasp(graph<T> tempgraph, T s);
    void relax(T v);       //放松节点v
    int disttovertex(T v); //返回到节点v的最短路径的权重
    bool haspathto(T v);   //判断当前节点是否可达
    void pathto(T v);      //查询从顶点s到顶点v的最短路径中的所有边
};
template <class T>
Dijkstrasp<T>::Dijkstrasp(graph<T> tempgraph, T s)
{
    start = s;
    graphforpath = tempgraph;
    edgeto = new T[graphforpath.vexsize];
    distto = new int[graphforpath.vexsize];
    recentpath = new int[graphforpath.vexsize];
    for (int i = 0; i < graphforpath.vexsize; i++)
    {
        distto[i] = INT_MAX;
        recentpath[i] = INT_MAX;
        edgeto[i] = NULL;
    }
    //默认让顶点start为起点的最短路径树
    T nextvisit = start;
    distto[graphforpath.locate(start)] = 0;
    recentpath[graphforpath.locate(start)] = 0;
    relax(start);
    for (int i = 0; i < graphforpath.vexsize - 1; i++)
    {
        T nearistvertex;
        int n = INT_MAX;
        for (int i = 0; i < graphforpath.vexsize; i++)
        {
            if (recentpath[i] > 0 && recentpath[i] < n)
            {
                n = recentpath[i];
                nearistvertex = graphforpath.vex[i].data;
            }
        }
        recentpath[graphforpath.locate(nearistvertex)] = INT_MAX;
        relax(nearistvertex);
    }
}
template <class T>
void Dijkstrasp<T>::relax(T v)
{
    for (adjvertex *w = graphforpath.vex[graphforpath.locate(v)].firstadj; w; w = w->nextadj)
    {
        //获取该边的终点w
        if (distto[graphforpath.locate(v)] + w->weight < distto[w->adjvex])
        {
            distto[w->adjvex] = distto[graphforpath.locate(v)] + w->weight;
            recentpath[w->adjvex] = distto[graphforpath.locate(v)] + w->weight;
            edgeto[w->adjvex] = graphforpath.vex[graphforpath.locate(v)].data;
        }
    }
}
template <class T>
int Dijkstrasp<T>::disttovertex(T v)
{
    return distto[graphforpath.locate(v)];
}
template <class T>
bool Dijkstrasp<T>::haspathto(T v)
{
    return distto[graphforpath.locate(v)] < INT_MAX ? true : false;
}
template <class T>
void Dijkstrasp<T>::pathto(T v)
{
    if (!haspathto(v))
    {
        cout << "no path" << endl;
    }
    stack<T> tempstack;
    tempstack.push(v);
    T previousvertex = edgeto[graphforpath.locate(v)];
    while (previousvertex != NULL)
    {
        tempstack.push(previousvertex);
        previousvertex = edgeto[graphforpath.locate(previousvertex)];
    }
    while (!tempstack.empty())
    {
        cout << tempstack.pop() << " ";
    }
}
int main()
{
    graph<char> graph1;
    graph1.create(7,13);
    Dijkstrasp<char> dijkstrasp1(graph1, 'c');
    dijkstrasp1.pathto('g');
    return 0;
}