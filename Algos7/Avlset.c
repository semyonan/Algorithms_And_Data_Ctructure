#include <stdio.h>
 
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
    if (x == NULL) {
        return 0;
    } else {
        return height(x->right) - height(x->left);
    }
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
    return balance(root);
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
 
node *search(node *root, int x) {
    while (root != NULL) {
        if (root->key == x) {
            return root;
        } else if (x < root->key) {
            root = root->left;
        } else if (x > root->key) {
            root = root->right;
        }
    }
    return root;
}
 
int main() {
    int n;
    int val = 0;
    char op = 0;
 
    FILE *fin, *fout;
    fin = fopen("avlset.in", "r");
    fout = fopen("avlset.out", "w");
 
    fscanf(fin, "%d\n", &n);
    node *root = NULL;
 
    for (int i = 0; i < n; i++) {
        fscanf(fin, "%c %d\n", &op, &val); 
 
        if (op == 'A') {
            root = insert(root, val);
            fprintf(fout, "%d\n", bfactor(root));
        } else if (op == 'D') {
            root = delete(root, val);
            fprintf(fout, "%d\n", bfactor(root));
        } else {
            if (search(root, val) != NULL) {
                fprintf(fout, "Y\n");
            } else {
                fprintf(fout, "N\n");
            }
        }
    }
 
    fclose(fin);
    fclose(fout);
 
    return 0;
}