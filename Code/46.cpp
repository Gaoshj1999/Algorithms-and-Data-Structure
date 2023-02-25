//prim算法构造最小生成树MST(加权无向图)
#include <iostream>
using namespace std;
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
class primMST
{
public:
    graph<T> graphforprim;
    int *edgeto;     //索引代表顶点，值代表当前顶点和最小生成树之间的最短边的另一端的顶点
    int *arcweight;  //索引代表顶点，值代表当前顶点和最小生成树之间的最短边的权重
    bool *marked;    //如果当前顶点已经在树中，则为true，否则为false
    int *recentpath; //索引代表顶点，值代表当前所有可达边的权重
    primMST(graph<T> tempgraph);
    int visited(int v); //把顶点v添加到最小生成树中,并更新数据,并返回下一个需要添加的顶点
    void gettree();     //将最小生成树输出出来
};
template <class T>
primMST<T>::primMST(graph<T> tempgraph)
{
    graphforprim = tempgraph;
    edgeto = new int[graphforprim.vexsize];
    arcweight = new int[graphforprim.vexsize];
    marked = new bool[graphforprim.vexsize];
    recentpath = new int[graphforprim.vexsize];
    for (int i = 0; i < graphforprim.vexsize; i++)
    {
        arcweight[i] = INT_MAX; //int类型的最大值
        recentpath[i] = INT_MAX;
        marked[i] = false;
    }
    //默认让顶点0进入到树中，但是树中只有一个顶点0，因此0顶点默认没有和其他顶点相连，所以让arcweight对应处值为0
    arcweight[0] = 0;
    int nextvisit = 0;
    for (int i = 0; i < graphforprim.vexsize; i++)
    {
        nextvisit = visited(nextvisit);
    }
}
template <class T>
int primMST<T>::visited(int v)
{
    marked[v] = true;
    for (adjvertex *w = graphforprim.vex[v].firstadj; w; w = w->nextadj)
    {
        //获取该边的另外一个顶点，其中当前节点为v
        int temp = w->adjvex;
        //判断另外一个顶点是不是已经在树中，如果不在树中则更新数据
        if (!marked[temp])
        {
            //判断新边的权重是否小于从另一顶点到树中已经存在的最小边的权重
            if (w->weight < arcweight[temp])
            {
                edgeto[temp] = v;
                arcweight[temp] = w->weight;
                recentpath[temp] = w->weight;
            }
        }
    }
    int temp = recentpath[1];
    int itemp=1;
    for (int i = 1; i < graphforprim.vexsize; i++) //搜索所有可达边中的最小值，并把v另一侧的节点返回
    {
        if (temp > recentpath[i])
        {
            temp = recentpath[i];
            itemp = i;
        }
    }
    recentpath[itemp] = INT_MAX;
    return itemp;
}
template <class T>
void primMST<T>::gettree()
{
    for (int i = 1; i < graphforprim.vexsize; i++)
    {
        cout << graphforprim.vex[i].data << "<-->" << graphforprim.vex[edgeto[i]].data << ":" << arcweight[i] << endl;
    }
}
int main()
{
    graph<char> graph1;
    graph1.create(5, 8);
    primMST<char> primMST(graph1);
    primMST.gettree();
    return 0;
}
