//二叉树(链式存储)
#include <iostream>
using namespace std;
template <class T>
class node
{
    T data;
    node<T> *leftchild;
    node<T> *rightchild;
    int depth;
};
template <class T>
class binarytree
{
public:
    node<T> *root;
    int height;
    int size;
    binarytree();
    ~binarytree();
    int getsize();               //所有节点的个数
    void insert(T elem);         //按照左小中中右大的顺序插入
    void create(T *list, int n); //创建一棵树
    void preordertreverse();     //递归定义先序遍历
};
template <class T>
binarytree<T>::binarytree()
{
    root = new node<T>;
    root->data = NULL;
    root->leftchild = nullptr;
    root->rightchild = nullptr;
    height = 0;
    depth = 0;
    size = 0;
}
template <class T>
binarytree<T>::~binarytree()
{
    delete root;
}
template <class T>
int binarytree<T>::getsize()
{
    return size;
}
template <class T>
void binarytree<T>::insert(T elem)
{
    if (size == 0)
    {
        root->data = elem;
        size++;
    }
    else
    {
        size++;
        node<T> *temp = root;
        while (temp != nullptr)
        {
            if (elem <= temp->data)
            {
                if (temp->leftchild == nullptr)
                {
                    temp->leftchild = new node<T>;
                    temp->leftchild->data = elem;
                    break;
                }
                else
                {
                    temp = temp->leftchild;
                }
            }
            else
            {
                if (temp->rightchild == nullptr)
                {
                    temp->rightchild = new node<T>;
                    temp->rightchild->data = elem;
                    break;
                }
                else
                {
                    temp = temp->rightchild;
                }
            }
        }
    }
}
template <class T>
void binarytree<T>::create(T *list, int n)
{
    for (int i = 0; i < n; i++)
    {
        insert(list[i]);
    }
}
template <class T>
void binarytree<T>::preordertreverse() //递归定义先序遍历函数
{
    node<T>* temp=
}
