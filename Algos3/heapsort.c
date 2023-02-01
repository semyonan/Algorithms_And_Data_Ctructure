#include <stdio.h>

void swap(int *a, int *b) {
    int c = (*a);
    (*a) = (*b);
    (*b) = c;
}

void heapCreation(int arr[], int n, int i) {
    int root = i;
    int left = 2*i + 1;
    int right = 2*i + 2;

    if ((left < n) && (arr[left] > arr[root]) && ((right >= n) || (arr[left] >= arr[right]))) {
        root = left;
    }
    else if ((right < n) && (arr[right] > arr[root])) {
        root = right;
    }

    if (root != i) {
        swap(&arr[i], &arr[root]);
        heapCreation(arr, n, root);
    }
}

void heapSort(int arr[],int n) {
    for (int i = n/2 - 1; i>=0; i--) {
        heapCreation(arr, n, i);
    }

    for (int i = n-1; i>=0; i--) {
        swap(&arr[0], &arr[i]);
        heapCreation(arr, i, 0);
    }
}

int main() {
    int n;

    FILE *fin, *fout;
    fin = fopen("sort.in", "r");
    fout = fopen("sort.out", "w");

    fscanf(fin, "%d", &n);

    int *a;
    a = (int*)malloc(n*sizeof(int));
    for (int i = 0; i < n; i++) {
        fscanf(fin, "%d", &a[i]);
    }

    heapSort(a, n);

    for (int i = 0; i < n; i++) {
        fprintf(fout, "%d ", a[i]);
    }

    fclose(fin);
    fclose(fout);
    free(a);



    return 0;
}