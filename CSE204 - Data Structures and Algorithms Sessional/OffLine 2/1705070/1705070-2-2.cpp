#include <bits/stdc++.h>
#include <chrono>
#include <winnt.h>
#include <afxres.h>

#define sync ios::sync_with_stdio(false);cin.tie(nullptr);cout.tie(nullptr);
//#define debug(...) fprintf(stderr,__VA_ARGS__),fflush(stderr)
//#define time_needed(d)\
//    for( auto blockTime = make_pair(chrono::high_resolution_clock::now(), true);\
//    blockTime.second; \
//        endTime = chrono::duration_cast<chrono::hours>\
//                (chrono::high_resolution_clock::now() - blockTime.first).count(),\
//        debug("%s : %lld ns\n", d, endTime), blockTime.second = false \
//        )

using namespace std;
vector<char> vectorOfCharacter;

long long endTime = 0;

ofstream outToFile("PowerSet.out");
ofstream timePower("PowerSetTime.out");

void PowerSet() {

    int sizeOfVector = vectorOfCharacter.size();
    unsigned long long totalIteration = pow(2, sizeOfVector);
    unsigned one = 1, m = 0;

    for (unsigned long long i = 0; i < totalIteration; i++) {
        int count_pos = 0;
        unsigned int n = i;
        string s = "{ ";
        cout << "{ ";
        while (n) {
            if (n & one) {
                cout << vectorOfCharacter[count_pos] << ", ";
                s += vectorOfCharacter[count_pos];
                s += ", ";
            }
            n = n >> one;
            count_pos++;
        }
        int len = s.size();
        if (len > 2) {
            len -= 2;
            s[len] = ' ';
            s[len + 1] = '}';
        } else {
            s += '}';
        }
        if (totalIteration < 32768)outToFile << "\t\t" << s << endl;
        cout << " }" << endl;
    }

}

int main() {
    sync
    char ar[] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l',
                 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x',
                 'y', 'z', '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D'};
    printf("Enter the total number of element of set : 5\n");
    int n , q = 0, times = 36;

    cin >> n;
    cout << " Enter the elements : " << endl;

    while (times--) {

        for (q = 0; q < n; q++) {
            vectorOfCharacter.push_back(ar[q]);
        }
        outToFile << " All Possible power set of { ";
        for (int i = 0; i < vectorOfCharacter.size(); i++) {
            cout << vectorOfCharacter[i] << " ";
            outToFile << vectorOfCharacter[i];
            if (i != vectorOfCharacter.size() - 1) outToFile << ", ";
            else outToFile << " ";
        }
        outToFile << "}" << endl << endl << " Power Sets :" << endl;
        cout << endl;

        long double ms = 0.0;
        LARGE_INTEGER freq;
        LARGE_INTEGER t1, t2;
        if (QueryPerformanceFrequency(&freq) == 0) {
            printf("Your machine not support high resolution performance counter\n");
            exit(-1);
        }

//        QueryPerformanceCounter(&t1);
        auto startTime = chrono::high_resolution_clock::now();
        PowerSet();
        auto endTimeNow = chrono::high_resolution_clock::now();
//        QueryPerformanceCounter(&t2);
//        ms = (t2.QuadPart - t1.QuadPart) / (freq.QuadPart / 1000.0);
        long long neededTime = chrono::duration_cast<chrono::nanoseconds>(endTimeNow - startTime).count();
        timePower << n << " -> " << neededTime << endl;
        cout << n << " -> " << neededTime << endl;

//        n += 2;
        vectorOfCharacter.clear();
        cout << endl;
        cin >> n;
        printf("Enter the total number of element of set : %d\n", n);
        cout << endl;
    }

//    auto startTime = chrono::high_resolution_clock::now();
//    auto endTimeNow = chrono::high_resolution_clock::now();
//    long long neededTime = chrono::duration_cast<chrono::seconds>(endTimeNow - startTime).count();
//    cout << neededTime << endl;

    return EXIT_SUCCESS;
}
