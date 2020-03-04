#include <bits/stdc++.h>

using namespace std;

typedef struct {
    int startTime;
    int finishTime;
} activityStructure;

void MERGE(activityStructure A[], int p, int q, int r) {
    int n1 = q - p + 1;
    int n2 = r - q;
    activityStructure L[n1];
    activityStructure R[n2];
    for (int i = 0; i < n1; i++) {
        L[i] = A[p + i];
    }
    for (int i = 0; i < n2; i++) {
        R[i] = A[q + i + 1];
    }
    int i = 0, j = 0, k = p;
    while (i < n1 && j < n2) {
        if (L[i].finishTime < R[j].finishTime) {
            A[k] = L[i];
            i++;
        } else if (L[i].finishTime > R[j].finishTime) {
            A[k] = R[j];
            j++;
        } else {
            if (L[i].startTime < R[j].startTime) {
                A[k] = L[i];
                i++;
            } else {
                A[k] = R[j];
                j++;
            }
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

void MergeSort(activityStructure A[], int p, int r) {
    if (p < r) {
        int q = (p + r) / 2;
        MergeSort(A, p, q);
        MergeSort(A, q + 1, r);
        MERGE(A, p, q, r);
    }

}

//bool compare(activityStructure a, activityStructure b) {
//    if (a.finishTime != b.finishTime) {
//        return a.finishTime < b.finishTime;
//    }
//    return a.startTime <= b.startTime;
//}

void selectSingleSetOfOptimumActivities(const int s[], const int t[], int size) {
    activityStructure lists[size];
    for (int i = 0; i < size; i++) {
        activityStructure S;
        S.startTime = s[i];
        S.finishTime = t[i];
        lists[i] = S;
    }
    MergeSort(lists, 0, size - 1);
//    sort(lists, lists + size, compare);
    cout << "Ordered activities w.r.t early finish" << endl;
    for (int i = 0; i < size; i++) {
        cout << "\t" << lists[i].startTime << "  " << lists[i].finishTime << endl;
    }
    cout << "---------------------------------- " << endl;
    vector<activityStructure> v;
    for (int i = 0; i < size; i++) {
        v.push_back(lists[i]);
        int k = i + 1;
        while (lists[k].startTime <= lists[i].finishTime) {
            k += 1;
        }
        i = k - 1;
    }
    cout << "Optimum solution for mutually compatible activities :" << endl;
    for (auto &x:v) {
        cout << "\t" << x.startTime << " " << x.finishTime << endl;
    }
}

void Make_Tasks() {
    int n = rand() % 50 + 10;
    int x = rand() % 128;
    int y = rand() % 128;
    int counter = 0;
    int s[n], f[n];
    while (counter < n) {
        if (x == y) {
            continue;
        }
        if (x > y) swap(x, y);
        s[counter] = x;
        f[counter] = y;
        counter += 1;
        x = rand() % 128;
        y = rand() % 128;
    }
    selectSingleSetOfOptimumActivities(s, f, n);
}

int main() {
    srand(time(nullptr));

    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    Make_Tasks();
}
