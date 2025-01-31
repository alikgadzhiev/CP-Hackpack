struct Node {
    int key, priority, size;
    Node* left;
    Node* right;
    Node(int key) : key(key), priority(rand()), size(1), left(nullptr), right(nullptr) {}
};

int getSize(Node* t) {
    return t ? t->size : 0;
}

void update(Node* t) {
    if (t) {
        int lsize = getSize(t->left), rsize = getSize(t->right);
        t->size = lsize + 1 + rsize;
    }
}

void split(Node* t, int key, Node*& l, Node*& r) { // (-inf, key) and [key, +inf)
    if (!t) {
        l = r = nullptr;
        return;
    }
    if (key <= t->key) {
        split(t->left, key, l, t->left);
        r = t;
    } else {
        split(t->right, key, t->right, r);
        l = t;
    }
    update(t);
}

Node* merge(Node* l, Node* r) {
    if (!l || !r) return l ? l : r;
    if (l->priority > r->priority) {
        l->right = merge(l->right, r);
        update(l);
        return l;
    } else {
        r->left = merge(l, r->left);
        update(r);
        return r;
    }
}

Node* insert(Node* t, int key) {
    Node* l, *r;
    split(t, key, l, r);
    return merge(merge(l, new Node(key)), r);
}

Node* erase(Node* t, int key) {
    Node *t1, *t2, *t3, *t4;
    split(t, key, t1, t4);

    split(t4, key + 1, t2, t3);

    free(t2);
    return merge(t1, t3);
}

// FOR DEBUGGING
std::ostream &operator<< (std::ostream &out, Node &a) { 
 return out << "(" << a.key << ' ' << a.size << ")"; 
} 
using TreeNode = Node; 
 
void print_nodes(const string &padding, const string &edge, TreeNode *node, bool has_left_sibling) 
{ 
    if (node != NULL) { // recursion stopping condition 
        cout << endl << padding << edge << *node; // printing the current node along with the needed padding and connecting edge 
 
        // If the current node is a leaf, we wish to add some distance from it to another node that is in an upper 
        // level in the tree, and is possibly yet to be printed.. 
        if ((node->left == NULL) && (node->right == NULL)) { 
            cout << endl << padding; // adding a new line along with the padding 
            if (has_left_sibling) { // also, if the leaf has a left sibling, we wish to extend the edge between them 
                cout << "|"; 
            } 
        } else {  
            // if the current node is not a leaf, we add some spacing to the current padding, based on whether 
            // the current node has a left sibling or not 
            string new_padding = padding + (has_left_sibling ? "|    " : "     "); 
            print_nodes(new_padding, "|----", node->right, node->left != NULL); // recurring with the right child and the new padding 
            print_nodes(new_padding, "|____", node->left, false); // recurring with the left child and the new padding 
        } 
    } 
} /* print_nodes */ 
 
// main function to HORIZONTALLY print a binary tree 
void print_tree(TreeNode *root) 
{ 
    // checking validity of root pointer 
    if (root == NULL) { 
        return; 
    } 
 
    // printing the key of the root, and moving on to print the rest of the nodes, using the utility function (initial padding is an empty string) 
    cout << *root; 
    print_nodes("", "|----", root->right, root->left != NULL); // printing the nodes on the right (similar to the recursive call inside print_nodes) 
    print_nodes("", "|____", root->left, false); // printing the nodes on the left (note that the left child cannot have a left sibling) 
 cout << '\n'; 
} /* print_tree */
