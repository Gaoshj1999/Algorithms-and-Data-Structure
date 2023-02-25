//平衡二叉树(AVLtree)(为了提升查找效率)
#include <iostream>
using namespace std;
template <class T>
class treenode
{
public:
    T data;
    treenode<T> *leftchild, *rightchild;
    int height;
    treenode(const T &data) //自定义构造函数
    {
        this->data = data;
        leftchild = rightchild = nullptr;
        height = 0;
    }
};
template <class T>
class AVLtree
{
public:
    treenode<T> *proot;
    AVLtree();
    ~AVLtree() {}
    void insert(const T &data);                               //const是不希望函数内部对data值进行修改，而&是不想再临时构造一个对象浪费
    void insertnodetotree(treenode<T> *&root, const T &data); //这里是为了封装，不希望外界看到，其实前面还可以加一个private
    treenode<T> *erase(const T &data);
    treenode<T> *erasetreenode(treenode<T> *&root, const T &data);
    int getheight(treenode<T> *&root);
    treenode<T> *RR(treenode<T> *root);     //右旋
    treenode<T> *LL(treenode<T> *root);     //左旋
    treenode<T> *LR(treenode<T> *root);     //左右旋
    treenode<T> *RL(treenode<T> *root);     //右左旋
    treenode<T> *adjust(treenode<T> *root); //调平衡
};
template <class T>
AVLtree<T>::AVLtree()
{
    proot = NULL;
}
template <class T>
void AVLtree<T>::insert(const T &data)
{
    insertnodetotree(proot, data);
}
template <class T>
int AVLtree<T>::getheight(treenode<T> *&root)
{
    if (root)
    {
        return root->height;
    }
    else
    {
        return 0;
    }
}
template <class T>
treenode<T> *AVLtree<T>::LL(treenode<T> *root) //在旋转中已经将直接相关的结点调整高度了
{
    treenode<T> *temp = root->leftchild;
    root->leftchild = temp->rightchild;
    temp->rightchild = root;
    int lh = getheight(root->leftchild);
    int rh = getheight(root->rightchild);
    root->height = 1 + ((lh > rh) ? lh : rh);
    lh = getheight(temp->leftchild);
    rh = getheight(temp->rightchild);
    temp->height = 1 + ((lh > rh) ? lh : rh);
    return temp;
}
template <class T>
treenode<T> *AVLtree<T>::RR(treenode<T> *root)
{
    treenode<T> *temp = root->rightchild;
    root->rightchild = temp->leftchild;
    temp->leftchild = root;
    int lh = getheight(root->leftchild);
    int rh = getheight(root->rightchild);
    root->height = 1 + ((lh > rh) ? lh : rh);
    lh = getheight(temp->leftchild);
    rh = getheight(temp->rightchild);
    temp->height = 1 + ((lh > rh) ? lh : rh);
    return temp;
}
template <class T>
treenode<T> *AVLtree<T>::LR(treenode<T> *root)
{
    root->leftchild = RR(root->leftchild);
    return LL(root);
}
template <class T>
treenode<T> *AVLtree<T>::RL(treenode<T> *root)
{
    root->leftchild = LL(root->leftchild);
    return RR(root);
}
template <class T>
void AVLtree<T>::insertnodetotree(treenode<T> *&root, const T &data)
{
    //第一步以有序二叉树的方式插入

    //第二步检查是否需要旋转，需要就旋转

    //第三步设置高度

    if (root == NULL)
    {
        root = new treenode<T>(data);
    }
    else if (root->data < data)
    {
        insertnodetotree(root->rightchild, data);
        if (getheight(root->rightchild) - getheight(root->leftchild) > 1) //右边比左边高//这个调整会在第一个出现问题的结点处进行调整
        {
            //判断是哪种不平衡导致旋转
            if (data > root->rightchild->data) //RR(左旋)
            {
                root = RR(root);
            }
            else //RL(右左旋)
            {
                root = RL(root);
            }
        }
    }
    else if (root->data > data)
    {
        insertnodetotree(root->leftchild, data);
        if (getheight(root->leftchild) - getheight(root->rightchild) > 1) //左边比右边高
        {
            if (data < root->leftchild->data) //LL(右旋)
            {
                root = LL(root); //以root为轴右旋，然后返回值赋值给root，修改根结点
            }
            else //左右旋
            {
                root = LR(root);
            }
        }
    }
    else
    {
        cout << "you can't insert the element which is already had " << endl;
        exit(1);
    }
    int lh = getheight(root->leftchild); //这里的调整高度是为了插入时的调整，旋转的调整在旋转中已实现
    int rh = getheight(root->rightchild);
    root->height = 1 + ((lh > rh) ? lh : rh);
}
template <class T>
treenode<T> *AVLtree<T>::adjust(treenode<T> *root)
{
    if (root == NULL)
    {
        return NULL;
    }
    if (getheight(root->leftchild) - getheight(root->rightchild) > 1) //沿高度大的那条路判断
    {
        if (getheight(root->leftchild->leftchild) >= getheight(root->leftchild->rightchild))
        {
            root = LL(root);
        }
        else
        {
            root = LR(root);
        }
    }
    if (getheight(root->rightchild) - getheight(root->leftchild) > 1) //沿高度大的那条路判断
    {
        if (getheight(root->rightchild->rightchild) >= getheight(root->rightchild->leftchild))
        {
            root = RR(root);
        }
        else
        {
            root = RL(root);
        }
    }
    // int lh = getheight(root->leftchild);
    // int rh = getheight(root->rightchild);
    // root->height = 1 + ((lh > rh) ? lh : rh);
    return root;
}
template <class T>
treenode<T> *AVLtree<T>::erase(const T &data)
{
    return erasetreenode(proot, data);
}
template <class T>
treenode<T> *AVLtree<T>::erasetreenode(treenode<T> *&root, const T &data)
{
    if (root == NULL)
    {
        return NULL;
    }
    if (root->data == data)
    {
        if (root->rightchild == nullptr) //这里因为右子树为空，所以左子树也只能有一个结点，因此左子树的高度不需要调整
        {
            treenode<T> *temp = root;
            root = root->leftchild;
            delete temp;
            return root;
        }
        else //将直接后继作为这个节点的值，并递归删除这个结点(变为删除直接后继)
        {
            treenode<T> *temp = root->rightchild;
            while (temp->leftchild)
            {
                temp = temp->leftchild;
            }
            root->data = temp->data;
            root->rightchild = erasetreenode(root->rightchild, root->data); //到右子树去删除结点
            int lh = getheight(root->leftchild);                            //可以看到在结点所有可能的情况均调整高度了，因此删除节点的所有祖先的高度均完成了调整
            int rh = getheight(root->rightchild);
            root->height = 1 + ((lh > rh) ? lh : rh);
        }
    }
    else if (root->data > data)
    {
        root->leftchild = erasetreenode(root->leftchild, data);
    }
    else
    {
        root->rightchild = erasetreenode(root->rightchild, data);
    }
    int lh = getheight(root->leftchild); //可以看到在结点所有可能的情况均调整高度了，因此删除节点的所有祖先的高度均完成了调整
    int rh = getheight(root->rightchild);
    root->height = 1 + ((lh > rh) ? lh : rh);
    // if (root->leftchild)
    // {
    //     root->leftchild = adjust(root->leftchild);
    // }
    // if (root->rightchild)
    // {
    //     root->rightchild = adjust(root->rightchild);
    // }
    if (root) //所有的删除结点的祖先均参与了调整，只需每次调整节点即可因为该调整都是保证不破坏平衡的条件下向上调整的，所以按此顺序调整不会破坏平衡
    {
        root = adjust(root);
    }
    return root;
}
template <class T>
void inordertraverse(treenode<T> *tree) //中序遍历
{
    if (tree)
    {
        inordertraverse(tree->leftchild);
        cout << tree->data << " " << tree->height << endl;
        inordertraverse(tree->rightchild);
    }
}
int main()
{
    AVLtree<int> tree1;
    tree1.insert(5);
    tree1.insert(4);
    tree1.insert(3);
    tree1.insert(2);
    tree1.insert(1);
    tree1.insert(6);
    tree1.insert(7);
    tree1.insert(8);
    tree1.insert(9);
    inordertraverse(tree1.proot);
    cout << " " << endl;
    tree1.erase(1);
    inordertraverse(tree1.proot);
    cout << " " << endl;
    tree1.erase(3);
    inordertraverse(tree1.proot);
    cout << " " << endl;
    tree1.erase(6);
    inordertraverse(tree1.proot);
    cout << " " << endl;
    tree1.erase(8);
    tree1.erase(9);
    inordertraverse(tree1.proot);
    cout << " " << endl;
    return 0;
}