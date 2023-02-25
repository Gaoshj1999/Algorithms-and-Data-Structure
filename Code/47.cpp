//kruskal算法构造最小生成树MST(加权无向图)(并查集实现)
#include <iostream>
using namespace std;
class disjointset
{
public:
    int *parent;
    int *height;
    disjointset(int size);
    int find(int i);              //找到根节点
    void set_union(int i, int j); //合并
};
disjointset::disjointset(int size)
{
    parent = new int[size];
    height = new int[size];
    for (int i = 0; i < size; i++)
    {
        parent[i] = i;
        height[i] = 1;
    }
}
int disjointset::find(int i)
{
    return parent[i] == i ? i : find(parent[i]);
}
void disjointset::set_union(int i, int j) //此即为加边过程
{
    int parenti = find(i);
    int parentj = find(j);
    if (parenti != parentj)
    {
        if (height[parenti] > height[parentj])
        {
            int temp = parenti;
            parenti = parentj;
            parentj = temp;
        }
        parent[parenti] = parentj;
        height[parentj] += height[parenti];
    }
    if (parenti == parentj) //判断回路
    {
        cout << "there is a circle" << endl;
    }
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
class edge
{
public:
    int a; //一端顶点
    int b; //另一端顶点
    int weight;
};
template <class T>
class kruskalMST
{
public:
    graph<T> graphforprim;
    edge *graphedge;
    int *edgeto;    //索引代表顶点，值代表当前顶点和最小生成树之间的最短边的另一端的顶点
    int *arcweight; //索引代表顶点，值代表当前顶点和最小生成树之间的最短边的权重
    kruskalMST(graph<T> tempgraph);
    void getedge();
    void settree();
    void gettree(); //将最小生成树输出出来
};
template <class T>
kruskalMST<T>::kruskalMST(graph<T> tempgraph)
{
    graphforprim = tempgraph;
    graphedge = new edge[2 * graphforprim.arcsize];
    edgeto = new int[graphforprim.vexsize];
    arcweight = new int[graphforprim.vexsize];
    for (int i = 0; i < graphforprim.vexsize; i++)
    {
        arcweight[i] = INT_MAX;
    }
    getedge();
    settree();
}
template <class T>
void kruskalMST<T>::getedge()
{
    int edgenumber = 0;
    for (int i = 0; i < graphforprim.vexsize; i++)
    {
        for (adjvertex *w = graphforprim.vex[i].firstadj; w; w = w->nextadj)
        {
            edge tempedge;
            tempedge.a = i;
            tempedge.b = w->adjvex;
            tempedge.weight = w->weight;
            graphedge[edgenumber] = tempedge;
            edgenumber++;
        }
    }
    for (int i = 2 * graphforprim.arcsize - 1; i > 0; i--)
    {
        for (int j = 0; j < i; j++)
        {
            if (graphedge[j + 1].weight < graphedge[j].weight)
            {
                edge temp = graphedge[j];
                graphedge[j] = graphedge[j + 1];
                graphedge[j + 1] = temp;
            }
        }
    }
}
template <class T>
void kruskalMST<T>::settree()
{
    int temp = 0;
    disjointset tempdisjointset(graphforprim.vexsize);
    for (int i = 0; i < 2 * graphforprim.arcsize; i++)
    {
        int parenti = tempdisjointset.find(graphedge[i].a);
        int parentj = tempdisjointset.find(graphedge[i].b);
        if (parenti != parentj && edgeto[graphedge[i].b] != graphedge[i].a)
        {
            if (arcweight[graphedge[i].a] == INT_MAX)
            {
                arcweight[graphedge[i].a] = graphedge[i].weight;
                edgeto[graphedge[i].a] = graphedge[i].b;
            }
            else
            {
                arcweight[graphedge[i].b] = graphedge[i].weight;
                edgeto[graphedge[i].b] = graphedge[i].a;
            }
            temp++;
            tempdisjointset.set_union(graphedge[i].a, graphedge[i].b);
        }
        if (temp == graphforprim.vexsize - 1)
        {
            break;
        }
    }
}
template <class T>
void kruskalMST<T>::gettree()
{
    for (int i = 0; i < graphforprim.vexsize; i++)
    {
        if (arcweight[i] != INT_MAX)
        {
            cout << graphforprim.vex[i].data << "<-->" << graphforprim.vex[edgeto[i]].data << ":" << arcweight[i] << endl;
        }
    }
}
int main()
{
    graph<char> graph1;
    graph1.create(6,11);
    kruskalMST<char> kruskalMST1(graph1);
    kruskalMST1.gettree();
    return 0;
}
