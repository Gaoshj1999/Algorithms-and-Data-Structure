//线索二叉树(太复杂不要求实现且学校课上没讲过)
#include <iostream>
using namespace std;
template <class T>
class bitreenode
{
public:
    T data;
    bitreenode<T> *leftchild, *rightchild;
    int lefttag,righttag;//等于1时表示无孩子则指向相应的前驱/后继，等于0时则为左右孩子
    bitreenode();
    ~bitreenode() {}
};
template <class T>
bitreenode<T>::bitreenode()
{
    data = NULL;
    leftchild = nullptr;
    rightchild = nullptr;
    lefttag=righttag=0;
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