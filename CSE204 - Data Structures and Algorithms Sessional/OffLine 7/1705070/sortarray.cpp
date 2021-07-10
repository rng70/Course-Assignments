#include <bits/stdc++.h>
#include <winnt.h>
#include <afxres.h>

using namespace std;

int join(vector<int> &A, vector<int> &left, vector<int> &right,
         int l, int m, int r) {
    int i; // Used in second loop
    for (i = 0; i <= m - l; i++)
        A[i] = left[i];

    for (int j = 0; j < r - m; j++)
        A[i + j] = right[j];
}

// Function to store alternate elements in left
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

void generateAverageCase(vector<int> &A, int n) {
    std::random_device dev;
    std::mt19937 rng(dev());
    for (int i = 0; i < n; i++) {
        std::uniform_int_distribution<std::mt19937::result_type> dist6(1, 10 * n);
        A.push_back(dist6(rng));
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int choice, n;
    LARGE_INTEGER start, end, freq;
    QueryPerformanceFrequency(&freq);


    vector<int> A;
    vector<int> B;

    while (true) {
        printf("\n\t1. Generate Random order case\n");
        printf("\t2. Generate Ascending order case\n");
        printf("\t3. Generate Descending order case\n");
        printf("\t4. Apply Merge sort\n");
        printf("\t5. Apply Quick sort\n");
        printf("\t6. Print array\n");
        printf("\t7. Exit\n");
        printf("\t> \n");
        cin >> choice;
        if (choice == 7) break;

        switch (choice) {
            case 1:
                printf("\tNumber of elements: ");
                cin >> n;
                A.clear();
                generateAverageCase(A, n);
                B.clear();
                B = A;
                break;
            case 2:
                printf("\tNumber of elements: ");
                cin >> n;
                A.clear();
                generateAverageCase(A, n);
                MergeSort(A, 0, n - 1);
                B.clear();
                B = A;
                break;
            case 3:
                printf("\tNumber of elements: ");
                cin >> n;
                A.clear();
                generateAverageCase(A, n);
                MergeSort(A, 0, n - 1);
                reverse(A.begin(), A.end());
                B.clear();
                B = A;
                break;
//                cout << " \n\t1. For Merge Sort\n\t2. For Quick Sort"<<endl;
//                int c;
//                cin >> c;
//                if(c==1){
//                    printf("\tNumber of elements: ");
//                    cin >> n;
//                    A.clear();
//                    generateAverageCase(A,n);
//                    generateWorstCase(A,0,n-1);
//                }
//                else if(c==2){
//                    printf("\tNumber of elements: ");
//                    cin >> n;
//                    A.clear();
//                    generateAverageCase(A,n);
//                    QuickSort(A,0,n-1);
//                    reverse(A.begin(),A.end());
//                }else{
//                    cout << "\n\tInvalid input :'( \n\tContinue with valid input"<<endl;
//                }
//                break;
            case 4:
                printf("\tApplying merge sort :\n");
                int len;
                len = (int) A.size() - 1;
                QueryPerformanceCounter(&start); //To start the times
                MergeSort(A, 0, len);
                QueryPerformanceCounter(&end);
                unsigned long long num_Ticks;
                num_Ticks = (end.LowPart - start.LowPart); // Save the number of ticks
                double elapsedTime;
                elapsedTime = (double) num_Ticks / (double) (freq.QuadPart / 1000.0);

                printf("\tTime taken to finish : ");
                cout << elapsedTime << " milliseconds" << endl;
                break;
            case 5:
                printf("\tApplying quick sort\n");
                int nk;
                nk = B.size();
                QueryPerformanceCounter(&start); //To start the times
                QuickSort(B, 0, nk - 1);
                QueryPerformanceCounter(&end);
                unsigned long long num_Ticks1;
                num_Ticks1 = (end.LowPart - start.LowPart); // Save the number of ticks
                double elapsedTime1;
                elapsedTime1 = (double) num_Ticks1 / (double) (freq.QuadPart / 1000.0);

                printf("\tTime taken to finish : ");
                cout << elapsedTime1 << " milliseconds" << endl;
                break;
            case 6:
                printf("\tArray :\n\t");
                for (int i : A) {
                    cout << i << " ";
                }
                cout << endl;
                break;
            default:
                cout << "\n\tInvalid input :'( \n\tContinue with valid input" << endl;
                break;
        }
    }
}



