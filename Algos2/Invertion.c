#include <stdio.h>
#include <malloc.h>
#include <stdint.h>

void invcount(int arr[], int result[], int left, int mid, int right, int64_t *count) {
    int it1 = 0;
    int it2 = 0;

    while ((left + it1 < mid) && (mid + it2 <= right)) {
        if (arr[left + it1] <= arr[mid + it2]) {
            result[it1 + it2] = arr[left + it1];
            it1++;
        }

        else {
            result[it1 + it2] = arr[mid + it2];
            it2++;
            (*count) += (mid - (left + it1)) ;
        }
    }

    while (left + it1 < mid) {
        result[it1 + it2] = arr[left + it1];
        it1++;
    }

    while (mid + it2 <= right) {
        result[it1 + it2] = arr[mid + it2];
        it2++;
    }

    for (int i = 0; i < it1 + it2; i++) {
        arr[left + i] = result[i];
    }
}
       
void mergeSort( int a[],int buf[], int left, int right, int64_t *count) {
    if (left >= right) {
        return;
    }

    int mid = (left + right)/2 + 1;
    mergeSort(a, buf, left, mid - 1, count);
    mergeSort(a, buf, mid, right, count);
    invcount(a, buf, left, mid, right, count);
}  

int main()
{
        int n, i;
        int64_t count;

        FILE *fin, *fout;
        fin = fopen("inversions.in", "r");
        fout = fopen("inversions.out", "w");
        
        fscanf (fin, "%d", &n);
        int *a;
        int *buf;
        a = (int*)malloc(n * sizeof(int));
        buf = (int*)malloc(n * sizeof(int));
        for (i = 0; i < n; ++i ) {
            fscanf(fin, "%d", &a[i]);
        }    

        count = 0;
        mergeSort(a, buf, 0, n-1, &count);

        fprintf(fout, "%I64d\n", count);

        free(a);
        free(buf);
        fclose(fin);
        fclose(fout);

        return 0;
    
}