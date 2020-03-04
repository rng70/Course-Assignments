#include <bits/stdc++.h>
#include <winnt.h>
#include <afxres.h>

using namespace std;

int join(vector<int> &A, vector<int> &left, vector<int> &right, int l, int m, int r) {
    int i; // Used in second loop
    for (i = 0; i <= m - l; i++)
        A[i] = left[i];

    for (int j = 0; j < r - m; j++)
        A[i + j] = right[j];
}

// Function to store alternate elements in left
// and right subarray
int split(vector<int> &A, vector<int> &left, vector<int> &right, int l, int m, int r) {
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

void printArray(vector<int> &A) {
//    for(auto i:A){
//        cout << i << " ";
//    }
//    cout << endl;
}

void writeToFile(int n) {

    LARGE_INTEGER start, end, freq;
    QueryPerformanceFrequency(&freq);


    vector<int> A;
    vector<int> B;

    A.clear();
    generateAverageCase(A, n);
    B.clear();
    B = A;

    // Random order case
    QueryPerformanceCounter(&start); //To start the times
    MergeSort(A, 0, n);
    QueryPerformanceCounter(&end);
    unsigned long long num_Ticks;
    num_Ticks = (end.LowPart - start.LowPart); // Save the number of ticks
    double elapsedTime;
    elapsedTime = (double) num_Ticks / (double) (freq.QuadPart / 1000.0);
    cout << "Merge sort random : " << elapsedTime << endl;

    //Ascending order case
    QueryPerformanceCounter(&start);
    MergeSort(A, 0, n);
    QueryPerformanceCounter(&end);
    num_Ticks = (end.LowPart - start.LowPart);
    elapsedTime = (double) num_Ticks / (double) (freq.QuadPart / 1000.0);
    cout << "Merge sort ascending  : " << elapsedTime << endl;

    //Descending order case
    reverse(A.begin(), A.end());
    QueryPerformanceCounter(&start);
    MergeSort(A, 0, n);
    QueryPerformanceCounter(&end);
    num_Ticks = (end.LowPart - start.LowPart);
    elapsedTime = (double) num_Ticks / (double) (freq.QuadPart / 1000.0);
    cout << "Merge sort descending : " << elapsedTime << endl;


    // Random order case
    QueryPerformanceCounter(&start);
    QuickSort(B, 0, n);
    QueryPerformanceCounter(&end);
    num_Ticks = (end.LowPart - start.LowPart);
    elapsedTime = (double) num_Ticks / (double) (freq.QuadPart / 1000.0);
    cout << "Quick sort random : " << elapsedTime << endl;


    //Ascending order case
    QueryPerformanceCounter(&start);
    QuickSort(B, 0, n);
    QueryPerformanceCounter(&end);
    num_Ticks = (end.LowPart - start.LowPart);
    elapsedTime = (double) num_Ticks / (double) (freq.QuadPart / 1000.0);

    cout << "Quick sort ascending : " << elapsedTime << endl;

    //Descending order case
    reverse(B.begin(), B.end());
    QueryPerformanceCounter(&start);
    QuickSort(B, 0, n);
    QueryPerformanceCounter(&end);
    num_Ticks = (end.LowPart - start.LowPart);
    elapsedTime = (double) num_Ticks / (double) (freq.QuadPart / 1000.0);
    cout << "Quick sort descending : " << elapsedTime << endl;

}

//void writeToFile1(int n, int k) {
//
//    LARGE_INTEGER start, end, freq;
//    QueryPerformanceFrequency(&freq);
//
//
//    vector<int> Aa;
//    vector<int> Ba;
//    vector<int> A;
//    vector<int> B;
//    unsigned long long num_Ticks = 0;
//    double elapsedTime_mr = 0, elapsedTime_ma = 0, elapsedTime_md = 0, elapsedTime_qr = 0, elapsedTime_qa = 0, elapsedTime_qd = 0;
//
//    Aa.clear();
//    generateAverageCase(Aa, n);
//    Ba.clear();
//    Ba = Aa;
//    int total_count = k;
//    int temp = total_count;
//
//    while (total_count--) {
//        A = Aa;
//        B = Ba;
//        // Random order case
//        QueryPerformanceCounter(&start); //To start the times
//        MergeSort(A, 0, n);
//        QueryPerformanceCounter(&end);
//        num_Ticks = (end.LowPart - start.LowPart); // Save the number of ticks
//        elapsedTime_mr += (double) num_Ticks / (double) (freq.QuadPart / 1000.0);
//
//
//        //Ascending order case
//        QueryPerformanceCounter(&start);
//        MergeSort(A, 0, n);
//        QueryPerformanceCounter(&end);
//        num_Ticks = (end.LowPart - start.LowPart);
//        elapsedTime_ma += (double) num_Ticks / (double) (freq.QuadPart / 1000.0);
//
//        //Descending order case
//        reverse(A.begin(), A.end());
//        QueryPerformanceCounter(&start);
//        MergeSort(A, 0, n);
//        QueryPerformanceCounter(&end);
//        num_Ticks = (end.LowPart - start.LowPart);
//        elapsedTime_md += (double) num_Ticks / (double) (freq.QuadPart / 1000.0);
//
//        // Random order case
//        QueryPerformanceCounter(&start);
//        QuickSort(B, 0, n);
//        QueryPerformanceCounter(&end);
//        num_Ticks = (end.LowPart - start.LowPart);
//        elapsedTime_qr += (double) num_Ticks / (double) (freq.QuadPart / 1000.0);
//
//        //Ascending order case
//        QueryPerformanceCounter(&start);
//        QuickSort(B, 0, n);
//        QueryPerformanceCounter(&end);
//        num_Ticks = (end.LowPart - start.LowPart);
//        elapsedTime_qa += (double) num_Ticks / (double) (freq.QuadPart / 1000.0);
//
//
//        //Descending order case
//        reverse(B.begin(), B.end());
//        QueryPerformanceCounter(&start);
//        QuickSort(B, 0, n);
//        QueryPerformanceCounter(&end);
//        num_Ticks = (end.LowPart - start.LowPart);
//        elapsedTime_qd += (double) num_Ticks / (double) (freq.QuadPart / 1000.0);
//
//    }
////    toFile << "Merge :\t" << elapsedTime_mr / temp << "\t" << elapsedTime_ma / temp << "\t" << elapsedTime_md / temp
////           << endl;
////    toFile << "Quick :\t" << elapsedTime_qr / temp << "\t" << elapsedTime_qa / temp << "\t" << elapsedTime_qd / temp
////           << endl;
//    cout << endl << " Number of element : " << n << endl;
//    cout << "Merge sort random : " << elapsedTime_mr / temp << endl;
//    cout << "Merge sort ascending  : " << elapsedTime_ma / temp << endl;
//    cout << "Merge sort descending : " << elapsedTime_md / temp << endl;
//    cout << "Quick sort random : " << elapsedTime_qr / temp << endl;
//    cout << "Quick sort ascending : " << elapsedTime_qa / temp << endl;
//    cout << "Quick sort descending : " << elapsedTime_qd / temp << endl;
//    cout << "Execution success " << endl << endl;
//}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    vector<int> A{1, 2, 3, 4, 5};

//    int sizeOfArray[] = {10, 100, 1000, 5000, 10000, 50000, 100000, 500000, 1000000};

    int temp = 0;
    int n; //, k;

    while (temp < 9) {
        cout << "Enter the number : ";
        flush(cout);
        cin >> n;
//        cout << "Enter the number of iteration : ";
//        flush(cout);
//        cin >> k;
        writeToFile(n);
        temp++;
    }
    printArray(A);
}





