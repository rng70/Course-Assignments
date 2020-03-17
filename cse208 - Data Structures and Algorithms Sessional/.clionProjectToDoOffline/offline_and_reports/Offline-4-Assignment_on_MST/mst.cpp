#include <bits/stdc++.h>
#include <limits>

#define vi vector<int>
#define pi pair<int, int>
#define pb push_back
#define FOR(i, a) for(int i=0;i<a;i++)
using namespace std;

class Edge {
    int u, v;
    double w;
public:
    Edge(int u, int v, double w) : u(u), v(v), w(w) {}

    double get(char ch = 'u') {
        return ((ch == 'u') ? (double) u : ((ch == 'v') ? (double) v : w));
    }
};

int comp(Edge a, Edge b) {
    return a.get('w') > b.get('w');
}

class Graph {
    int V;
    bool dir, f_n;
    vi vert, d;
//    vi d;
    vector<Edge> E;
    double **parentMatrix{}, **distanceMatrix{};
public:
    Graph(bool d, bool f = false) : dir(d), f_n(f) {}

    ~Graph() {
        FOR(i, V) {
            delete[] parentMatrix[i];
            delete[] distanceMatrix[i];
        }
        delete[] parentMatrix;
        delete[] distanceMatrix;
        parentMatrix = distanceMatrix = nullptr;
    }

    void setVertices(int n) {
        this->V = n + 1;
        vert.resize(V);
        d.resize(V, INT_MAX);
        parentMatrix = new double *[V];
        distanceMatrix = new double *[V];
        FOR(i, V) {
            parentMatrix[i] = new double[V];
            distanceMatrix[i] = new double[V];
        }
    }

    bool addEdge(int u, int v, double w) {
        if ((u >= 0 && u < V) && (v >= 0 && v < V)) {
            double W = getWeight(u, v);
            if (W != INT_MAX && W != w) {
                E.emplace_back(u, v, w); // passing three different integer and appending them as Edge object;
                // Same as passing Edge(u, v, w) in push_back
                // .i.e E.push_back(Edge(u, v, w)
                return true;
            }
        }
        return false;
    }

    void removeEdge(int u, int v) {
        if (isEdge(u, v)) {
            E.erase(remove_if(E.begin(), E.end(), [&](Edge &e) {
                return ((int) e.get() == u && (int) e.get('v') == v);
            }), E.end());
        }
    }

    bool isEdge(int u, int v) {
        if ((u >= 0 && u < V) && (v >= 0 && v < V)) {
            return (find_if(E.begin(), E.end(), [&](Edge &e) {
                return ((int) e.get() == u && (int) e.get('v') == v);
            }) != E.end());
        }
        return false;
    }

    double getWeight(int u, int v) {
        if ((u >= 0 && u < V) && (v >= 0 && v < V) && isEdge(u, v)) {
            for (Edge e:E) {
                int f = (int) e.get(), s = (int) e.get('v');
                if (f == u && s == v) {
                    return e.get('w');
                }
            }
        }
        return numeric_limits<double>::infinity();
    }

    Edge *searchEdge(int u, int v) {
        for (Edge &e:E) {
            int f = (int) e.get(), s = (int) e.get('v');
            if (f == u && s == v)
                return &e;
        }
        return nullptr;
    }

    void reweightEdge(int u, int v, double w) {
        removeEdge(u, v);
        addEdge(u, v, w);
        Edge *e = searchEdge(u, v);
    }

    double getShortestPathWeight(int u, int v) {
        return distanceMatrix[u][v];
    }

    void edgeToList(vector<vector<pi > > &adjList) {
        for (Edge e : E) {
            adjList[(int) e.get()].pb({(int) e.get('v'), (int) e.get('w')});
        }
    }

    void printGraph() {
        ofstream out("output.txt", ios_base::app);
        if (f_n)
            out << "Graph: " << endl;
        cout << "Graph:" << endl;
        vector<vector<pi > > adjList(V);
        edgeToList(adjList);
        FOR(i, V) {
            if (i == 0)
                continue;
            cout << i << " : ";
            if (f_n)
                out << i << " : ";
            int t = 1;
            for (auto v:adjList[i]) {
                cout << v.first << "(" << v.second << ")";
                if (f_n)
                    out << v.first << "(" << v.second << ")";
                if (t != adjList[i].size()) {
                    cout << " --> ";
                    if (f_n)
                        out << " --> ";
                }

                t++;
            }
            cout << endl;
            if (f_n)
                cout << endl;
        }
    }

    void primAlgorithm(int n) {
        vector<vector<pi > > adjLists(V);
        edgeToList(adjLists);
    }

    void kruskalAlgorithm(int n) {
        vi st(V, -1);
        sort(E.begin(), E.end(), comp);
        for (auto e:E) {
            cout << e.get() << " " << e.get('v') << " " << e.get('w') << endl;
        }
        vi pt(V, -1);
    }

};

void menu() {
    cout << "\t1. Prim's Algorithm\n\t"
            "2. Kruskal's Algorithm\n\t3. Print Graph\n\t4. Exit" << endl;
}

void consoleInput() {
    Graph g(true);

    int N, M;
    cin >> N >> M;
    g.setVertices(N);

    int u, v, w;
    while (M--) {
        cin >> u >> v >> w;
        g.addEdge(u, v, w);
    }
    cout << "Graph created\n";
    int choice;
    while (true) {
        menu();
        cin >> choice;

        if (choice == 1) {
            g.primAlgorithm(0);
        } else if (choice == 2) {
            g.kruskalAlgorithm(3);
        } else if (choice == 3) {
            g.printGraph();
        } else if (choice == 4) {
            break;
        }
    }
}

void fileInput() {
    Graph g(true, true);
    ifstream in("data.txt");
    ofstream out("output.txt", ios_base::app);
    out << "---------------Start---------------" << endl;

    int N, M;
    in >> N >> M;
    g.setVertices(N);

    int u, v, w;
    while (M--) {
        in >> u >> v >> w;
        g.addEdge(u, v, w);
    }
    out << "Graph created\n";
    int choice;
    while (true) {
        menu();
        in >> choice;
        break;
    }
}

int main() {
    int n;
    cout << "Enter choice\n\t1. consoleInput\n\t2. fileInput" << endl;
    cin >> n;
    if (n == 1)
        consoleInput();
    if (n == 2)
        fileInput();
}
