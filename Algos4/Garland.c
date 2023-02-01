#include <stdio.h>
#include <stdlib.h>

int main() {
    double answer = 0.0;
    int n = 0;

    FILE *fin, *fout;
    fin = fopen("garland.in", "r");
    fout = fopen("garland.out", "w");

    fscanf(fin, "%d ", &n);
    double *h;
    h = (double*)malloc(n * sizeof(double));
    for( int i = 0; i < n; i++) {
        h[i] = 0.0;
    }

    fscanf(fin, "%lf\n", &h[0]);

    double l = 0;
    double r = h[0];
    while (r - l > 0.0000001) {
        h[1] = (l + r) / 2;
        int flag = 1;
        for (int i = 2; i < n; i++) {
            h[i] = (2 * h[i - 1] + 2 - h[i-2]);
            if (h[i] < 0) {
                flag = 0;
                break;
            }
        }
        if (flag == 1) {
            r = h[1];
        }
        else {
            l = h[1];
        }
    }
        
    fprintf(fout, "%.2lf\n", h[n-1]);

    fclose(fin);
    fclose(fout);
    free(h);

    return 0;
}