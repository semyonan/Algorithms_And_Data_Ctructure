#include <stdio.h>
#include <stdlib.h>
 
typedef struct node {
    int val;
    int left;
    int right;
    int balance;
}node;
 
int balance(node a[], int ind) {
    if (a == NULL) {
        return 0;
    }
     
    if ((a[ind - 1].left == 0) && (a[ind-1].right == 0)) {
        a[ind - 1].balance = 0;
        return 1;
    } else if (a[ind-1].left == 0) {
        int right = balance(a, a[ind-1].right);
        a[ind-1].balance = right;
        return 1 + right;
    } else if (a[ind-1].right == 0) {
        int left = balance(a, a[ind-1].left);
        a[ind-1].balance = -left;
        return 1 + left;
    } 
     
    int left = balance(a, a[ind - 1].left);
    int right = balance(a, a[ind - 1].right); 
    a[ind - 1].balance = right - left;
    if (left >= right) {
        return 1 + left;
    } else {
        return 1 + right;
    }
}
 
int main() {
    int n;
 
    FILE *fin, *fout;
    fin = fopen("balance.in", "r");
    fout = fopen("balance.out", "w");
 
    fscanf(fin, "%d", &n);
    node *a = NULL;
    if (n != 0) {
       a = (node*)malloc(sizeof(node)*n); 
    }
 
    for (int i = 0; i < n; i++) {
       fscanf(fin, "%d %d %d", &a[i].val, &a[i].left, &a[i].right); 
    }
 
    balance(a, 1);
 
    for (int i = 0; i < n; i++) {
        fprintf(fout, "%d\n", a[i].balance);
    }
 
    fclose(fin);
    fclose(fout);
    free(a);
     
 
    return 0;
}