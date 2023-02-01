#include <stdio.h>
#include <stdlib.h>
 
typedef struct node{
    int key;
    int count;
    int height;
    struct node *left;
    struct node *right;
}node;
 
int height(node *x) {
    if (x != NULL) {
        return x->height;
    } else {
        return 0;
    }
}
 
void fixheight(node *x) {
    int hleft = height(x->left);
    int hright = height(x->right);
    if (hleft > hright) {
        x->height = hleft + 1;
    } else {
        x->height = hright + 1;
    }
}
 
int bfactor(node *x) {
    return height(x->right) - height(x->left);
}
 
node* left_rotate(node *x) {
    node *tmp = x->right;
    x->right = tmp->left;
    tmp->left = x;
    fixheight(x);
    fixheight(tmp);
    return tmp;
}
 
node* right_rotate(node *x) {
    node *tmp = x->left;
    x->left = tmp->right;
    tmp->right = x;
    fixheight(x);
    fixheight(tmp);
    return tmp;
}
 
node* balance(node *x) {
    fixheight(x);
    if (bfactor(x) == 2) {
        if (bfactor(x->right) < 0) {
            x->right = right_rotate(x->right);
        }
        return left_rotate(x);
    }
    if (bfactor(x) == -2) {
        if (bfactor(x->left) > 0) {
            x->left = left_rotate(x->left);
        }
        return right_rotate(x);
    }
    return x;
}
 
node* insert(node *root, int k) {
    if (root == NULL) {
        node *tmp = (node*)malloc(sizeof(node));
        tmp->key = k;
        tmp->left = NULL;
        tmp->right = NULL;
        tmp->height = 1;
        root = tmp;
        return root;
    }
    if (k < root->key) {
        root->left = insert(root->left, k);
    } else {
        root->right = insert(root->right, k);
    }
    fixheight(root);
    return root;
}
 
node *search_max(node *x) {
    if (x->right != NULL) {
        return search_max(x->right);
    } else {
        return x;
    }
}
 
node *delete_max(node* x) {
    if (x->right== NULL) {
        return x->left;
    }
 
    x->right = delete_max(x->right);
    return balance(x);
}
 
node *delete(node *x, int k) {
    if (x == NULL) {
        return NULL;
    }
 
    if (k < x->key) {
        x->left = delete(x->left, k);
    } else if (k > x->key) {
        x->right = delete(x->right, k);
    } else {
        node *left = x->left;
        node *right = x->right;
        free(x);
        if (left == NULL) {
            return right;
        }
        node *max = search_max(left);
        max->left = delete_max(left);
        max->right = right;
        return balance(max);
    }
 
    return balance(x);
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
    fin = fopen("deletion.in", "r");
    fout = fopen("deletion.out", "w");
 
    fscanf(fin, "%d", &n);
    node *root = NULL;
 
    for (int i = 0; i < n; i++) {
       fscanf(fin, "%d %*d %*d", &val); 
       root = insert(root, val);
    }
 
    fscanf(fin, "%d", &val);
    if ((root = delete(root, val)) == NULL) {
        fprintf(fout, "%d\n", 0);
    } else {
        fprintf(fout, "%d\n", n-1);
        count(root);
        print_nodes(root, 1, fout);
    }
 
    fclose(fin);
    fclose(fout);
 
    return 0;
}