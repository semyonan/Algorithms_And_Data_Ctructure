#include <stdio.h>
#include <malloc.h>

int main() {
    int n, i, c;

    FILE *fin, *fout;
    fin = fopen("antiqs.in", "r");
    fout = fopen("antiqs.out", "w");
        
    fscanf (fin, "%d", &n);
    int *a;
    a = (int*)malloc(n * sizeof(int));
    for (i = 0; i < n; ++i ) {
        a[i] = i + 1;
    }   

    for (i = 2; i < n; ++i) {
        c = a[i];
        a[i] = a[i/2];
        a[i/2] = c;
    }

    for (i = 0 ; i < n ; ++i) {
        fprintf(fout, "%d ", a[i]);
    }

    free(a);
    fclose(fin);
    fclose(fout); 

    return 0;
}