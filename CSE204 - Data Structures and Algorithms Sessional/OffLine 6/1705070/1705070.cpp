#include <bits/stdc++.h>

#define MAX_SIZE 10
#define NULL_VALUE -9999999

using namespace std;

template<class T>
class priorityQueue {
    T *listOfElement;
    int max_available;

public:
    explicit priorityQueue() {
        listOfElement = new T[MAX_SIZE];
        max_available = MAX_SIZE;
        listOfElement[0] = 0;
    }

    void Max_heapifyUp(int idx) {
        if (idx > 1) {
            int p = getParent(idx);
            if (listOfElement[p] < listOfElement[idx]) {
                swap(listOfElement[p], listOfElement[idx]);
                Max_heapifyUp(p);
            }
        }
    }

    void Max_heapifyDown(int idx) {
        int index = idx;

        int l = getLeftChild(index);
        int r = getRightChild(index);
        int largest = index;

        if (l <= listOfElement[0] && listOfElement[l] > listOfElement[largest]) {
            largest = l;
        }
        if (r <= listOfElement[0] && listOfElement[r] > listOfElement[largest]) {
            largest = r;
        }
        if (largest != index) {
            swap(listOfElement[index], listOfElement[largest]);
            Max_heapifyDown(largest);
        }
    }

    int getLeftChild(int i) {
        return 2 * i;
    }

    int getRightChild(int i) {
        return 2 * i + 1;
    }

    int getParent(int i) {
        if (i > 1) return i / 2;
        else return NULL_VALUE;
    }

    void ensureCapacity() {
        int temp_size = max_available * 2;
        T *temp = new T[temp_size];
        for (int i = 0; i <= listOfElement[0]; i++) {
            temp[i] = listOfElement[i];
        }
        max_available = temp_size;
        delete[] listOfElement;
        listOfElement = new T[max_available];
        for (int i = 0; i <= listOfElement[0]; i++) {
            listOfElement[i] = temp[i];
        }
        delete[] temp;
    }

    void Insert(T x) {
        if (listOfElement[0] >= (max_available-1)){
            ensureCapacity();
        }

        listOfElement[++listOfElement[0]] = x;
        int pos = listOfElement[0];
        Max_heapifyUp(pos);
    }

    T FindMax() {
        if (listOfElement[0] == 0) {
            cout << "Heap underflow.. No maximum element" << endl;
            return NULL_VALUE;
        }
        return listOfElement[1];
    }

    T ExtractMax() {
        if (listOfElement[0] < 1) {
            cout << "Heap underflow.. No maximum element" << endl;
            return NULL_VALUE;
        }

        T temp = listOfElement[1];
        listOfElement[1] = listOfElement[listOfElement[0]];
        listOfElement[0] -= 1;
        Max_heapifyDown(1);
        return temp;
    }

    void IncreaseKey(int pos, T key) {
        if (key < listOfElement[pos]) {
            cout << "New element is smaller than current key" << endl;
            return;
        }

        listOfElement[pos] = key;
        Max_heapifyUp(pos);
    }

    void DecreaseKey(int pos, T key) {
        if (key > listOfElement[pos]) {
            cout << "New element is greater than current key" << endl;
            return;
        }
        listOfElement[pos] = key;
        Max_heapifyDown(pos);
    }

    void Print() {
        cout << "\tCurrent Heap           : ";
        for (int i = 1; i <= listOfElement[0]; i++) {
            cout << listOfElement[i] << " ";
        }
        cout << endl;
        cout << "\tCurrent heap size      : " << listOfElement[0] << endl;
        cout << "\tMaximum available size : " << max_available << endl;
    }
};

void menu() {
    cout << "\n\tEnter your choice : ";
    cout << "\n\t1. Insert\n\t2. FindMax\n\t3. ExtractMax"
            "\n\t4. IncreaseKye\n\t5. DecreaseKey\n\t6. Print\n\t7. PrintSize\n\t8. Quit" << endl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    priorityQueue<int> pQueue;
    cout << "\n\t ***** This is the implementation of max Priority Queue *****" << endl;

    while (true) {
        menu();
        int choice;
        cin >> choice;

        if (choice == 8)
            break;
        switch (choice) {
            case 1:
                cout << "\t1. Insert one-by-one\n\t2. All at once" << endl;
                int option;
                cin >> option;

                switch (option) {
                    case 1:
                        cout << "\tEnter the element : ";
                        flush(cout);
                        int element;
                        cin >> element;
                        pQueue.Insert(element);
                        break;
                    case 2:
                        cout << "\tEnter total number of elements : ";
                        flush(cout);
                        int total1;
                        cin >> total1;
                        cout << "\tEnter the elements : ";
                        flush(cout);
                        int element1;
                        while (total1--) {
                            cin >> element1;
                            pQueue.Insert(element1);
                        }
                        break;
                    default:
                        cout << "\n\tInvalid input :'( .... continue with valid input " << endl;
                        break;
                }
                break;
            case 2:
                cout << "\n\tMaximum element : " << pQueue.FindMax() << endl;
                break;
            case 3:
                cout << "\n\tMaximum element : " << pQueue.ExtractMax() << " extracted" << endl;
                break;
            case 4:
                cout << "\n\tEnter the new key with new position : ";
                flush(cout);
                int i, Key;
                cin >> i >> Key;
                pQueue.IncreaseKey(i, Key);
                break;
            case 5:
                cout << "\n\tEnter the new key with new position : ";
                flush(cout);
                int j, key;
                cin >> j >> key;
                pQueue.DecreaseKey(j, key);
                break;
            case 6:
                cout << "Printing : " << endl;
                pQueue.Print();
                break;
            default:
                cout << "\n\tInvalid input :'( .... continue with valid input " << endl;
                break;
        }
    }
    return EXIT_SUCCESS;
}
