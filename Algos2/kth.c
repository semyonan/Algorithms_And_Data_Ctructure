#include <stdio.h> 
#include <malloc.h>
#include <stdint.h>

void swap(int32_t *a1, int32_t *a2) {
    int32_t c = *a1;
    *a1 = *a2;
    *a2 = c;
}

int partition(int32_t arr[], int left, int right) {
    srand ((left + 1) * right);
    int pind = rand() % (right - left + 1) + left;
    int32_t pivot = arr[pind];
    swap(&arr[pind], &arr[right]);
    int i = left;
    int j = right-1;
    while (i <= j) {
        while (arr[i] < pivot) {
            i++;
        }
        while (arr[j] > pivot) {
            j--;
        }
        if (i <= j) {
            swap(&arr[i],&arr[j]); 
            i++;
            j--;
        }
    }
    swap(&arr[i], &arr[right]);
    return (i);
}

int32_t findk (int32_t arr[], int n, int k) {
    int left = 0;
    int right  = n-1;

    while (1) {
        int mid = partition(arr, left, right);

        if (mid == k) {
            return (arr[k]);
        }
        else if (mid < k) {
            left = mid + 1;
        }
        else {
            right = mid -1;
        }
    }

}
 
int main() {
    int n, i, k, a, b, c; 
 
    FILE *fin, *fout;
    fin = fopen("kth.in", "r");
    fout = fopen("kth.out", "w");
 
    fscanf (fin, "%d %d\n", &n, &k);
    fscanf (fin, "%d %d %d", &a, &b, &c);
    int32_t *mas;
    mas = (int32_t*)malloc(n * sizeof(int32_t));
    for (i = 0; i < 2; ++i ) {
        fscanf(fin, "%I32d", &mas[i]);
    } 
 
    for (i = 2; i < n; ++i) {
        mas[i] = mas[i-2]*a + b*mas[i-1] + c;
    }
 
    fprintf(fout, "%I32d\n", findk(mas, n, k - 1));
 
    free(mas);
    fclose(fin);
    fclose(fout); 
 
    return 0;   
} 