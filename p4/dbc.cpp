#include <iostream>
#include <fstream>
#include <algorithm>
#include <string>
#include "BinaryTree.h"
#include "NodeInfo.h"
using namespace std;

void output_node_info(Node *current_node, BinaryTree &tree, string &cur_more, char choice)
// MODIFIES: current_node
// EFFECTS: let the current_node points to the node which is obtained
// by going through the path from the root of the tree, then output the
// compressed message according to the current_node's value and choice.
{
    current_node = tree.visitThroughPath(cur_more);
    NodeInfo current_node_info(current_node->getVal(), choice);
    cout << current_node_info;
}

void update_left(int &index, Node *current_node)
// REQUIRES: index >=0
// MODIFIES: index, current_node
// EFFECTS: update the index of nodes and add a new node to the current_node
// as the left child. Set the value of the new node be index.
{
    index++;
    current_node->setLeft(index);
}

void update_right(int &index, Node *current_node)
// REQUIRES: index >=0
// MODIFIES: index, current_node
// EFFECTS: update the index of nodes and add a new node to the current_node
// as the right child. Set the value of the new node be index.
{
    index++;
    current_node->setRight(index);
}

void deal_with_dbc(NodeInfo &d_current_node_info, Node * d_current_node, BinaryTree &dtree, int &index)
// MODIFIES: index, d_current_node
// EFFECTS: construct the binary tree and decompress the message according to the d_current_node_info.
{
    if (d_current_node_info.c=='0'){
        update_left(index,d_current_node);
        cout<<dtree.findPath(index);
    }else if (d_current_node_info.c=='1'){
        update_right(index,d_current_node);
        cout<<dtree.findPath(index);
    }else{
        cout<<dtree.findPath(d_current_node_info.node_index);
    }
}

int main(int argc, char *argv[]){
    // TODO: implement your dbc program here!
    string a1=argv[1];
    string filename=argv[2];
    string message;

    ifstream iFile;
    iFile.open(filename);
    getline(iFile,message);
    iFile.close();
    iFile.open(filename);

    if (a1=="-x"){
        BinaryTree xtree(0);
        Node * current_node;
        int index=0, exist;
        string cur,cur_more,exist_path ;
        char extra_path;
        if (message.empty()==1){
            NodeInfo current_node_info(0, '@');
            cout << current_node_info;
        }
        while (!message.empty()){
            exist=0;
            cur_more=cur+message[0];
            message=message.substr(1);
            // Test if cur_more is already contained in the current map.
            for (int i = 0; i <index ; ++i) {
                if (xtree.findPath(i+1)==cur_more) {
                    exist = 1;
                    cur = cur_more;
                    break;
                }
            }
            // If exist and there is message left, just continue to process. Otherwise, output the last Node's information.
            if (exist==1){
                if( !message.empty()) continue;
                else output_node_info(current_node,xtree,cur_more,'@');
            }
            // If doesn't exist, just add a node and update the corresponding information.
            // Note that if the message is empty now, output the first node's information.
            else{
                exist_path = cur_more.substr(0, cur_more.size() - 1);
                extra_path = cur_more[cur_more.size() - 1];
                current_node = xtree.visitThroughPath(exist_path);
                NodeInfo x_current_node_info(current_node->getVal(), extra_path);
                cout << x_current_node_info;
                if (extra_path == '1') update_right(index,current_node);
                else update_left(index,current_node);
                cur = "";
                if (message.empty()==1){
                    NodeInfo current_node_info(0, '@');
                    cout << current_node_info;
                }
            }
        }
    }else{
        BinaryTree dtree(0);
        Node *d_current_node;
        NodeInfo d_current_node_info;
        int index=0;
        while (iFile>>d_current_node_info){
            d_current_node=dtree.find(d_current_node_info.node_index);
            deal_with_dbc(d_current_node_info,d_current_node,dtree,index);
        }
    }
    iFile.close();
    return 0;
}