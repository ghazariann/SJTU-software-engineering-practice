#include "Tree.h"

#include <limits.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include <algorithm>
#include <cmath>
#include <fstream>
#include <iostream>
#include <queue>
#include <vector>

using namespace std;

/****************************************************************
 *                    Write your code below
 ****************************************************************/
ostream &operator<<(ostream &out, const TreeNode &b) {
    cout << b.data[0] << " " << b.data[1];
    return out;  // return same ostream object for chaining
}
TreeNode::TreeNode(int x, int y, int level, TreeNode *lt, TreeNode *rt) : level(level), lt(lt), rt(rt) {
    data[0] = x;
    data[1] = y;
};
int TreeNode::getX() {
    return data[0];
}

int TreeNode::getY() {
    return data[1];
}

TreeNode::~TreeNode() {
}

double distance(TreeNode *&cur, int x, int y) {
    return sqrt(pow(cur->getX() - x, 2) + pow(cur->getY() - y, 2));
};

istream &operator>>(istream &in, BinaryDimonTree &tree) {
    int n = 0;
    in >> n;
    for (int i = 0; i < n; i++) {
        int x, y;
        in >> x >> y;
        TreeNode *t = new TreeNode(x, y);
        tree.nodes.push_back(t);
    }
    tree.create();
    return in;  // return in stream object for chaining
}

void BinaryDimonTree::create() {
    int dim = 0;
    root = createNode(nodes, dim);  // 根节点返回值
}

bool tree_cmp_func(TreeNode *n1, TreeNode *n2, int index) {
    if (index == 0) return n1->getX() < n2->getX();
    if (index == 1) return n1->getY() < n2->getY();
    return false;
}

TreeNode* BinaryDimonTree::createNode(vector<TreeNode*> nodes, int& dimension) {
    if (nodes.empty())
        return nullptr;
    sort(nodes.begin(), nodes.end(), [dimension](TreeNode* n1, TreeNode* n2) {
        return tree_cmp_func(n1, n2, dimension);
    });
    int mid = nodes.size() / 2;
    TreeNode* root = new TreeNode(nodes[mid]->getX(), nodes[mid]->getY(), dimension);
    vector<TreeNode*> left_nodes(nodes.begin(), nodes.begin() + mid);
    vector<TreeNode*> right_nodes(nodes.begin() + mid + 1, nodes.end());
    nodes.erase(nodes.begin() + mid);
    dimension = (dimension + 1) % 2;
    root->rt = createNode(right_nodes, dimension);
    root->lt = createNode(left_nodes, dimension);
    return root;
}

TreeNode *BinaryDimonTree::find_nearest_node(int x, int y) {
    TreeNode *gs = nullptr;
    double distance = INT64_MAX;
    recur_search(root, x, y, distance, gs);
    return gs;
}
void BinaryDimonTree::recur_search(TreeNode *cur, int x, int y, double &min_dist, TreeNode *&nearest) {
    if (cur == nullptr) return;
    double d = distance(cur, x, y);
    if (d == min_dist) {
        if (cur->getX() < nearest->getX()) nearest = cur;
        if (cur->getX() == nearest->getX() && cur->getY() < nearest->getY()) nearest = cur;
    }
    if (d < min_dist) {
        min_dist = d;
        nearest = cur;
    }
    int dim = cur->level;
    int dist_to_split_plane = cur->data[dim] - x * ((dim + 1) % 2) - y * (dim % 2);
    if (dist_to_split_plane > 0)
        recur_search(cur->lt, x, y, min_dist, nearest);
    else
        recur_search(cur->rt, x, y, min_dist, nearest);
    if (abs(dist_to_split_plane) > min_dist) return;
    if (dist_to_split_plane > 0)
        recur_search(cur->rt, x, y, min_dist, nearest);
    else
        recur_search(cur->lt, x, y, min_dist, nearest);
}

BinaryDimonTree::BinaryDimonTree() {
    root = nullptr;
}
BinaryDimonTree::~BinaryDimonTree() {
    makeEmpty(root);
}

void BinaryDimonTree::makeEmpty(TreeNode *t) {
    if (t == NULL) return;
    makeEmpty(t->lt);
    makeEmpty(t->rt);
    delete t;
}
