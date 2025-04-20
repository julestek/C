#include <stdio.h>
#include <stdlib.h>
#include "bst.h"

struct bst * bstCreateNode(int key) {
    struct bst * noeud = malloc(sizeof(struct bst));
    noeud->key = key;
    noeud->left = NULL;
    noeud->right = NULL;
    return noeud;
}

void bstInorderTraversal(struct bst * root) {

    if (root != NULL){
        bstInorderTraversal(root->left);
        printf("%d ", root->key);
        bstInorderTraversal(root->right);
    }
}

struct bst * bstInsert(struct bst * root, int key) {
    if (root == NULL) {
        return bstCreateNode(key);
    }

    if (key < root->key) {
        root->left = bstInsert(root->left, key);
    } else if (key > root->key){
        root->right = bstInsert(root->right, key);
    }
    return root;
}

struct bst * bstMinValue(struct bst * root) {
    if (root->right==NULL && root->left == NULL){
        return root;
    }
    return bstMinValue(root->left);
}

struct bst * bstDelete(struct bst * root, int key) {
    if (root==NULL){return root;}
    if (key==root->key){
        if (root->left && root->right==NULL){
            root = NULL;
        }
        else if (root->left == NULL || root->right == NULL){
            struct avl * temp = root->left ? root->left : root->right;
            free(root);
            return temp;
        }
        else{
            struct bst * temp = bstMinValue(root->right);
            root->key = temp->key;
            root->right = bstDelete(root->right, temp->key);
        }
    }
    else if(key<root->key){
        root->left = bstDelete(root->left, key);
    }
    else{
        root->right = bstDelete(root->right, key);
    }
    return root;
}

void bstFree(struct bst * root) {
    if (root){
        bstFree(root->left);
        bstFree(root->right);
        free(root);
    }
}

void bstDisplay(struct bst * root) {
    if (root == NULL) {
        printf("[]");
        return;
    }
    printf("%d [", root->key);
    bstDisplay(root->left);
    printf("] [");
    bstDisplay(root->right);
    printf("]");
}
