#include<iostream>
#include "tree.h"
using namespace std;

int main(){
    tree<double> demo = tree<double>();
    demo.insert(15.5);
    demo.insert(13.4);
    demo.insert(14);
    demo.insert(11.2);
    demo.insert(11.0);
    demo.insert(11.4);
    demo.insert(13.6);
    demo.insert(14.2);
    demo.insert(20.4);
    demo.insert(25.6);
    demo.insert(21.3);
    demo.insert(20.5);
    demo.insert(13.5);
    //cout<<(demo.search(21)!=nullptr? ("Found"):("Not Found"))<<endl;
    //cout<<demo.find_max()<<endl;
    // cout<<demo.tree_height()<<endl;
    // demo.bfs();
    // demo.mid_travel();
    // cout<<demo.isBST()<<endl;
    // demo.delete_node(11.2);
    // demo.bfs();
    //cout<<demo.Get_predecessor(20.5)<<endl;
    return 0;
}