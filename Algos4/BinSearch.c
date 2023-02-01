#include <stdio.h>
#include <stdlib.h>

int binSearchfirst(int arr[], int key, int right, int left) {
    while ((right - left) > 1) {
        int mid = left + (right - left)/2;
        if (key <= arr[mid]) {
            right = mid;
        }
        else if (key > arr[mid]) {
            left = mid;
        }
    }
    if (arr[left] == key) {
        return left+1;
    }
    if (arr[right] == key) {
        return right+1;
    }
    return -1;
}

int binSearchlast(int arr[], int key, int right, int left) {
    while ((right - left) > 1) {
        int mid = left + (right - left)/2;
        if (key < arr[mid]) {
            right = mid;
        }
        else if (key >= arr[mid]) {
            left = mid;
        }
    }
    if (arr[right] == key) {
        return right+1;
    }
    if (arr[left] == key) {
        return left+1;
    }
    return -1;
}

int main() {
    int n, m, request;
    n = 0;
    m = 0;
    request = 0;


    FILE *fin, *fout;
    fin = fopen("binsearch.in", "r");
    fout = fopen("binsearch.out", "w");

    fscanf(fin, "%d\n", &n);
    int *a;
    a = (int*)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        fscanf(fin, "%d ", &a[i]);
    }
    fscanf(fin, "%d\n", &m);
    for (int i = 0; i < m; i++) {
        fscanf(fin, "%d ", &request);
        fprintf(fout, "%d ", binSearchfirst(a, request, n-1, 0));
        fprintf(fout, "%d\n", binSearchlast(a, request, n-1, 0));
    }

    fclose(fin);
    fclose(fout);

    return 0;
}