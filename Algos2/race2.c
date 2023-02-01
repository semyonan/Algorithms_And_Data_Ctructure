#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void merge ( char *contry[], char *name[], char *result1[], char *result2[], int left, int mid, int right) {
    int it1 = 0;
    int it2 = 0;

    while ((left + it1 < mid) && (mid + it2 <= right)) {
        if (strcmp( contry[left + it1], contry[mid + it2]) <= 0) {
            result1[it1 + it2] = contry[left + it1];
            result2[it1 + it2] = name[left + it1];
            it1++;
        }
        else {
            result1[it1 + it2] = contry[mid + it2];
            result2[it1 + it2] = name[mid + it2];
            it2++;
        }
    }

    while (left + it1 < mid) {
        result1[it1 + it2] = contry[left + it1];
        result2[it1 + it2] = name[left + it1];
        it1++;
    }

    while (mid + it2 <= right) {
        result1[it1 + it2] = contry[mid + it2];
        result2[it1 + it2] = name[mid + it2];
        it2++;
    }

    for (int i = 0; i < it1 + it2; i++) {
        contry[left + i] = result1[i];
        name[left + i] = result2[i];
    }

}

void mergeSort( char *a[], char *b[], char *bufc[], char *bufn[], int left, int right) {
    if (left >= right) {
        return;
    }
            
    int mid = (left + right)/2 + 1;
    mergeSort(a, b, bufc, bufn, left, mid - 1);
    mergeSort(a, b, bufc, bufn, mid, right);
    merge(a, b, bufc, bufn, left, mid, right);

}  


int main()
{
    int n, i, j;

    FILE *fin, *fout;
    fin = fopen("race.in", "r");
    fout = fopen("race.out", "w");
        
    fscanf (fin, "%d", &n);
    char **a, **b, **bufc, **bufn;
    a = (char**)malloc(n * sizeof(char*));
    b = (char**)malloc(n * sizeof(char*));
    bufc = (char**)malloc(n * sizeof(char*));
    bufn = (char**)malloc(n * sizeof(char*));
    for (i = 0; i < n; ++i ) {
        a[i] = (char*)malloc(10 * sizeof(char));
        b[i] = (char*)malloc(10 * sizeof(char));
        bufc[i] = (char*)malloc(10 * sizeof(char));
        bufn[i] = (char*)malloc(10 * sizeof(char));
    }
    for (i = 0; i < n; ++i ) {
        fscanf(fin, "%s %s\n", a[i], b[i]);
    }    
    
    mergeSort(a, b, bufc, bufn, 0, n-1);

    for (i = 0; i < n; i++) {
        if ((i == 0) || (strcmp(a[i],a[i-1])!=0)) {
            fprintf(fout, "=== %s ===\n", a[i]);
        }
        fprintf(fout, "%s\n", b[i]);
    }

    free(a);
    free(b);
    fclose(fin);
    fclose(fout);

    return 0;
    }