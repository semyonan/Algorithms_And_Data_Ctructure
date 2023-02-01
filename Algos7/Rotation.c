#include <stdio.h>
#include <stdlib.h>
 
typedef struct node{
    int key;
    int count;
    struct node *left;
    struct node *right;
}node;
  
node* insert(node *root, int k) {
    if (root == NULL) {
        node *tmp = (node*)malloc(sizeof(node));
        tmp->key = k;
        tmp->left = NULL;
        tmp->right = NULL;
        root = tmp;
        return root;
    }
    if (k < root->key) {
        root->left = insert(root->left, k);
    } else if (k > root->key) {
        root->right = insert(root->right, k);
    }
    return root;
}
 
int height(node *x) {
    if (x == NULL) {
        return 0;
    }
 
    if ((x->left == NULL) && (x->right == NULL)) {
        return 1;
    } else if (x->left == NULL) {
        return 1 + height(x->right);
    } else if (x->right == NULL) {
        return 1 + height(x->left);
    } 
     
    int left = height(x->left);
    int right = height(x->right); 
    if (left >= right) {
        return 1 + left;
    } else {
        return 1 + right;
    }
}
 
node* left_rotate(node *x) {
    node *tmp = x->right;
    x->right = tmp->left;
    tmp->left = x;
    return tmp;
}
 
node* right_rotate(node *x) {
    node *tmp = x->left;
    x->left = tmp->right;
    tmp->right = x;
    return tmp;
}
 
node* big_rotate(node *x) {
    x->right = right_rotate(x->right);
    return left_rotate(x);
}
 
int count(node *x) {
    if (x == NULL) {
        return 0;
    }
    if ((x->left == NULL) && (x->right == NULL)) {
        x->count = 0;
        return 1;
    } else if (x->left == NULL) {
        x->count = count(x->right);
        return x->count + 1;
    } else if (x->right == NULL) {
        x->count = count(x->left);
        return x->count + 1;
    } 
     
    x->count = count(x->left) + count(x->right);
    return x->count + 1;
}   
 
void print_nodes (node *x, int count, FILE *fout) {
    fprintf(fout, "%d ", x->key);
 
    if (x->left == NULL) {
        fprintf(fout, "%d ", 0);
    } else {
        count++;
        fprintf(fout, "%d ", count);
    }
 
    if (x->right == NULL) {
        fprintf(fout, "%d\n", 0);
    } else {
        if (x->left != NULL) {
            fprintf(fout, "%d\n", count + x->left->count + 1);
        } else {
            fprintf(fout, "%d\n", count + 1);
        }
    }
 
    if(x->left != NULL) {
        print_nodes(x->left, count, fout);
    }  
 
    if (x->right != NULL) {
        if (x->left != NULL) {
            print_nodes(x->right, count + x->left->count + 1, fout);
        } else {
            print_nodes(x->right, count + 1, fout);
        }
    }
}
 
int main() {
    int n;
    int val;
 
    FILE *fin, *fout;
    fin = fopen("rotation.in", "r");
    fout = fopen("rotation.out", "w");
 
    fscanf(fin, "%d", &n);
    node *root = NULL;
 
    for (int i = 0; i < n; i++) {
       fscanf(fin, "%d %*d %*d", &val); 
       root = insert(root, val);
    }
 
    if (height(root->right->right) - height(root->right->left) >= 0) {
        root = left_rotate(root);
    } else {
        root = big_rotate(root);
    }
 
    fprintf(fout, "%d\n", n);
 
    root->count = count(root);
 
    print_nodes(root, 1, fout);
 
    fclose(fin);
    fclose(fout);
 
    return 0;
}