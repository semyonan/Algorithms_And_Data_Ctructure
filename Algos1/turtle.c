#include <stdio.h>
#include <malloc.h>

int main()
{
        int h, w, i, j;

        FILE *fin, *fout;
        fin = fopen("turtle.in", "r");
        fout = fopen("turtle.out", "w");
        
        fscanf (fin, "%d\t%d", &h, &w);
        int **a;
        a = (int**)malloc(h * sizeof(int));
        for (i = 0; i < h; ++i ) {
            a[i] = malloc(w * sizeof(int));
            
            for (j = 0; j < w; ++j) {
                fscanf(fin, "%d", &a[i][j]);
            }
        }

        for (i = h-1; i > -1; --i) {

            for (j = 0; j < w; ++j)  {

                if (i != h-1 || j != 0) {

                    if (i == h-1) {
                        a[i][j] += a[i][j-1];
                    }

                    else if (j == 0) {
                        a[i][j] += a[i+1][j];
                    }

                    else {
                        if (a[i+1][j] > a[i][j-1]) {
                        a[i][j] += a[i+1][j];
                        }

                        else {
                            a[i][j] += a[i][j-1];
                        }
                    }
                }
            }
        }

        fprintf (fout, "%d", a[0][w-1]);

        free(a);
        fclose(fin);
        fclose(fout);
        return 0;
    
}