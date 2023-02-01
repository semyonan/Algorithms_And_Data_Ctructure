#include <stdio.h>
#include <stdlib.h>
#include <string.h>
  
typedef struct list {
    node node;
    struct list *next;
}list;
  
void push(list **head, node data) {
    list *tmp = (list*)malloc(sizeof(list));
    tmp->node = data;
    tmp->next = NULL;
    if ((*head) != NULL) {
        (*head)->next = tmp;
    }
    (*head) = tmp;
}
  
node pop(list **tail) {
    list* Nextel = NULL;
    node val;
    if (tail == NULL) {
        exit(-1);
    }
    Nextel = (*tail);
    val = Nextel->node;
    (*tail) = Nextel->next;
    free(Nextel);
    return val;
}  
 
typedef struct Node {
    int color; 
    int comp;
    int next[200000];
    int size;
}node;
 
void bfs(node *graph, int i, int n, int count) {
    list *head = NULL;
    list *tail = NULL;
    graph[i].color = 1;
    graph[i].comp = count;
    while()
    for (int j = 0; j < graph[i].size; j++) {
        if (graph[graph[i].next[j]].color == 0) {
            dfs(graph , graph[i].next[j], n, count);
        }
    }
    graph[i].color = 2;
    return;
}
 
int main() {
    int n, m, x, y, count;
    count = 0;
   
    FILE *fin, *fout;
    fin = fopen("components.in", "r");
    fout = fopen("components.out", "w");
   
    fscanf(fin, "%d %d", &n, &m);
 
    node *graph = (node*)malloc(sizeof(node)*n);
 
    for (int i = 0; i < n; i++) {
        graph[i].color = 0;
        graph[i].size = 0;
        graph[i].comp = 0;
        memset(graph[i].next, 0, 200000*sizeof(int));
    }
 
    for (int i = 0; i < m; i++) {
        fscanf(fin, "%d %d", &x, &y);
        graph[x-1].next[graph[x-1].size] = y-1;
        graph[x-1].size++;
        graph[y-1].next[graph[y-1].size] = x-1;
        graph[y-1].size++;
    }
 
    for (int i = 0; i < n; i++) {
        if (graph[i].color == 0) {
            count++;
            dfs(graph, i, n, count);
        }
    }
 
    fprintf(fout, "%d\n", count);
 
    for (int i = 0; i < n; i++) {
        fprintf(fout,"%d ", graph[i].comp);
    }
 
    free(graph);
    fclose(fin);
    fclose(fout);
 
    return 0;
}