//图的存储结构(数组表示法，邻接矩阵)(有无向图均适用)
#include <iostream>
using namespace std;
const int maxsize = 100; //定义顶点的最大数目
enum graphkind           //定义图的类型
{
    DG, //有向图
    DN, //有向网
    AG, //无向图
    AN  //无向网
};
template <class T>
class vertex //定义顶点
{
public:
    T data;
};
template <class T>
class matrix
{
public:
    graphkind kind;                  //图的类型
    vertex<T> vex[maxsize];          //顶点数组
    int adjmatrix[maxsize][maxsize]; //邻接矩阵
    int vexsize, edgsize;            //顶点个数及边的个数
    matrix();
    ~matrix() {}
    void create(graphkind kind, int vexsize, int edgsize); //创建图
    void DFStraverse();                                    //深度优先遍历
    void BFDtraverse();                                    //广度优先遍历
};
template <class T>
matrix<T>::matrix()
{
    vexsize = 0;
    edgsize = 0;
    for (int i = 0; i < maxsize; i++)
    {
        for (int j = 0; j < maxsize; j++)
        {
            adjmatrix[i][j] = INT_MAX/2;
        }
    }
}
template <class T>
void matrix<T>::create(graphkind kind, int vexsize, int edgsize)
{
    this->kind = kind;
    this->vexsize = vexsize;
    this->edgsize = edgsize;
    cout << "please enter the vertex" << endl;
    for (int i = 0; i < vexsize; i++)
    {
        cin >> vex[i].data;
    }
    cout << "please enter the adjmatrix" << endl;
    for (int i = 0; i < vexsize; i++) //按行输入边
    {
        for (int j = 0; j < vexsize; j++)
        {
            cin >> adjmatrix[i][j];
        }
    }
    //     
    // for (int i = 0; i < edgsize; i++) //按边输入(无向图)
    // {
    //     T k, j;
    //     int tempweight;
    //     cout << "please enter the vertex between the arc" << endl;
    //     cin >> k >> j;
    //     cout << "please enter the weight of the arc" << endl;
    //     cin >> tempweight;
    //     adjmatrix[locate(k)][locate(j)] = tempweight;
    //     adjmatrix[locate(j)][locate(k)] = tempweight;
    // }
}
int main()
{
    matrix<int> matrix1;
    matrix1.create(DG, 2, 2);
    for (int i = 0; i < 2; i++)
    {
        for (int j = 0; j < 2; j++)
        {
            cout << matrix1.adjmatrix[i][j] << " ";
        }
        cout << endl;
    }
}