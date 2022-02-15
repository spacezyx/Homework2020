//
// Created by Smile on 2019/4/8.
//

#ifndef C_BINARYDIMEN_TREE_H
#define C_BINARYDIMEN_TREE_H

#include <stdio.h>
#include <iostream>
#include <vector>
using namespace std;

/****************************************************************
 *                    Write your code below
 ****************************************************************/

struct dataNode
{
public:
    int x=0;
    int y=0;
};

class TreeNode
{
  friend ostream &operator<<(ostream &out, const TreeNode &b);
  friend class BinaryTree;
  friend class BinaryDimonTree;

//private:
  /* data */


public:
  int data[2];
  TreeNode *lchild;
  TreeNode *rchild;
  int step;
  /* methods */
  TreeNode():lchild(NULL),rchild(NULL){}
  TreeNode& operator=(TreeNode& b){
      TreeNode *p=new TreeNode;
      p->data[0]=b.data[0];
      p->data[1]=b.data[1];
      return *p;
  }
  int getX();  /* DO NOT CHANGE */
  int getY();  /* DO NOT CHANGE */
  ~TreeNode(); /* DO NOT CHANGE */
};


class BinaryDimonTree
{
friend istream &operator>>(istream &in, BinaryDimonTree &tree); /* DO NOT CHANGE */

private:
  /* data */
  TreeNode *root;

public:
  int size=0;
  vector<TreeNode*> input;
  /* methods */
  BinaryDimonTree();          /* DO NOT CHANGE */
  TreeNode *find_nearest_node(int x, int y);  /* DO NOT CHANGE */
  int step;

  void buildTree(vector<TreeNode*> input);

  void recur_search(TreeNode *cur, int x, int y, long long int &min_distance, TreeNode **guess);

  // deconstruct function
  int Distory(TreeNode* &Tree)
  {
      if (Tree)			//该根节点非空
      {
          TreeNode *Left_Tree = Tree->lchild;
          TreeNode *Right_Tree = Tree->rchild;
          delete Tree;
          if (Left_Tree)			//左子树非空则释放
              Distory(Left_Tree);
          if (Right_Tree)			//同
              Distory(Right_Tree);
      }
      return 0;
  }

  ~BinaryDimonTree(){
      Distory(root);
  }
};



#endif //C_BINARYDIMEN_TREE_H
