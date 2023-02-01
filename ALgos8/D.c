#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
    int color; 
    int distance;
    int next[10000];
    int size;
}node;

void dfs(node *graph, int i, int n, int *count) {
    graph[i].color = 1;
    if ((graph[i].distance == 0) || ((*count) < graph[i].distance)) {
        graph[i].distance = (*count);
    }
    (*count)++;
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
    fin = fopen("pathbge1.in", "r");
    fout = fopen("pathbge1.out", "w");
  
    fscanf(fin, "%d %d", &n, &m);

    node *graph = (node*)malloc(sizeof(node)*n);

    for (int i = 0; i < n; i++) {
        graph[i].color = 0;
        graph[i].size = 0;
        graph[i].distance = 0;
        memset(graph[i].next, 0, 10000*sizeof(int));
    }

    for (int i = 0; i < m; i++) {
        fscanf(fin, "%d %d", &x, &y);
        graph[x-1].next[graph[x-1].size] = y-1;
        graph[x-1].size++;
        graph[y-1].next[graph[y-1].size] = x-1;
        graph[y-1].size++;
    }

    dfs(graph, 0, n, &count);

    for (int i = 0; i < n; i++) {
        fprintf(fout,"%d ", graph[i].distance);
    }

    free(graph);
    fclose(fin);
    fclose(fout);

    return 0;
}