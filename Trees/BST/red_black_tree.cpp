#include "bits/stdc++.h"

using namespace std;

template<typename T>
istream &operator>>(istream &is, vector<T> &v) {
    for (auto &i: v) is >> i;
    return is;
}

template<typename T>
ostream &operator<<(ostream &os, vector<T> v) {
    for (auto &i: v) os << i << ' ';
    return os;
}

long long mod = 998244353;
//Rules That Every Red-Black Tree Follows:
//    1) Every node has a color either red or black.
//    2) The root of the tree is always black.
//    3) There are no two adjacent red nodes (A red node cannot have a red parent or red child).
//    4) Every path from a node (including root) to any of its descendants NULL nodes has the same number of black nodes.
//    5) Every leaf (e.i. NULL node) must be colored BLACK.


struct rb_tree {
    int data;
    int c; // 1 - red, 0 - black
    rb_tree *left;
    rb_tree *right;
    rb_tree *parent;

    rb_tree(int data) : data(data), c(1), left(NULL), right(NULL), parent(NULL) {}
};

rb_tree* root = NULL;

rb_tree* insert(int data, rb_tree *node){
    if(node == NULL)
        return new rb_tree(data);

    if(data < node->data){
        node->left = insert(data, node->left);
        node->left->parent = node;
    } else {
        node->right = insert(data, node->right);
        node->right->parent = node;
    }
    return node;
}

void rotateLeft(rb_tree *temp){
    rb_tree* r = temp->right;
    temp->right = r->left;
    if (temp->right)
        temp->right->parent = temp;
    r->parent = temp->parent;
    if (!temp->parent)
        root = r;
    else if (temp == temp->parent->left)
        temp->parent->left = r;
    else
        temp->parent->right = r;
    r->left = temp;
    temp->parent = r;
}

void rotateRight(rb_tree *temp){
    rb_tree* l = temp->left;
    temp->left = l->right;
    if (temp->left)
        temp->left->parent = temp;
    l->parent = temp->parent;
    if (!temp->parent)
        root = l;
    else if (temp == temp->parent->left)
        temp->parent->left = l;
    else
        temp->parent->right = l;
    l->right = temp;
    temp->parent = l;
}

void fix(rb_tree *pt){
    rb_tree *parent_pt = NULL;
    rb_tree *grand_parent_pt = NULL;

    while ((pt != root) && (pt->c != 0)
           && (pt->parent->c == 1)) {
        parent_pt = pt->parent;
        grand_parent_pt = pt->parent->parent;
        if (parent_pt == grand_parent_pt->left) {
            rb_tree *uncle_pt = grand_parent_pt->right;
            if (uncle_pt != NULL && uncle_pt->c == 1) {
                grand_parent_pt->c = 1;
                parent_pt->c = 0;
                uncle_pt->c = 0;
                pt = grand_parent_pt;
            } else {
                if (pt == parent_pt->right) {
                    rotateLeft(parent_pt);
                    pt = parent_pt;
                    parent_pt = pt->parent;
                }
                rotateRight(grand_parent_pt);
                int t = parent_pt->c;
                parent_pt->c = grand_parent_pt->c;
                grand_parent_pt->c = t;
                pt = parent_pt;
            }
        } else {
            rb_tree *uncle_pt = grand_parent_pt->left;
            if ((uncle_pt != NULL) && (uncle_pt->c == 1)) {
                grand_parent_pt->c = 1;
                parent_pt->c = 0;
                uncle_pt->c = 0;
                pt = grand_parent_pt;
            } else {
                if (pt == parent_pt->left) {
                    rotateRight(parent_pt);
                    pt = parent_pt;
                    parent_pt = pt->parent;
                }
                rotateLeft(grand_parent_pt);
                int t = parent_pt->c;
                parent_pt->c = grand_parent_pt->c;
                grand_parent_pt->c = t;
                pt = parent_pt;
            }
        }
    }
}

void inorder(rb_tree *trav){
    if (trav == NULL)
        return;
    inorder(trav->left);
    printf("%d ", trav->data);
    inorder(trav->right);
}

void solve(){

}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int t;
    cin >> t;
    while(t--)
        solve();
}
