#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    int n, x;
    int sum = 0;
  
    FILE *fin, *fout;
    fin = fopen("input.txt", "r");
    fout = fopen("output.txt", "w");
  
    fscanf(fin, "%d", &n);

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            fscanf(fin, "%d ", &x);
            if (x == 1) {
                sum++;
            }
        }
    }

    if (sum%2 == 0) {
        fprintf(fout, "YES");
    } else {
        fprintf(fout, "NO");
    }

    fclose(fin);
    fclose(fout);

    return 0;
}