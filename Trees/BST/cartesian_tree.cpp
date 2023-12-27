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

struct CartesianTree{
    int key, prior;
    CartesianTree *left, *right;
    CartesianTree() {}
    CartesianTree(int key, int prior) : key(key), prior(prior), left(NULL), right(NULL) {}
};

CartesianTree *new_node(int key, int prior){
    CartesianTree *cur = new CartesianTree(key, prior);
    return cur;
}

CartesianTree* find(int key, CartesianTree *root){
    if(root == NULL)
        return NULL;

    if(root->key == key)
        return root;
    else if(root->key < key)
        return find(key, root->right);
    else if(root->key > key)
        return find(key, root->left);
}

CartesianTree* merge(CartesianTree *a, CartesianTree *b){
    if(a == NULL) return b;
    if(b == NULL) return a;

    if(a->prior > b->prior){
        merge(a->left, b);
        return a;
    } else {
        merge(a, b->left);
        return b;
    }
}

pair<CartesianTree*, CartesianTree*> split(int key, CartesianTree *root){
    if(root == NULL) return {NULL, NULL};

    if(root->key < key){
        auto [l, r] = split(key, root->right);
        root->right = l;
        return {root, r};
    } else {
        auto [l, r] = split(key, root->left);
        root->left = l;
        return {l, root};
    }
}

CartesianTree* remove(int key, CartesianTree *root){
    if(root == NULL) return NULL;

    if(root->key == key){
        root = merge(root->left, root->right);
    } else {
        if(key < root->key)
            root->left = remove(key, root->left);
        else
            root->right = remove(key, root->right);
    }
    return root;
}

CartesianTree* insert(int key, int prior, CartesianTree *root){
    if(root == NULL) return new CartesianTree(key, prior);

    auto [l, r] = split(key, root);
    CartesianTree *node = new_node(key, prior);
    CartesianTree *ans = merge(l, node);
    ans = merge(ans, r);
    return ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
}
