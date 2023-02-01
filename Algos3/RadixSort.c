#include <stdio.h>

void merge (int r, char *arr[], int left, int mid, int right, char *buf[]) {
    int it1 = 0;
    int it2 = 0;
 
    while ((left + it1 < mid) && (mid + it2 <= right)) {
        if (arr[left + it1][r] <= arr[mid + it2][r]) {
            buf[it1 + it2] = arr[left + it1];
            it1++;
        }
 
        else {
            buf[it1 + it2] = arr[mid + it2];
            it2++;
        }
    }
 
    while (left + it1 < mid) {
        buf[it1 + it2]= arr[left + it1];
        it1++;
    }
 
    while (mid + it2 <= right) {
        buf[it1 + it2] = arr[mid + it2];
        it2++;
    }
 
    for (int i = 0; i < it1 + it2; i++) {
        arr[left + i] = buf[i];
    }
}
        
void mergeSort(char *a[], int left, int right, int r, char *buf[]) {
    if (left >= right) {
        return;
    }
             
    int mid = (left + right)/2 + 1;
    mergeSort(a, left, mid - 1, r, buf);
    mergeSort(a, mid, right, r, buf);
    merge(r, a, left, mid, right, buf);
 
}  

void radixSort(char *str[],int n, int m, int k, char *buf[]) {
    for (int i = 0; i < k; i++) {
        int r = m-i-1;
        mergeSort(str, 0, n-1, r, buf);
    }
}

int main() {
    int n, m , k;

    FILE *fin, *fout;
    fin = fopen("radixsort.in", "r");
    fout = fopen("radixsort.out", "w");

    fscanf(fin, "%d %d %d", &n, &m, &k);

    char **str;
    char **buf;
    str = (char**)malloc(n*sizeof(char*));
    buf = (char**)malloc(n*sizeof(char*));
    for (int i = 0; i < n; i++) {
        str[i] = (char*)malloc(m*sizeof(char));
        buf[i] = (char*)malloc(m*sizeof(char));
    }
    for (int j = 0; j < n; j++) {
        fscanf(fin, "%s", str[j]);
    }

    radixSort(str, n, m, k, buf);

    for (int i = 0; i < n; i++) {
        fprintf(fout,"%s\n", str[i]);
    }
    
    fclose(fin);
    fclose(fout);
    free(str);



    return 0;
}