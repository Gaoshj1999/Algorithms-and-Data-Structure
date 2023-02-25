//关键路径(基于拓扑排序)(有向有权图)
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
    int adjvex; //邻接点的下标
    int weight;
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
    int *invertex; //记录每个点的入度
    int vexsize, arcsize;
    graph();
    ~graph() {}
    void create(int vexsize, int arcsize); //构造一张图
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
    invertex = new int[vexsize];
    for (int i = 0; i < maxsize; i++)
    {
        invertex[i] = 0;
    }
    cout << "please enter the vertex" << endl;
    for (int i = 0; i < vexsize; i++)
    {
        cin >> vex[i].data;
        vex[i].firstadj = nullptr;
    }
    for (int n = 0; n < arcsize; n++) //有向图，因此只需插入一个节点背后
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
        invertex[j] += 1; //入度增加
        adjvertex *temp = new adjvertex;
        temp->adjvex = j;
        temp->nextadj = vex[i].firstadj;
        temp->weight = tempweight;
        vex[i].firstadj = temp;
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
class criticalpath
{
public:
    graph<T> graphfortps;
    int *criticaltime;
    T *previousvertex;
    criticalpath(graph<T> &graph1);
    void returncriticalpath(); //输出关键路径以及时间
};
template <class T>
criticalpath<T>::criticalpath(graph<T> &graph1)
{
    graphfortps = graph1;
    criticaltime = new int[graphfortps.vexsize];
    previousvertex = new T[graphfortps.vexsize];
    for (int i = 0; i < graphfortps.vexsize; i++)
    {
        previousvertex[i] = NULL;
        criticaltime[i] = 0;
    }
}
template <class T>
void criticalpath<T>::returncriticalpath()
{
    stack<T> tempstack;
    int count = 0;
    for (int i = 0; i < graphfortps.vexsize; i++)
    {
        if (graphfortps.invertex[i] == 0)
        {
            tempstack.push(graphfortps.vex[i].data);
        }
    }
    while (!tempstack.empty())
    {
        T temp = tempstack.pop();
        int tempcriticaltime = criticaltime[graphfortps.locate(temp)];
        count++;
        for (adjvertex *w = graphfortps.vex[graphfortps.locate(temp)].firstadj; w; w = w->nextadj)
        {
            if (criticaltime[w->adjvex] < tempcriticaltime + w->weight)
            {
                criticaltime[w->adjvex] = tempcriticaltime + w->weight;
                previousvertex[w->adjvex] = temp;
            }
            graphfortps.invertex[w->adjvex]--;
            if (graphfortps.invertex[w->adjvex] == 0)
            {
                tempstack.push(graphfortps.vex[w->adjvex].data);
            }
        }
    }
    if (count < graphfortps.vexsize)
    {
        cout << "there is a circle in the directed graph" << endl;
        exit(1);
    }
    int t;
    int tcriticaltime = criticaltime[0];
    for (int i = 0; i < graphfortps.vexsize; i++)
    {
        if (tcriticaltime < criticaltime[i])
        {
            tcriticaltime = criticaltime[i];
            t = i;
        }
    }
    stack<T> temp2;
    temp2.push(graphfortps.vex[t].data);
    for (T tempdata = previousvertex[t]; tempdata != NULL; tempdata = previousvertex[graphfortps.locate(tempdata)])
    {
        temp2.push(tempdata);
    }
    while (!temp2.empty())
    {
        cout << temp2.pop() << " ";
    }
    cout << endl;
    cout << criticaltime[t];
}
int main()
{
    graph<char> graph1;
    graph1.create(4,4);
    criticalpath<char> criticalpath1(graph1);
    criticalpath1.returncriticalpath();
    return 0;
}