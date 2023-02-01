#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    int n, m, x, y, flag;
    flag = 0;

    FILE *fin, *fout;
    fin = fopen("input.txt", "r");
    fout = fopen("output.txt", "w");
  
    fscanf(fin, "%d %d", &n, &m);

    int **adc_matrix = (int**)malloc(sizeof(int*)*n);
    for (int i = 0; i < n; i++) {
        adc_matrix[i] = (int*)malloc(sizeof(int)*n);
        memset(adc_matrix[i], 0, n*sizeof(int));
    }

    for (int i = 0; i < m; i++) {
        fscanf(fin, "%d %d", &x, &y);
        if (adc_matrix[x-1][y-1] == 1) {
            fprintf(fout, "YES");
            flag = 1;
            break;
        } else {
            if (adc_matrix[y-1][x-1] == 1) {
                fprintf(fout, "YES");
                flag = 1;
                break;
            }
            adc_matrix[x-1][y-1] = 1;
        }
    }
    
    if (flag == 0) {
        fprintf(fout, "NO");
    }


    free(adc_matrix);
    fclose(fin);
    fclose(fout);

    return 0;
}