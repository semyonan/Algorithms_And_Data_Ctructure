#include <stdio.h>

int isHeap(int arr[],int i,int n) {
    if (((2*i+1)<n) && (arr[i] <= arr[2*i+1])) {
        return 1;
    } else {
        return 0;
    }
    if (((2*i+2)<n) && (arr[i] <= arr[2*i+2])) {
        return 1;
    } else {
        return 0;
    }
}

int main() {
    int n, result;
    result = 1;

    FILE *fin, *fout;
    fin = fopen("isheap.in", "r");
    fout = fopen("isheap.out", "w");

    fscanf(fin, "%d", &n);

    int *a;
    a = (int*)malloc(n*sizeof(int));
    for (int i = 0; i < n; i++) {
        fscanf(fin, "%d", &a[i]);
    }

    for(int i = 1; i<n/2; i++) {
        if (isHeap(a, i-1, n) == 0) {
            result = 0;
            break;
        }
    }

    if (result == 1) {
        fprintf(fout, "YES\n");
    } else {
        fprintf(fout, "NO\n");
    }

    fclose(fin);
    fclose(fout);
    free(a);



    return 0;
}