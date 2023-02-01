#include <stdio.h>
#include <malloc.h>

void merge (int arr[], int left, int mid, int right) {
    int it1 = 0;
    int it2 = 0;
    int *result;
    result = (int*)malloc((1+right-left) * sizeof(int));

    while ((left + it1 < mid) && (mid + it2 <= right)) {
        if (arr[left + it1] < arr[mid + it2]) {
            result[it1 + it2] = arr[left + it1];
            it1++;
        }

        else {
            result[it1 + it2] = arr[mid + it2];
            it2++;
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

    free(result);
}
       
void mergeSort( int a[], int left, int right) {
    if (left >= right) {
        return;
    }
            
    int mid = (left + right)/2 + 1;
    mergeSort(a, left, mid - 1);
    mergeSort(a, mid, right);
    merge(a, left, mid, right);

}  

int main()
{
        int n, i, j;

        FILE *fin, *fout;
        fin = fopen("sort.in", "r");
        fout = fopen("sort.out", "w");
        
        fscanf (fin, "%d", &n);
        int *a;
        a = (int*)malloc(n * sizeof(int));
        for (i = 0; i < n; ++i ) {
            fscanf(fin, "%d", &a[i]);
        }    

        mergeSort (a, 0, n-1);
        
        for (int i = 0 ; i < n ; ++i) {
            fprintf(fout, "%d ", a[i]);
        }

        free(a);
        fclose(fin);
        fclose(fout);

        return 0;
    
}