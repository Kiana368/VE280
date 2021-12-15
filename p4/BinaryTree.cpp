#include "BinaryTree.h"
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

/* ================================== Node =================================== */

Node::Node(const int &val, Node *left, Node *right) {
    this->val=val;
    this->left=left;
    this->right=right;
}

int Node::getVal() const {
    return val;
}

void Node::setVal(const int &newVal) {
    this->val=newVal;
}

Node *Node::getLeft() const {
    return this->left;
}

void Node::setLeft(const int &newVal) {
    if (this->left== nullptr){
        this->left=new Node(newVal);
    }else{
        this->left->val=newVal;
    }
}

Node *Node::getRight() const {
    return this->right;
}

void Node::setRight(const int &newVal) {
    if (this->right== nullptr){
        this->right=new Node(newVal);
    }else{
        this->right->val=newVal;
    }
}

/* =============================== Binary Tree =============================== */

BinaryTree::BinaryTree(const int &rootValue) {
    root=new Node(rootValue);
}

BinaryTree::BinaryTree(Node *node) {
    root=new Node(*node);
}

Node *deep_copy_node(Node *root){
    if (root== nullptr) return nullptr;
    Node *left = nullptr;
    Node *right = nullptr;
    if (root->getLeft()!= nullptr) left=deep_copy_node(root->getLeft());
    if (root->getRight()!= nullptr) right=deep_copy_node(root->getRight());
    Node *nc=new Node(root->getVal(),left,right);
    return nc;
}

BinaryTree::BinaryTree(const BinaryTree &tree) {
    root=deep_copy_node(tree.root);
}

Node *BinaryTree::createFromVariant(const vector<nodeValue> &source, const int &rootIndex) {
    if (rootIndex >= source.size())
        return nullptr;
    auto rootValue = get_if<int>(&source[rootIndex]);
    if (!rootValue)
        return nullptr;
    int rightIndex = 2 * (rootIndex + 1);
    int leftIndex = rightIndex - 1;
    return new Node(*rootValue, createFromVariant(source, leftIndex), createFromVariant(source, rightIndex));
}

BinaryTree::BinaryTree(vector<nodeValue> &source) {
   root=createFromVariant(source,0);
}

void destroy_helper(Node *root){
    if (root!= nullptr){
        destroy_helper(root->getLeft());
        destroy_helper(root->getRight());
        delete root;
    }
}

BinaryTree::~BinaryTree() {
    destroy_helper(this->root);
}

bool BinaryTree::empty() const {
    return this->root == nullptr;
}

Node *find_helper(Node *root, const int &key){
    if (root== nullptr) return nullptr;
    if (root->getVal()==key) return root;
    Node * left= find_helper(root->getLeft(),key);
    Node * right= find_helper(root->getRight(),key);
    if (left!= nullptr) return left;
    if (right!= nullptr) return right;
    return nullptr;
}

Node *BinaryTree::find(const int &key) const {
    return find_helper(root,key);
}

string findPath_helper(Node *root, const int &value){
    if (root== nullptr) return "-1";
    if (root->getVal()==value) return "";
    string left=findPath_helper(root->getLeft(),value);
    string right=findPath_helper(root->getRight(),value);
    if (left!="-1") return "0"+left;
    if (right!="-1") return "1"+right;
    return "-1";
}

std::string BinaryTree::findPath(const int &value) const {
    string ans=findPath_helper(root,value);
    return ans;
}

Node *visitThroughPath_helper(Node *root, const string &path){
    if (path.empty()) return root;
    if (path[0]=='0' && root->getLeft()!= nullptr)
        return visitThroughPath_helper(root->getLeft(),path.substr(1));
    if (path[0]=='1' && root->getRight()!= nullptr)
        return visitThroughPath_helper(root->getRight(),path.substr(1));
    return nullptr;
}

Node *BinaryTree::visitThroughPath(const string &path) const {
    return visitThroughPath_helper(root,path);
}

int sum_helper(Node *root){
    if (root== nullptr) return 0;
    return root->getVal()+sum_helper(root->getRight())+sum_helper(root->getLeft());
}

int BinaryTree::sum() const {
    return sum_helper(root);
}

int height_helper(Node *root){
    if (root== nullptr) return 0;
    int left=height_helper(root->getLeft());
    int right=height_helper(root->getRight());
    if (left>=right) return left+1;
    return right+1;
}

int BinaryTree::height() const {
    return height_helper(root);
}

void preOrder_helper(Node *root){
    if (root== nullptr) return;
    cout<<root->getVal()<<" ";
    preOrder_helper(root->getLeft());
    preOrder_helper(root->getRight());
}

void BinaryTree::preOrder() const {
    preOrder_helper(root);
    cout<<endl;
}

void inOrder_helper(Node *root){
    if (root== nullptr) return;
    inOrder_helper(root->getLeft());
    cout<<root->getVal()<<" ";
    inOrder_helper(root->getRight());
}

void BinaryTree::inOrder() const {
    inOrder_helper(root);
    cout<<endl;
}

void postOrder_helper(Node *root){
    if (root== nullptr) return;
    postOrder_helper(root->getLeft());
    postOrder_helper(root->getRight());
    cout<<root->getVal()<<" ";
}

void BinaryTree::postOrder() const {
    postOrder_helper(root);
    cout<<endl;
}

int min_PathSum(Node *root){
    if (root== nullptr) return 0;
    if (root->getLeft()== nullptr && root->getRight()== nullptr) return root->getVal();
    int left=min_PathSum(root->getLeft());
    int right=min_PathSum(root->getRight());
    if (left<=right) return left+root->getVal();
    return right+root->getVal();
}

bool BinaryTree::allPathSumGreater(const int &sum) const {
    int min_sum=min_PathSum(root);
    return min_sum > sum;
}

bool cover_helper(Node *root, Node *tree_root){
    if (root== nullptr) return true;
    if (tree_root== nullptr) return false;
    return root->getVal() == tree_root->getVal() && cover_helper(root->getLeft(), tree_root->getLeft()) &&
           cover_helper(root->getRight(), tree_root->getRight());
}

bool BinaryTree::operator<(const BinaryTree &tree) const {
    return cover_helper(root,tree.root);
}

bool contain_helper(Node *root, Node *tree_root){
    if (cover_helper(root,tree_root)) return true;
    if (tree_root== nullptr) return false;
    return contain_helper(root,tree_root->getLeft()) || contain_helper(root,tree_root->getRight());
}

bool BinaryTree::operator<<(const BinaryTree &tree) const {
    return contain_helper(root,tree.root);
}

BinaryTree &BinaryTree::operator=(const BinaryTree &tree) {
    if(this!=&tree){
        destroy_helper(this->root);
        this->root=deep_copy_node(tree.root);
    }
    return *this;
}