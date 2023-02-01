#include <stdio.h>
#include <malloc.h>

int main()
{
        int n, i, j, key;

        FILE *fin, *fout;
        fin = fopen("smallsort.in", "r");
        fout = fopen("smallsort.out", "w");
        
        fscanf (fin, "%d", &n);
        int *a;
        a = (int*)malloc(n * sizeof(int));
        for (i = 0; i < n; ++i ) {
            fscanf(fin, "%d", &a[i]);
        }

        for (i = 1; i < n; ++i) {
            key = a[i];
            j = i-1;
            while (a[j] > key && j >= 0) {
                a[j+1] = a[j];
                --j;
            }
            a[j+1] = key;
        }
        
        for ( i = 0 ; i < n ; ++i) {
            fprintf(fout, "%d ", a[i]);
        }

        free(a);
        fclose(fin);
        fclose(fout);
        return 0;
    
}