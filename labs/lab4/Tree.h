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

class TreeNode
{
  friend ostream &operator<<(ostream &out, const TreeNode &b);
  friend class BinaryTree;
  friend class BinaryDimonTree;

private:
  /* data */
  int data[2];
  int level;
  TreeNode *parent, *lt, *rt;

public:
  /* methods */
    TreeNode( int x, int y,int level=0,TreeNode *lt=NULL,TreeNode *rt=NULL);
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

  vector<TreeNode *> nodes;
  void create();
  TreeNode *createNode( vector<TreeNode *> nodes,int &dimension);
  void makeEmpty(TreeNode *t);

public:
  /* methods */
  BinaryDimonTree();          /* DO NOT CHANGE */
  TreeNode *find_nearest_node(int x, int y);  /* DO NOT CHANGE */

  void recur_search(TreeNode *cur, int x, int y, double &min_distance, TreeNode *&guess);
  ~BinaryDimonTree();
};

#endif //C_BINARYDIMEN_TREE_H
