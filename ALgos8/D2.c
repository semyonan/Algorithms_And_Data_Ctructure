#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 
void dfs(int **matrix, int **class, int peak, int n, int *count) {
        (*class)[peak - 1] = (*count);
        for(int i = 0; i < n; i++) {
            if ((matrix[peak-1][i] == 1) && ((*class)[i] == 0)) {
                dfs(matrix, class, i+1, n, count);
            }
        }
}
 
int main() {
    int n, m, x, y, count;
    count = 0;
   
    FILE *fin, *fout;
    fin = fopen("components.in", "r");
    fout = fopen("components.out", "w");
   
    fscanf(fin, "%d %d", &n, &m);
 
    int **adc_matrix = (int**)malloc(sizeof(int*)*n);
    for (int i = 0; i < n; i++) {
        adc_matrix[i] = (int*)malloc(sizeof(int)*n);
        memset(adc_matrix[i], 0, n*sizeof(int));
    }

    int *class = (int*)malloc(sizeof(int*)*n);
    memset(class, 0, n*sizeof(int));
 
    for (int i = 0; i < m; i++) {
        fscanf(fin, "%d %d", &x, &y);
        adc_matrix[x-1][y-1] = 1;
        adc_matrix[y-1][x-1] = 1;
    }
 
    for (int i = 0; i < n; i++) {
        if (class[i] == 0) {
            count++;
            dfs(adc_matrix, &class, i+1, n, &count);
        }
    }
 
    fprintf(fout, "%d\n", count);
 
    for (int i = 0; i < n; i++) {
        fprintf(fout,"%d ", class[i]);
    }
 
    free(adc_matrix);
    fclose(fin);
    fclose(fout);
 
    return 0;
}