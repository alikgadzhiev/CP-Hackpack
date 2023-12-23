#include <iostream>

using namespace std;

typedef struct avlnode{
    int key;
    int data;
    int height;
    struct avlnode *left;
    struct avlnode *right;
} avlnode;

typedef avlnode *avltree;

void deleteTree(avltree tree){
    if(tree != NULL){
        deleteTree(tree->left);
        deleteTree(tree->right);
        free(tree);
    }
}

avltree newNode(int key, int data){
    avltree tree = (avltree) malloc(sizeof(avlnode));
    tree->left = tree->right = NULL;
    tree->key = key;
    tree->data = data;
    tree->height = 1;
    return tree;
}

int max(int a, int b){
    return (a > b ? a : b);
}

int height(avltree tree){
    return tree ? tree->height : 0;
}

int heightDiff(avltree tree){
    return height(tree->right) - height(tree->left);
}

void updateHeight(avltree tree){
    tree->height = max(height(tree->left), height(tree->right)) + 1;
}

avltree rotateRight(avltree old_node){
    avltree new_node = old_node->left;
    old_node->left = new_node->right;
    new_node->right = old_node;

    updateHeight(new_node);
    updateHeight(old_node);

    return new_node;
}

avltree rotateLeft(avltree tree){
    avltree right = tree->right;
    tree->right = right->left;
    right->left = tree;

    updateHeight(right);
    updateHeight(tree);

    return right;
}

avltree balance(avltree tree){
    updateHeight(tree);

    if(heightDiff(tree) == 2){
        if(heightDiff(tree->right) < 0){
            tree->right = rotateRight(tree->right);
        }
        return rotateLeft(tree);
    }

    if(heightDiff(tree) == -2){
        if(heightDiff(tree->left) > 0){
            tree->left = rotateLeft(tree->left);
        }

        return rotateRight(tree);
    }

    return tree;
}

avltree findMin(avltree tree){
    if(tree != NULL){
        while(tree->left)
            tree = tree->left;
    }
    return tree;
}

avltree findMax(avltree tree){
    if(tree != NULL){
        while(tree->right)
            tree = tree->right;
    }
    return tree;
}

avltree find(avltree tree, int key){
    if(tree == NULL || tree->key == key) {
        return tree;
    } else if(tree->key > key) {
        return find(tree->left, key);
    } else {
        return find(tree->right, key);
    }
    return NULL;
}

avltree deleteMin(avltree tree){
    if(tree->left == NULL){
        return tree->right;
    }
    tree->left = deleteMin(tree->left);
    return balance(tree);
}

avltree insert(avltree tree, int key, int data){
    if(tree == NULL) {
        return newNode(key, data);
    }
    if(tree->key == key){
        tree->data = data;
        return tree;
    } else if(tree->key > key){
        tree->left = insert(tree->left, key, data);
    } else if(tree->key < key){
        tree->right = insert(tree->right, key, data);
    }

    return balance(tree);
}

avltree deleteNode(avltree tree, int key){
    if(tree == NULL)
        return NULL;
    if(tree->key > key){
        tree->left = deleteNode(tree->left, key);
    } else if(tree->key < key){
        tree->right = deleteNode(tree->right, key);
    } else if(tree->key == key){
        avltree left = tree->left;
        avltree right = tree->right;

        free(tree);

        if(right == NULL){
            return left;
        }

        avltree rightMin = findMin(right);
        rightMin->right = deleteMin(right);
        rightMin->left = left;

        return balance(rightMin);
    }

    return balance(tree);
}

int main(){

}
