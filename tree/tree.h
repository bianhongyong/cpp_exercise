#ifndef TREE_H
#define TREE_H

#include<iostream>
#include<math.h>
#include<stdexcept>
#include<queue>
template<typename T>/*模板结构体,兼容不同数据类型*/
struct Bstnode
{
    T data;
    Bstnode<T> *left;
    Bstnode<T> *right;
    Bstnode<T> *p;
};


template<typename T>/*模板类,兼容不同数据类型*/
class tree
{
private:
    Bstnode<T>* Root;//储存根节点
    int node_sum;//节点数量
    void pre_travel_re(Bstnode<T>* &root/*指针变量的引用,避免生成临时变量拷贝*/);/*递归前序遍历,根左右*/
    void mid_travel_re(Bstnode<T>* &root);/*递归中序遍历,左根右*/
    void sub_travel_re(Bstnode<T>* &root);/*递归后序遍历,右根左*/

    void insert_re(Bstnode<T>* &root,Bstnode<T>* &root_p,T data);/*递归插入新数据，保持二叉搜索树的性质*/
    Bstnode<T>* search_re(Bstnode<T>* &root,T data);/*递归搜索相应的值,返回对应结点的内存地址*/
    
    int tree_height_re(Bstnode<T>* &root);/*递归求取树的最大高度*/

    template<bool findMax>
    T find_extreme_re(Bstnode<T>* &root);/*递归寻找,函数模板兼容最大最小值*/

    bool isBST_re(Bstnode<T>* &root,T minvalue,T maxvalue);/*递归判断,子树也需满足二叉树的性质*/
    void delete_node_re(Bstnode<T>* &root);/*删除某个结点*/
    T Get_successor_re(Bstnode<T>* &root,T data);/*获取比data大的值的最小值*/
    T Get_predecessor_re(Bstnode<T>* &root,T data);/*获取比data小的值中的最大值*/
    void clear_re(Bstnode<T>* &root);/*后续遍历释放内存删除结点,只能后续遍历,根节点必须最后删*/

public:
    tree();
    ~tree();

    Bstnode<T>* getnode(T data);/*获取新节点,开辟一块堆内存,并返回*/
    void insert(T data);/*插入新数据*/
    Bstnode<T>* search(T data);/*搜索数据是否在树中*/
    int tree_height();/*获取树的高度*/

    T find_max();/*寻找最大值*/
    T find_min();/*寻找最小值*/
    
    void bfs();/*层次遍历树*/
    bool isBST();/*判断是否是一颗二叉搜索树*/
    
    void pre_travel(){/*前序遍历*/
        pre_travel_re(this->Root);
        std::cout<<std::endl;
    }
    void mid_travel(){/*中序遍历*/
        mid_travel_re(this->Root);
        std::cout<<std::endl;
    }
    void sub_travel(){/*后序遍历*/
        sub_travel_re(this->Root);
        std::cout<<std::endl;
    }
    bool delete_node(T data);
    T Get_successor(T data);
    T Get_predecessor(T data);
};

template<typename T>
tree<T>::tree():Root(nullptr),node_sum(0){}

template<typename T>
void tree<T>::insert_re(Bstnode<T>* &root/*指针的引用*/,Bstnode<T>* &root_p,T data){
    /*递归插入data*/
    if (root==nullptr)
    {
        root = getnode(data);
        root->p = root_p;
        root->left = nullptr;
        root->right = nullptr;
        return;
    }
    else if(root->data>=data){
        insert_re(root->left,root,data);
    }
    else if(root->data<data){
        insert_re(root->right,root,data);
    }
}
template<typename T>
Bstnode<T>* tree<T>::getnode(T data){
    Bstnode<T>* node = new(Bstnode<T>);
    node->data = data;
    node_sum++;
    return node;
}
template<typename T>
Bstnode<T>* tree<T>::search_re(Bstnode<T>* &root/*指针的引用*/,T data){
    if(root==nullptr){
        return nullptr;
    }
    if(root->data>data){//左子树
        return search_re(root->left,data);
    }
    else if(root->data<data){//右子树
        return search_re(root->right,data);
    }
    else if(root->data==data){//匹配成功
        return root;
    }

    return nullptr;
}

template<typename T>
template<bool findMax>
T tree<T>::find_extreme_re(Bstnode<T>* &root) {
    Bstnode<T>* &direction = findMax ? root->right : root->left;
    if(direction==nullptr) return root->data;
    return find_extreme_re<findMax>(direction);
}

template<typename T>
int tree<T>::tree_height_re(Bstnode<T>* &root){
    if(root==nullptr){
        return -1;
    }
    return std::max(tree_height_re(root->left),tree_height_re(root->right))+1;
}

template<typename T>
void tree<T>::insert(T data){
    Bstnode<T>* temp = nullptr;
    insert_re(Root,temp,data);
}

template<typename T>
Bstnode<T>* tree<T>::search(T data){
    return search_re(Root,data);
}

template<typename T>
T tree<T>::find_max(){
    if (Root==nullptr)
    {
        throw std::runtime_error("Error: Tree is empty!");
        return -1;
    }
    return find_extreme_re<true>(Root);
}

template<typename T>
T tree<T>::find_min(){
    if (Root==nullptr)
    {
        throw std::runtime_error("Error: Tree is empty!");
        return -1;
    }
    return find_extreme_re<false>(Root);
}

template<typename T>
int tree<T>::tree_height(){
    return tree_height_re(Root);
}

template<typename T>
void tree<T>::bfs(){
    /*宽度优先遍历*/
    std::queue<Bstnode<T>*> node_queue;
    node_queue.push(Root);
    while (!node_queue.empty())
    {
        Bstnode<T>* temp = node_queue.front();

        std::cout<<temp->data<<" ";
        if(temp->left!=nullptr) node_queue.push(temp->left);
        if(temp->right!=nullptr) node_queue.push(temp->right);
        node_queue.pop();
    }
    std::cout<<std::endl;
}
template<typename T>
void tree<T>::pre_travel_re(Bstnode<T>* &root){
    if(root==nullptr) return;
    std::cout<<root->data<<" ";
    pre_travel(root->left);
    pre_travel(root->right);
}

template<typename T>
void tree<T>::mid_travel_re(Bstnode<T>* &root){
    if(root==nullptr) return;
    mid_travel_re(root->left);
    std::cout<<root->data<<" ";
    mid_travel_re(root->right);
}

template<typename T>
void tree<T>::sub_travel_re(Bstnode<T>* &root){
    if(root==nullptr) return;
    sub_travel_re(root->left);
    sub_travel_re(root->right);
    std::cout<<root->data<<" ";
}

template<typename T>
bool tree<T>::isBST_re(Bstnode<T>* &root,T minvalue,T maxvalue){
    if(root==nullptr) return true;

    if(root->data>=minvalue&&root->data<=maxvalue&&isBST_re(root->left,minvalue,root->data)&&isBST_re(root->right,root->data,maxvalue)){
        std::cout<<root->data<<" "<<minvalue<<" "<<maxvalue<<std::endl;
        return true;
    }
    else{
        return false;
    }
    
}
template<typename T>
bool tree<T>::isBST(){
    //std::cout<<Root->data<<std::endl;
    return isBST_re(Root,(T)INT32_MIN,(T)INT32_MAX);
}

template<typename T>
void tree<T>::delete_node_re(Bstnode<T>* &root){
    /*case1:叶子节点*/
    if(root->left==nullptr&&root->right==nullptr){
        if(root->p->left==root) root->p->left=nullptr;
        else if(root->p->right==root) root->p->right=nullptr;
        delete root;
    }
    /*case2:单孩子的内结点*/
    else if(root->left==nullptr&&root->right!=nullptr){
        if(root->p->left==root) root->p->left=root->right;
        else if(root->p->right==root) root->p->right=root->right;
        delete root;
    }
    else if(root->left!=nullptr&&root->right==nullptr){
        if(root->p->left==root) root->p->left=root->left;
        else if(root->p->right==root) root->p->right=root->left;
        delete root;
    }
    /*case2:双孩子的内节点*/
    else{
        T temp_value = find_extreme_re<true>(root->left);//找左子树的最大值 o(h)
        Bstnode<T>* temp = search(temp_value);//o(h)
        root->data = temp_value;
        delete_node_re(temp);//递归删除
    }

}

template<typename T>
bool tree<T>::delete_node(T data){
    Bstnode<T>* temp = search(data);
    if(temp==nullptr) return false;
    else{
        delete_node_re(temp);
        return true;
    }
}

template<typename T>
T tree<T>::Get_successor_re(Bstnode<T>* &root,T data){
    Bstnode<T>* temp = search(data);
    if(temp==nullptr) return (T)-1;
    /*该结点右子树存在,根据二叉搜索树性质，后继为结点右子树的最小值*/
    if(temp->right!=nullptr){
        T temp_value = find_extreme_re<false>(temp->right);
        return search(temp_value)->data;
    }
    /*该结点右子树不存在,那么它的后继就是它的某个祖先节点，该祖先节点的值大于 x，
    并且这个祖先节点是 x 的所有祖先节点中值最小的。这需要从 x 的父节点开始向上查找,
    直到找到一个祖先,x在这个祖先的左子树里*/
    else{
        Bstnode<T>* current=temp;
        while(current->p!=nullptr&&current->p->left!=current){
            current=current->p;
        }
         if(current->p==nullptr){//祖先搜索到根节点，证明值为最大的，没有后继。
            throw std::runtime_error("This data have not successor!");
            return (T)-1;
        }
        return current->p->data;
    }
}

template<typename T>
T tree<T>::Get_successor(T data){
    return Get_successor_re(Root,data);
}

template<typename T>
T tree<T>::Get_predecessor_re(Bstnode<T>* &root,T data){
    Bstnode<T>* temp = search(data);
    if(temp==nullptr){
        return (T)-1;
    }
    else{
        /*该结点右子树存在,根据二叉搜索树性质，前驱为结点左子树的最大值*/
        if(temp->left!=nullptr){
            return find_extreme_re<true>(temp->left);
        }
        /*该结点左子树不存在,那么它的前驱就是它的某个祖先节点，该祖先节点的值小于 x，
        并且这个祖先节点是 x 的所有祖先节点中值最大的。这需要从 x 的父节点开始向上查找,
        直到找到一个祖先,x在这个祖先的右子树里*/
        else{
            Bstnode<T>* current=temp;
            while (current->p!=nullptr&&current->p->right!=current)
            {
                current = current->p;
            }
            if(current->p==nullptr){
                throw std::runtime_error("This data have not predecessor!");
                return (T)-1;
            }
            return current->p->data;
        }
    }
}

template<typename T>
T tree<T>::Get_predecessor(T data){
    return Get_predecessor_re(Root,data);
}

template<typename T>
void tree<T>::clear_re(Bstnode<T>* &root){
    if(root==nullptr){
        return;
    }
    clear_re(root->left);
    clear_re(root->right);
    delete root;
}

template<typename T>
tree<T>::~tree()
{
    clear_re(Root);//如果不是空树则递归删除.
}

#endif