//二叉树(递归实现遍历)(树的先序遍历类似于图的深度优先)
#include <iostream>
using namespace std;
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
void preordertraverse(bitreenode<T> *tree) //递归定义先序遍历并输出每个点的值
{
    if (tree)
    {
        cout << tree->data << " ";
        preordertraverse(tree->leftchild);
        preordertraverse(tree->rightchild);
    }
}
template <class T>
bool visit(T elem) //visit函数举例，本例仅适用于int与double
{
    cout << elem << " ";
    return true;
}
template <class T>
bool preordertraverse1(bitreenode<T> *tree, bool (*visit)(T elem))
{
    if (tree)
    {
        if (visit(tree->data)) //这个在判断时如果成功了也就调用了，调用了也就成功了
        {
            preordertraverse1(tree->leftchild, visit);
            preordertraverse1(tree->rightchild, visit);
        }
    }
    return true;
}
template <class T>
void inordertraverse(bitreenode<T> *tree)//中序遍历
{
    if (tree)
    {
        inordertraverse(tree->leftchild);
        cout << tree->data << " ";
        inordertraverse(tree->rightchild);
    }
}
template <class T>
void postordertraverse(bitreenode<T> *tree)//后序遍历
{
    if (tree)
    {
        postordertraverse(tree->leftchild);
        postordertraverse(tree->rightchild);
        cout << tree->data << " ";
    }
}
int main()
{
    bitreenode<int> tree1;
    int a[] = {4, 1, 2, 3, 5, 6, 7, 8};
    create(tree1, a, 8);
    preordertraverse(&tree1);
    cout << endl;
    preordertraverse1(&tree1, visit);
    cout << endl;
    inordertraverse(&tree1);
    cout<<endl;
    postordertraverse(&tree1);
    return 0;
}