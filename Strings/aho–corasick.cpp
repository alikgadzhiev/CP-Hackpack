#include "bits/stdc++.h"

using namespace std;

struct Trie {
    char ch;
    Trie* parent;
    Trie* child[26];
    bool is_terminal;
    Trie* suffix_link;

//    Trie(){
//        this->parent = NULL;
//        for(int i = 0; i < 26; i++)
//            this->child[i] = NULL;
//    }
};

void insert(string s, Trie* root){
    for(int i = 0; i < (int) s.size(); i++){
        int pos = s[i] - 'a';
        root->child[pos] = new Trie;
        root->child[pos]->parent = root;
        root = root->child[pos];
        root->ch = s[i];
    }
    root->is_terminal = true;
}

bool search(string s, Trie* root){
    for(int i = 0; i < (int) s.size(); i++){
        int pos = s[i] - 'a';
        if(root->child[pos] == NULL)
            return false;
        root = root->child[pos];
    }
    return root->is_terminal;
}

void suffix_link_build(Trie* root){
    queue<Trie*> q;
    q.push(root);
    while(!q.empty()){
        int sz = (int) q.size();
        for(int i = 1; i <= sz; i++){
            Trie *cur = q.front();
            q.pop();
            int pos = cur->ch - 'a';
            if(cur->parent == NULL){
                for(int i = 0; i < 26; i++){
                    if(cur->child[pos] != NULL)
                        q.push(cur->child[pos]);
                }
                continue;
            }
            Trie *par = cur->parent;
            while(par->suffix_link->child[pos] == NULL && par->suffix_link != NULL)
                par = par->suffix_link;
            cur->suffix_link = par->suffix_link;
            for(int i = 0; i < 26; i++){
                if(cur->child[pos] != NULL)
                    q.push(cur->child[pos]);
            }
        }
    }
}

bool find(string s, int ind, Trie* root){
    if(ind >= (int) s.size())
        return false;
    int pos = s[ind];
    if(root->child[pos] != NULL){
        if(root->child[pos]->is_terminal)
            return true;
        return find(s, ind + 1, root->child[pos]);
    }
    Trie* cur = root;
    while(cur->suffix_link->child[pos] == NULL && cur->suffix_link->parent != NULL)
        cur = cur->suffix_link;
    if(cur->suffix_link->child[pos]->is_terminal)
        return true;
    if(root->child[pos] == NULL){
        root->child[pos] = new Trie;
        root->child[pos]->parent = root;
        root->child[pos]->ch = s[ind];
    }
    return find(s, ind + 1, root->child[pos]);
}

int main(){
    // find if p strings contain in s as a substring
    Trie* root = new Trie;
    string s;
    cin >> s;
    int q;
    cin >> q;
    for(int i = 0; i < q; i++){
        string p;
        cin >> p;
        insert(p, root);
    }
    suffix_link_build(root);
    cout << find(s, 0, root) << '\n';
}
