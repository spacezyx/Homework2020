#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <limits.h>
#include <vector>
#include <queue>
#include <algorithm>

#include "Tree.h"

using namespace std;

/****************************************************************
 *                    Write your code below
 ****************************************************************/

//implementation of the operator

istream &operator>>(istream &in, BinaryDimonTree &tree){
    int num1;
    int num2;
    in>>tree.size;
    for(int i=0;i<tree.size;i++){
        in>>num1>>num2;
        TreeNode *node=new TreeNode;
        node->data[0]=num1;
        node->data[1]=num2;
        tree.input.push_back(node);
    }
    random_shuffle(tree.input.begin(),tree.input.end());

    tree.buildTree(tree.input);
    return in;
}

ostream &operator<<(ostream &out, const TreeNode &b){
    out<<b.data;
    return out;
}

//implementation of TreeNode
int TreeNode::getX(){ return this->data[0]; }
int TreeNode::getY(){ return this->data[1]; }
TreeNode::~TreeNode(){}

//implementation of BinaryDimonTree

BinaryDimonTree::BinaryDimonTree(){
    root=NULL;
}

void BinaryDimonTree::buildTree(vector<TreeNode*> input){
     while(!input.empty()){
         TreeNode *node=input.back();
         input.pop_back();
        if(this->root==NULL){
            root=node;
            node->step=0;
        }
        else{
            int step=0;
            TreeNode* cur=this->root;
            //TreeNode* parent=NULL;
            //find the position of new node and insert it
            while(cur){
                if((step%2==0)&&(node->data[0]<=cur->data[0])){
                    if(cur->lchild){
                    cur=cur->lchild;
                    step++;
                    continue;
                    }
                    else{
                        cur->lchild=node;
                        node->step=step+1;
                        break;
                    }
                }
                if((step%2==0)&&(node->data[0]>cur->data[0])){
                    if(cur->rchild){
                    cur=cur->rchild;
                    step++;
                    continue;
                    }
                    else{
                        cur->rchild=node;
                        node->step=step+1;
                        break;
                    }
                }
                if((step%2==1)&&(node->data[1]<=cur->data[1])){
                    if(cur->lchild){
                    cur=cur->lchild;
                    step++;
                    continue;
                    }
                    else {
                        cur->lchild=node;
                        node->step=step+1;
                        break;
                    }
                }
                if((step%2==1)&&(node->data[1]>cur->data[1])){
                    if(cur->rchild){
                    cur=cur->rchild;
                    step++;
                    continue;
                    }
                    else{
                        cur->rchild=node;
                        node->step=step+1;
                        break;
                    }
                }
                else break;
            }
        }
    }
}


TreeNode* BinaryDimonTree::find_nearest_node(int x, int y){
    TreeNode* node=this->root;
    TreeNode** guess=&node;
    long long int min_distance=100000000;
    TreeNode *cur=root;
    min_distance=(x-cur->data[0])*(x-cur->data[0])+(y-cur->data[1])*(y-cur->data[1]);

    if(cur==NULL)
        return NULL;
    else
        recur_search(root,x,y,min_distance,guess);
    return *guess;
}


void BinaryDimonTree::recur_search(TreeNode *cur, int x, int y, long long int &min_distance, TreeNode **guess){
    if(cur==NULL) return;
    bool flag=((cur->step)%2)==0?true:false;
    int tmp=((x-cur->data[0])*(x-cur->data[0]))+((y-cur->data[1])*(y-cur->data[1]));
    if(tmp<min_distance){
        min_distance=tmp;
        *guess=cur;
    }
    else if(tmp==min_distance){
        if(cur->data[0]<(*guess)->data[0])
            *guess=cur;
        else if((cur->data[0]==(*guess)->data[0])&&(cur->data[1]<(*guess)->data[1]))
            *guess=cur;
    }

    if(flag){
        if(x<cur->data[0]){
            if(cur->lchild)
                recur_search(cur->lchild,x,y,min_distance,guess);
            if(abs(cur->data[0]-x)<sqrt(min_distance)+1)
                if(cur->rchild)
                    recur_search(cur->rchild,x,y,min_distance,guess);
        }
        else{
            if(cur->rchild)
                recur_search(cur->rchild,x,y,min_distance,guess);
            if(abs(cur->data[0]-x)<sqrt(min_distance))
                if(cur->lchild)
                    recur_search(cur->lchild,x,y,min_distance,guess);
        }
    }
    else{
        if(y<cur->data[1]){
                    if(cur->lchild)
                        recur_search(cur->lchild,x,y,min_distance,guess);
                    if(abs(cur->data[1]-y)<sqrt(min_distance)+1)
                        if(cur->rchild)
                            recur_search(cur->rchild,x,y,min_distance,guess);
                }
                else{
                    if(cur->rchild)
                        recur_search(cur->rchild,x,y,min_distance,guess);
                    if(abs(cur->data[1]-y)<sqrt(min_distance))
                        if(cur->lchild)
                            recur_search(cur->lchild,x,y,min_distance,guess);
                }
    }
}

