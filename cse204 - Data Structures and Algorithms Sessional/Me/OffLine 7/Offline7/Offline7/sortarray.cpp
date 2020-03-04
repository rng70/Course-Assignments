#include <cstdio>
#include <bits/stdc++.h>

using namespace std;

int join(vector<int> &A, vector<int> &left, vector<int> &right,
         int l, int m, int r) {
    int i; // Used in second loop
    for (i = 0; i <= m - l; i++)
        A[i] = left[i];

    for (int j = 0; j < r - m; j++)
        A[i + j] = right[j];
}

// Function to store alternate elemets in left
// and right subarray
int split(vector<int> &A, vector<int> &left, vector<int> &right,
          int l, int m, int r) {
    for (int i = 0; i <= m - l; i++)
        left[i] = A[i * 2];

    for (int i = 0; i < r - m; i++)
        right[i] = A[i * 2 + 1];
}

void generateWorstCase(vector<int> &A, int l, int r) {
    if (l < r) {
        int m = l + (r - l) / 2;

        vector<int> left(m - l + 1);
        vector<int> right(r - m);

        // Store alternate array elements in left
        // and right subarray
        split(A, left, right, l, m, r);

        // Recurse first and second halves
        generateWorstCase(left, l, m);
        generateWorstCase(right, m + 1, r);

        // join left and right subarray
        join(A, left, right, l, m, r);
    }
}

void MERGE(vector<int> &A, int p, int q, int r) {
    int n1 = q - p + 1;
    int n2 = r - q;
    int L[n1];
    int R[n2];
    for (int i = 0; i < n1; i++) {
        L[i] = A[p + i];
    }
    for (int i = 0; i < n2; i++) {
        R[i] = A[q + i + 1];
    }
    int i = 0, j = 0, k = p;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            A[k] = L[i];
            i++;
        } else {
            A[k] = R[j];
            j++;
        }
        k++;
    }
    /* Copy the remaining elements of L[], if there
       are any */
    while (i < n1) {
        A[k] = L[i];
        i++;
        k++;
    }
    /* Copy the remaining elements of R[], if there
       are any */
    while (j < n2) {
        A[k] = R[j];
        j++;
        k++;
    }
}

void MergeSort(vector<int> &A, int p, int r) {
    if (p < r) {
        int q = (p + r) / 2;
        MergeSort(A, p, q);
        MergeSort(A, q + 1, r);
        MERGE(A, p, q, r);
    }

}
int PARTITION(vector<int> &A, int p, int r) {
    int x = A[r];
    int i = p - 1;
    for (int j = p; j < r; j++) {
        if (A[j] <= x) {
            i += 1;
            swap(A[i], A[j]);
        }
    }
    swap(A[i + 1], A[r]);
    return i + 1;
}

void QuickSort(vector<int> &A, int p, int r) {
    if (p < r) {
        int q = PARTITION(A, p, r);
        QuickSort(A, p, q - 1);
        QuickSort(A, q + 1, r);
    }
}
void generateAverageCase(vector<int>& A,int n){
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> dist6(1,6);
    for(int i=0;i<n;i++){
        std::uniform_int_distribution<std::mt19937::result_type> dist6(1,6);
         A.push_back(dist6(rng))
    }
}

int main() {
    int choice, n;

    vector<int>A;

    while (1) {
        printf("1. Generate average case\n");
        printf("2. Generate best case\n");
        printf("3. Generate worst case\n");
        printf("4. Apply Merge sort\n");
        printf("5. Apply Quicksort\n");
        printf("6. Print array\n");
        printf("> ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Number of elements: ");
                scanf("%d", &n);
                A.clear()
                break;

            case 2:
                printf("Number of elements: ");
                scanf("%d", &n);
                // do yourself
                break;

            case 3:
                printf("Number of elements: ");
                scanf("%d", &n);
                // do yourself
                break;

            case 4:
                printf("Applying merge sort\n");
                // do yourself
                // this should transform the given array into a sorted array
                printf("Time taken to finish: <your time>\n");
                break;

            case 5:
                printf("Applying quicksort\n");
                // do yourself
                // this should transform the given array into a sorted array
                printf("Time taken to finish: <your time>\n");
                break;

            case 6:
                printf("Array\n");
                // do yourself
                break;
        }
    }
}

