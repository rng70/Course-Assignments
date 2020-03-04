#include <bits/stdc++.h>

#define MAX_SIZE 100
using namespace std;


class disjointSetUnion {
    int parent[MAX_SIZE];
    int rank[MAX_SIZE];
public:
    disjointSetUnion() {
        for (int &i : parent) {
            i = 0;
        }
        for (int &i : rank) {
            i = -1;
        }
    }

    void Make_Set(int x) {
        parent[x] = x;
        rank[x] = 0;
    }

    int Find_Set(int x) {
        if (parent[x] != x) {
            parent[x] = Find_Set(parent[x]);
        }
        return parent[x];
    }
    void PrintParent(){
        for (int &i : parent){
            cout << i << " ";
        }
        cout << endl;
    }

    void Union(int x, int y) {
        int parent_x = Find_Set(x);
        int parent_y = Find_Set(y);


        if ((parent_x != parent_y) && (parent_x > 0 && parent_y > 0)) {
            if (rank[parent_x] == rank[parent_y]) {
                parent[y] = x;
                rank[x] += 1;
            } else if (rank[parent_x] > rank[parent_y]) {
                parent[y] = x;
            } else {
                parent[x] = y;
            }
        } else {
            cout << "Union failed. One or Two component does not exists." << endl;
        }
    }

    void Print(int x) {
        int parent_x = Find_Set(x);
        for (int i = 0; i < MAX_SIZE; i++) {
            if(parent[i] == parent_x)cout << i << " ";
            else{
                int cur_parent = Find_Set(i);
                if (cur_parent == parent_x) cout << i << " ";
            }
        }
        cout << endl;
    }
};


void Menu() {
    cout << "\n\tEnter your choice\n\t1. Make-Set\n\t2. Find-Set\n\t3. Union\n\t4. Print\n\t5. Exit" << endl;

}

int main() {
    cout << "<-------------------------------------->" << endl;
    cout << " This is implementation of Disjoint Set Union " << endl;
    disjointSetUnion dsu;
    Menu();
    int choice;
    cin >> choice;
    while (choice != 5) {
        switch (choice) {
            case 1:
                cout << "Enter the component x (0 < x < " << MAX_SIZE << ")" << endl;
                int n;
                cin >> n;
                if (n >= MAX_SIZE) {
                    cout << "Invalid input. Continue with valid input. Thank you!" << endl;
                } else {
                    dsu.Make_Set(n);
                }
                break;
            case 2:
                cout << "Enter the component x (0 < x < " << MAX_SIZE << ")" << endl;
                int nk;
                cin >> nk;
                if (nk >= MAX_SIZE) {
                    cout << "Invalid input. Continue with valid input. Thank you!" << endl;
                } else {
                    int x = dsu.Find_Set(nk);
                    if (x != 0) cout << "Component found in set : " << x << endl;
                    else cout << "Component not found" << endl;
                }
                break;
            case 3:
                cout << "Enter the components x and y (0 < x, y < " << MAX_SIZE << ")" << endl;
                int kn, m;
                cin >> kn >> m;
                if (kn >= MAX_SIZE || m >= MAX_SIZE) {
                    cout << "Invalid input. Continue with valid input. Thank you!" << endl;
                } else {
                    dsu.Union(kn, m);
                }
                break;
            case 4:
                cout << "Enter the components x (0 < x < " << MAX_SIZE << ")" << endl;
                int k;
                cin >> k;
                if (k >= MAX_SIZE) {
                    cout << "Invalid input. Continue with valid input. Thank you!" << endl;
                } else {
                    dsu.Print(k);
                }
                break;
//            case 6:
//                \n\t6. PrintParent
//                dsu.PrintParent();
//                break;
            default:
                cout << "Invalid input. Continue with valid input. Thank you!" << endl;
                break;
        }
        Menu();
        cin >> choice;
    }

    return 0;
}