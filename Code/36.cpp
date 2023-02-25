//二叉搜索(查找)树改进版(通过封装及引用的方式实现了递归调用)
#include <iostream>
using namespace std;
template <class T>
class treenode
{
public:
    T data;
    treenode<T> *leftchild, *rightchild;
    treenode(const T &data) //自定义构造函数
    {
        this->data = data;
        leftchild = rightchild = nullptr;
    }
};
template <class T>
class binarysearchtree
{
public:
    treenode<T> *proot;
    binarysearchtree();
    ~binarysearchtree() {}
    void insert(const T &data);                               //const是不希望函数内部对data值进行修改，而&是不想再临时构造一个对象浪费
    void insertnodetotree(treenode<T> *&root, const T &data); //这里是为了封装，不希望外界看到，其实前面还可以加一个private
    void erase(const T &data);
    void erasetreenode(treenode<T> *&root, const T &data); //删除一个元素并调整树
    treenode<T> *elemmax();
    treenode<T> *elemmin();
    treenode<T> *elemmax(treenode<T> *&root); //返回最大元素的地址
    treenode<T> *elemmin(treenode<T> *&root); //返回最小元素的地址
    bool find(const T &data);                 //判断是否有该元素
    bool findelem(treenode<T> *&root, const T &data);
};
template <class T>
binarysearchtree<T>::binarysearchtree()
{
    proot = nullptr;
}
template <class T>
bool binarysearchtree<T>::find(const T &data)
{
    findelem(proot, data);
}
template <class T>
bool binarysearchtree<T>::findelem(treenode<T> *&root, const T &data)
{
    if (root == nullptr)
    {
        return false;
    }
    else
    {
        if (root->data == data)
        {
            return true;
        }
        else if (root->data > data)
        {
            return findelem(root->leftchild, data);
        }
        else
        {
            return findelem(root->rightchild, data);
        }
    }
}
template <class T>
treenode<T> *binarysearchtree<T>::elemmax()
{
    return elemmax(proot);
}
template <class T>
treenode<T> *binarysearchtree<T>::elemmin()
{
    return elemmon(proot);
}
template <class T>
treenode<T> *binarysearchtree<T>::elemmax(treenode<T> *&root)
{
    treenode<T> *temp = root;
    if (temp == nullptr)
    {
        cout << "there is no node in the tree" << endl;
        return static_cast<T>(NULL);
    }
    while (temp->rightchild != nullptr)
    {
        temp = temp->rightchild;
    }
    return temp;
}
template <class T>
treenode<T> *binarysearchtree<T>::elemmin(treenode<T> *&root)
{
    treenode<T> *temp = root;
    if (temp == nullptr)
    {
        cout << "there is no node in the tree" << endl;
        return static_cast<T>(NULL);
    }
    while (temp->leftchild != nullptr)
    {
        temp = temp->leftchild;
    }
    return temp;
}
template <class T>
void binarysearchtree<T>::insert(const T &data)
{
    insertnodetotree(proot, data);
}
template <class T>
void binarysearchtree<T>::insertnodetotree(treenode<T> *&root, const T &data)
{
    if (root == NULL)
    {
        root = new treenode<T>(data);
    }
    else if (root->data < data)
    {
        insertnodetotree(root->rightchild, data);
    }
    else if (root->data > data)
    {
        insertnodetotree(root->leftchild, data);
    }
    else
    {
        cout << "you can't insert the element which is already had " << endl;
        exit(1);
    }
}
template <class T>
void binarysearchtree<T>::erase(const T &data)
{
    erasetreenode(proot, data);
}
template <class T>
void binarysearchtree<T>::erasetreenode(treenode<T> *&root, const T &data)
{
    if (find(data))
    {
        treenode<T> *temp = root;
        treenode<T> *tempp = nullptr;
        while (true)
        {
            if (temp->data == data)
            {
                break;
            }
            tempp = temp;
            if (temp->data > data)
            {
                temp = temp->leftchild;
            }
            else
            {
                temp = temp->rightchild;
            }
        }
        if (temp->rightchild) //右子树不为空
        {
            treenode<T> *parent = temp;
            treenode<T> *child = temp->rightchild;
            while (child->leftchild)
            {
                parent = child;
                child = child->leftchild;
            }
            temp->data = child->data;
            if (parent == temp) //即右子树没有左子树
            {
                parent->rightchild = child->rightchild;
            }
            else
            {
                parent->leftchild = child->rightchild;
            }
            delete child;
        }
        else
        {
            if (!temp)
            {
                delete temp;
            }
            else
            {
                if (tempp->rightchild == temp)
                {
                    tempp->rightchild = temp->leftchild;
                }
                else
                {
                    tempp->leftchild = temp->leftchild;
                }
                delete temp;
            }
        }
    }
}
template <class T>
void preordertraverse(treenode<T> *root) //递归定义先序遍历并输出每个点的值
{
    if (root)
    {
        cout << root->data << " ";
        preordertraverse(root->leftchild);
        preordertraverse(root->rightchild);
    }
}
template <class T>
void inordertraverse(treenode<T> *root)
{
    if (root != nullptr)
    {
        inordertraverse(root->leftchild);
        cout << root->data << " ";
        inordertraverse(root->rightchild);
    }
}
template <class T>
void postordertraverse(treenode<T> *root)
{
    if (root)
    {
        postordertraverse(root->leftchild);
        postordertraverse(root->rightchild);
        cout << root->data << " ";
    }
}
int main()
{
    binarysearchtree<int> tree1;
    tree1.insert(1);
    tree1.insert(9);
    tree1.insert(4);
    tree1.insert(6);
    tree1.insert(5);
    tree1.insert(3);
    tree1.insert(7);
    tree1.insert(8);
    tree1.insert(2);
    preordertraverse(tree1.proot);
    cout << endl;
    inordertraverse(tree1.proot);
    cout << endl;
    postordertraverse(tree1.proot);
    cout << endl;
    cout << tree1.find(1) << endl;
    tree1.erase(9);
    tree1.erase(4);
    inordertraverse(tree1.proot);
    cout << endl;
    preordertraverse(tree1.proot);
    return 0;
}