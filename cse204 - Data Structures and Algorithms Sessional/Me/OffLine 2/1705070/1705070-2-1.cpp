#include <bits/stdc++.h>
#include <chrono>

#define sync ios::sync_with_stdio(false);cin.tie(nullptr);cout.tie(nullptr);

//This define part is for measuring time
//#define debug(...) fprintf(stderr,__VA_ARGS__),fflush(stderr)
//#define time_needed(d, nameOfCase)\
//    for( auto blockTime = make_pair(chrono::high_resolution_clock::now(), true);\
//    blockTime.second; \
//        endTime = chrono::duration_cast<chrono::nanoseconds>\
//                (chrono::high_resolution_clock::now() - blockTime.first).count(),\
//       debug("%s %s: %lld ns\n", d,nameOfCase, endTime), blockTime.second = false \)

using namespace std;
const auto longPrime = 1000000009;
mt19937 mrand(random_device{}());

long long endTime = 0;
long double selectionAverage, insertionAverage;
long double selectionWorst, insertionWorst;
long double selectionBest, insertionBest;

ofstream insertionFile("InsertionChrono.out");
ofstream selectionFile("SelectionChrono.out");

vector<int> arrayToSortBySelection;
vector<int> arrayToSortByInsertion;

auto rnd(int x) {
    return mrand() * mrand() % x;
}

void selection_sort() {
    int totalArraySize = arrayToSortBySelection.size();
    int minimum_index;

    for (int i = 0; i < totalArraySize - 1; i++) {
        minimum_index = i;
        for (int j = i + 1; j < totalArraySize; j++) {
            if (arrayToSortBySelection[j] < arrayToSortBySelection[minimum_index]) {
                minimum_index = j;
            }
        }
        int temp = arrayToSortBySelection[i];
        arrayToSortBySelection[i] = arrayToSortBySelection[minimum_index];
        arrayToSortBySelection[minimum_index] = temp;
    }
}

void insertion_sort() {
    int totalArraySize = arrayToSortByInsertion.size();
    int j, current_value;

    for (int i = 0; i < totalArraySize; i++) {
        j = i - 1;
        current_value = arrayToSortByInsertion[i];
        while (arrayToSortByInsertion[j] > current_value && j >= 0) {
            arrayToSortByInsertion[j + 1] = arrayToSortByInsertion[j];
            j--;
        }
        arrayToSortByInsertion[j + 1] = current_value;
    }
}

void setProperValues() {
    selectionAverage = 0.0, insertionAverage = 0.0;
    selectionWorst = 0.0, insertionWorst = 0.0;
    selectionBest = 0.0, insertionBest = 0.0;
}

void measureAndNoteTime() {
    setProperValues();
    int toCountAverage = 100;
    int temp = toCountAverage;

    vector<int> v_selection;
    vector<int> v_insertion;

    v_insertion = arrayToSortByInsertion;
    v_selection = arrayToSortBySelection;

    while (toCountAverage--) {

        arrayToSortBySelection = v_selection;
        arrayToSortByInsertion = v_insertion;

        //Average Case
        auto start = std::chrono::steady_clock::now();
        insertion_sort();
        auto end = std::chrono::steady_clock::now();
        long long time = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
        insertionAverage += (long double) time;

        start = std::chrono::steady_clock::now();
        selection_sort();
        end = std::chrono::steady_clock::now();
        time = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
        selectionAverage += (long double) time;

        //Best Case
        start = std::chrono::steady_clock::now();
        insertion_sort();
        end = std::chrono::steady_clock::now();
        time = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
        insertionBest += (long double) time;

        start = std::chrono::steady_clock::now();
        selection_sort();
        end = std::chrono::steady_clock::now();
        time = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
        selectionBest += (long double) time;

        reverse(arrayToSortBySelection.begin(), arrayToSortBySelection.end());
        reverse(arrayToSortByInsertion.begin(), arrayToSortByInsertion.end());

        // Worst Case
        start = std::chrono::steady_clock::now();
        insertion_sort();
        end = std::chrono::steady_clock::now();
        time = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
        insertionWorst += (long double) time;

        start = std::chrono::steady_clock::now();
        selection_sort();
        end = std::chrono::steady_clock::now();
        time = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
        selectionWorst += (long double) time;
    }

    long double i_av = (long double) insertionAverage / (long double) temp;
    long double s_av = (long double) selectionAverage / (long double) temp;
    long double i_b = (long double) insertionBest / (long double) temp;
    long double s_b = (long double) selectionBest / (long double) temp;
    long double i_w = (long double) insertionWorst / (long double) temp;
    long double s_w = (long double) selectionWorst / (long double) temp;

    insertionFile << i_av << "," << i_b << "," << i_w << endl;
    selectionFile << s_av << "," << s_b << "," << s_w << endl;
    cout << "Average: " << i_av << " " << s_av << endl;
    cout << "Best   : " << i_b << " " << s_b << endl;
    cout << "Worst  : " << i_w << " " << s_w << endl;
}

void generateAndCopyArray(int n) {
    for (int i = 0; i < n; i++) {
        arrayToSortByInsertion.push_back(rnd(longPrime));
    }
    arrayToSortBySelection = arrayToSortByInsertion;
    measureAndNoteTime();
}

int main() {

    sync

    cout << "Entered the value of Array Size = 10" << endl;
    int n = 8, q = 0;
//    cin >> n;
    int a[] = {10, 100, 200, 500, 1000, 2000,5000, 10000};

    while (n--) {
        generateAndCopyArray(a[q]);
        q++;
        cout << "Entered the value of Array Size = " << a[q] << endl;
//        cin >> n;
    }
    return EXIT_SUCCESS;
}
