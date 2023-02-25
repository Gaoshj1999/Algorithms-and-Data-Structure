//最短路径floyd算法(加权无向图)(加权有向图算法不需要改变)(邻接矩阵实现)
//复杂度O(v^3)，对中间规模的数据很有效
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
const int maxsize = 100; //定义顶点的最大数目
template <class T>
class vertex //定义顶点
{
public:
    T data;
};
template <class T>
class graph
{
public:
    vertex<T> vex[maxsize];          //顶点数组
    int adjmatrix[maxsize][maxsize]; //邻接矩阵
    int vexsize, edgsize;            //顶点个数及边的个数
    graph();
    ~graph() {}
    int locate(T tempvertex);              //返回顶点序号
    void create(int vexsize, int edgsize); //创建图
};
template <class T>
graph<T>::graph()
{
    vexsize = 0;
    edgsize = 0;
    for (int i = 0; i < maxsize; i++)
    {
        for (int j = 0; j < maxsize; j++)
        {
            adjmatrix[i][j] = INT_MAX / 2;
        }
    }
    for (int i = 0; i < maxsize; i++)
    {
        adjmatrix[i][i] = 0;
    }
}
template <class T>
int graph<T>::locate(T tempvertex)
{
    for (int i = 0; i < vexsize; i++)
    {
        if (vex[i].data == tempvertex)
        {
            return i;
        }
    }
    return NULL;
}
template <class T>
void graph<T>::create(int vexsize, int edgsize)
{
    this->vexsize = vexsize;
    this->edgsize = edgsize;
    cout << "please enter the vertex" << endl;
    for (int i = 0; i < vexsize; i++)
    {
        cin >> vex[i].data;
    }
    // cout << "please enter the adjmatrix" << endl;
    // for (int i = 0; i < vexsize; i++) //按行输入边
    // {
    //     for (int j = 0; j < vexsize; j++)
    //     {
    //         cin >> adjmatrix[i][j];
    //     }
    // }
    for (int i = 0; i < edgsize; i++) //按边输入(无向图)
    {
        T k, j;
        int tempweight;
        cout << "please enter the vertex between the arc" << endl;
        cin >> k >> j;
        cout << "please enter the weight of the arc" << endl;
        cin >> tempweight;
        adjmatrix[locate(k)][locate(j)] = tempweight;
        adjmatrix[locate(j)][locate(k)] = tempweight;
    }
}
template <class T>
class floydsp
{
public:
    graph<T> graphforsp;
    int **matrixforpath; //放由start到end经过哪个顶点的矩阵
    floydsp(graph<T> tgraph);
    ~floydsp() {}
    void newvertexs();
    void newonevertex(int tvertex);
    void getpathandcost(T a, T b);
    void searchforvertex(queue<int> &tempqueue, int i, int j);
};
template <class T>
floydsp<T>::floydsp(graph<T> tgraph)
{
    graphforsp = tgraph;
    matrixforpath = new int *[graphforsp.vexsize];
    for (int i = 0; i < graphforsp.vexsize; i++)
    {
        matrixforpath[i] = new int[graphforsp.vexsize];
    }
    for (int i = 0; i < graphforsp.vexsize; i++)
    {
        for (int j = 0; j < graphforsp.vexsize; j++)
        {
            matrixforpath[i][j] = -1;
        }
    }
    newvertexs();
}
template <class T>
void floydsp<T>::newonevertex(int tvertex)
{
    for (int i = 0; i < graphforsp.vexsize; i++)
    {
        for (int j = 0; j < graphforsp.vexsize; j++)
        {
            if (graphforsp.adjmatrix[i][j] > graphforsp.adjmatrix[i][tvertex] + graphforsp.adjmatrix[tvertex][j])
            {
                graphforsp.adjmatrix[i][j] = graphforsp.adjmatrix[i][tvertex] + graphforsp.adjmatrix[tvertex][j];
                matrixforpath[i][j] = tvertex;
            }
        }
    }
}
template <class T>
void floydsp<T>::newvertexs()
{
    for (int i = 0; i < graphforsp.vexsize; i++)
    {
        newonevertex(i);
    }
}
template <class T>
void floydsp<T>::searchforvertex(queue<int> &tempqueue, int i, int j)
{
    if (matrixforpath[i][j] == -1)
    {
        tempqueue.enqueue(-1);
    }
    else
    {
        searchforvertex(tempqueue, i, matrixforpath[i][j]);
        tempqueue.enqueue(matrixforpath[i][j]);
        searchforvertex(tempqueue, matrixforpath[i][j], j);
    }
}
template <class T>
void floydsp<T>::getpathandcost(T a, T b)
{
    int i = graphforsp.locate(a);
    int j = graphforsp.locate(b);
    if (graphforsp.adjmatrix[i][j] == INT_MAX/2)
    {
        cout << "there is no path" << endl;
    }
    else
    {
        queue<int> tempqueue;
        tempqueue.enqueue(i);
        searchforvertex(tempqueue, i, j);
        tempqueue.enqueue(j);
        int temp;
        while (!tempqueue.empty())
        {
            temp = tempqueue.dequeue();
            if (temp != -1)
            {
                cout << graphforsp.vex[temp].data << " ";
            }
        }
        cout << ":" << graphforsp.adjmatrix[i][j];
    }
}
int main()
{
    graph<char> graph1;
    graph1.create(5, 6);
    floydsp<char> floydsp1(graph1);
    floydsp1.getpathandcost('a', 'e');
}