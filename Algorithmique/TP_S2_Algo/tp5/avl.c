#include <stdio.h>
#include <stdlib.h>
#include "avl.h"


int max(int a, int b) {
	if (a>b) {
		return a;
	}
	else {
		return b;
	}
}

struct avl * avlCreateNode(int key) {
    struct avl * a = malloc(sizeof(struct avl));
    a->key = key;
    a->left = NULL;
    a->right = NULL;
    return a;
}

int avlHeight(struct avl * root) {
    if (!root){
        return 0;
    }
    else{
        return 1 + max(avlHeight(root->left), avlHeight(root->right));
    }
}

int avlGetBalance(struct avl * root) {
    return (avlHeight(root->left) - avlHeight(root->right));
}

struct avl * avlRotateRight(struct avl * y) {
    if (!y || !y->left){return y;}

    struct avl * pivot = y->left;
    y->left = pivot->right;
    pivot->right = y;
    return pivot;

}

struct avl * avlRotateLeft(struct avl * x) {
    if (!x || !x->right){return x;}

    struct avl * pivot = x->right;
    x->right = pivot->left;
    pivot->left = x;
    return pivot;

}

struct avl * avlRotateLeftRight(struct avl * root){
    root = avlRotateLeft(root->left);
    root = avlRotateRight(root);
    return root;
}

struct avl * avlRotateRightLeft(struct avl * root){
    root = avlRotateRight(root->right);
    root = avlRotateLeft(root);
    return root;
}

struct avl * avlInsert(struct avl * root, int key) {
    if (root == NULL) {
        root = avlCreateNode(key);
    }

    if (key < root->key) {
        root->left = avlInsert(root->left, key);
    } else if (key > root->key){
        root->right = avlInsert(root->right, key);
    }

    int balance = avlGetBalance(root);

    if (balance==2){
        if (avlGetBalance(root->left)>=1){
            root = avlRotateRight(root);
        }
        else {
            root = avlRotateLeftRight(root);
        }
    }

    if (balance==-2){
        if (avlGetBalance(root->right)<=0){
            root = avlRotateLeft(root);
        }
        else{
            root = avlRotateRightLeft(root);
        }
    }

    return root;

    }

struct avl * avlMinValue(struct avl * root) {
    if (root->right==NULL && root->left == NULL){
        return root;
    }
    return avlMinValue(root->left);
}

struct avl * avlDelete(struct avl * root, int key) {
    if (root==NULL){return root;}
    if (key==root->key){
        if (root->left == NULL || root->right == NULL){
            struct avl * temp = root->left ? root->left : root->right;
            free(root);
            return temp;
        }
        else{
            struct avl * temp = avlMinValue(root->right);
            root->key = temp->key;
            root->right = avlDelete(root->right, temp->key);
        }
    }
    else if(key<root->key){
        root->left = avlDelete(root->left, key);
    }
    else{
        root->right = avlDelete(root->right, key);
    }

    if (!root){return NULL;}
    int balance = avlGetBalance(root);

    if (balance==2){
        if (avlGetBalance(root->left)>=1){
            root = avlRotateRight(root);
        }
        else {
            root = avlRotateLeftRight(root);
        }
    }

    if (balance==-2){
        if (avlGetBalance(root->right)<=0){
            root = avlRotateLeft(root);
        }
        else{
            root = avlRotateRightLeft(root);
        }
    }

    return root;
}

void avlFree(struct avl * root) {
    if (root){
        avlFree(root->left);
        avlFree(root->right);
        free(root);
    }
}

void avlDisplay(struct avl * root) {
    if (root == NULL) {
        printf("[]");
        return;
    }
    printf("%d [", root->key);
    avlDisplay(root->left);
    printf("] [");
    avlDisplay(root->right);
    printf("]");
}

