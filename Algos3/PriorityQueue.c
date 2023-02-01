#include <stdio.h>
#include <string.h>
#include <limits.h>

typedef struct Elem{
    int line;
    int val;
}Elem_t;

typedef struct Tree{
    Elem_t *arr;
    int size;
    int len;
}Tree_t;

void tree_siftup(Tree_t* ptree, int i) {
    Elem_t tmp;
    int j = (i-1)/2;
    while (i > 0 && ptree->arr[j].val > ptree->arr[i].val) {
        tmp = ptree->arr[j];
        ptree->arr[j] = ptree->arr[i];
        ptree->arr[i] = tmp;
        i = j;
        j = (i-1)/2;
    }
}

void tree_insert(Tree_t* ptree, int val, int line) {
    if(ptree->len == ptree->size) {
        ptree->size *= 2;
        ptree->arr = (Elem_t*)realloc(ptree->arr,ptree->size*sizeof(Elem_t));
        if (!ptree->arr) {
            ptree->size = ptree->len = 0;
            return;
        }
    }
    ptree->arr[ptree->len].val = val;
    ptree->arr[ptree->len].line = line;
    ptree->len += 1;
    tree_siftup(ptree, ptree->len-1);
}

void tree_siftdown(Tree_t* ptree, int i) {
    Elem_t tmp;
    int root;
    while (2*i+1 < ptree->len) {
        root = i;
        if ((ptree->arr[2*i+1].val < ptree->arr[i].val) && ((2*i+2 >= ptree->len) || (ptree->arr[2*i+1].val <= ptree->arr[2*i+2].val))){
            root = 2*i+1;
        }
        else if ((2*i+2 < ptree->len) && (ptree->arr[2*i+2].val < ptree->arr[i].val)) {
            root = 2*i+2;
        }
        if (root == i) {
            break;
        } 
        tmp = ptree->arr[i];
        ptree->arr[i] = ptree->arr[root];
        ptree->arr[root] = tmp;
        i = root;
    }
}

int tree_ex_min(Tree_t* ptree) {
    int val = INT_MAX;
    if (ptree->len > 0) {
        val = ptree->arr[0].val;
        ptree->arr[0] = ptree->arr[ptree->len-1];
        ptree->len -= 1;
        tree_siftdown(ptree, 0);
    }
    return val;
}

void decreaseKey(Tree_t *ptree, int line, int nval) {
    for (int i = 0; i < ptree->len; i++) {
        if (ptree->arr[i].line == line) {
            ptree->arr[i].val = nval;
            tree_siftup(ptree, i);
            break;
        }
    }
}

int main() {
    Tree_t tree;
    tree.arr = (Elem_t *)malloc(2048*sizeof(Elem_t));
    tree.size = 2048;
    tree.len = 0;

    FILE *fin, *fout;
    fin = fopen("priorityqueue.in", "r");
    fout = fopen("priorityqueue.out", "w");

    char str[100];
    char *comand;
    int val, line, curline;
    line = 0;
    curline = 0;
    
    while(!feof(fin)) {
        curline++;
        val = 0;
        line = 0;
        str[0] = '\0';
        fgets(str, 100, fin);
        comand = strtok(str, " \n\t");
        if (comand != NULL) {
            if (strcmp(comand, "push") == 0) {
                val = atoi(strtok(NULL, " \n\t"));
                tree_insert(&tree, val, curline);
            }
            else if (strcmp(comand, "extract-min") == 0) {
                val = tree_ex_min(&tree);
                if (val < INT_MAX) {
                    fprintf(fout, "%d\n", val);
                } else {
                    fprintf(fout, "*\n");
                }
            }
            else if (strcmp(comand, "decrease-key") == 0) {
                line = atoi(strtok(NULL, " \n\t"));
                val = atoi(strtok(NULL, " \n\t"));
                decreaseKey(&tree, line, val);
            }
        }
    }

    free(tree.arr);

    fclose(fin);
    fclose(fout);

    return 0;
}
