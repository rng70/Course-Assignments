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

class Graph {
    int V;
    bool dir;
    vi vert;
    vector<Edge> E;
    double **parentMatrix, **distanceMatrix;
public:
    Graph(bool d) : dir(d) {}

    ~Graph() {
        for (int i = 0; i < V; i++) {
            delete[] parentMatrix[i];
            delete[] distanceMatrix[i];
        }
        delete[] parentMatrix;
        delete[] distanceMatrix;
        parentMatrix = distanceMatrix = nullptr;
    }

    void setVertices(int n) {
        this->V = n;
        vert.resize(n);
        parentMatrix = new double *[n];
        distanceMatrix = new double *[n];
        for (int i = 0; i < n; i++) {
            parentMatrix[i] = new double[n];
            distanceMatrix[i] = new double[n];
        }
    }

    bool addEdge(int u, int v, int w) {
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
            vector<Edge>::iterator it;
            return find_if(E.begin(), E.end(), [&](Edge &e) {
                return ((int) e.get() == u && (int) e.get('v') == v);
            }) != E.end();
        }
//            for (Edge e:E) {
//                int f = (int) e.get(), s = (int) e.get('v');
//                if (f == u && s == v) {
//                    return true;
//                }
//            }
//        }
//        return false;
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

    void reweightEdge(int u, int v, int w) {
        removeEdge(u, v);
        addEdge(u, v, w);
    }

    Edge *searchEdge(int u, int v) {
        for (Edge &e:E) {
            int f = (int) e.get(), s = (int) e.get('v');
            if (f == u && s == v)
                return &e;
        }
        return nullptr;
    }

    void floydWarshall() {
        FOR(i, V) {
            FOR(j, V) {
                if (i == j)
                    distanceMatrix[i][j] = 0;
                else
                    distanceMatrix[i][j] = getWeight(i, j);
            }
        }
        FOR(k, V) {
            FOR(i, V) {
                FOR(j, V) {
                    if (distanceMatrix[i][j] > distanceMatrix[i][k] + distanceMatrix[k][j]) {
                        distanceMatrix[i][j] = distanceMatrix[i][k] + distanceMatrix[k][j];
                        parentMatrix[i][j] = k;
                    } else
                        parentMatrix[i][j] = j;
                }
            }
        }
    }

    bool BellmanFord() {
        vi d(V, INT_MAX);
        FOR(i, V) {
            for (Edge &e:E) {
                int u = (int) e.get(), v = (int) e.get('v'), w = (int) e.get('w');
                if (d[v] != INT_MAX && d[v] > d[u] + w) {
                    d[v] = d[u] + w;
                }
            }
        }
        for (Edge &e:E) {
            int u = (int) e.get(), v = (int) e.get('v'), w = (int) e.get('w');
            if (d[v] != INT_MAX && d[v] > d[u] + w) {
                return true;
            }
        }
        return false;
    }

    void Dijkstra(int n) {
        priority_queue<pi, vector<pi >, greater<> > pq;
        vector<vector<pi > > adjList;
        for (Edge e : E) {
            adjList[(int) e.get()].pb({(int) e.get('v'), (int) e.get('w')});
        }

        distanceMatrix[n][n] = 0;
        pq.push({0, n});

        while (!pq.empty()) {
            int w = (int) pq.top().first;
            int u = pq.top().second;

            for (auto e : adjList[u]) {
                int v = e.first;
                int d = (int) abs(e.second);
                if (distanceMatrix[v][v] > distanceMatrix[u][v] + d) {
                    distanceMatrix[v][v] = distanceMatrix[u][v] + d;
                    pq.push({distanceMatrix[v][v], v});
                    parentMatrix[v][v] = u;
                }
            }
        }

    }

    void johnsonsAlgo() {
        return;
    }

    double getShortestPathWeight(int u, int v) {
        return distanceMatrix[u][v];
    }

    void printShortestPath(int u, int v) {
        int p = v;
        vi nodes;
        vi weight;
        while (p != u) {
            nodes.push_back(p);
            weight.push_back(getWeight(p, (int) parentMatrix[u][p]));
            p = (int) parentMatrix[u][p];
        }
    }

    void printDistanceMatrix() {
        for (int i = 0; i < V; i++) {
            for (int j = 0; j < V; j++) {
                if (distanceMatrix[i][j] == numeric_limits<double>::infinity()) {
                    cout << "INF ";
                    continue;
                }
                cout << distanceMatrix[i][j] << " ";
            }
            cout << endl;
        }
    }

    void printPredecessorMatrix() {
        FOR(i, V) {
            FOR(j, V) {
                if ((int) parentMatrix[i][j] == -1) {
                    cout << "NIL ";
                    continue;
                }
                cout << (int) parentMatrix[i][j] << " ";
            }
            cout << endl;
        }
    }

    void cleanSPInfo() {
        FOR(i, V) {
            FOR(j, V) {
                distanceMatrix[i][j] = numeric_limits<double>::infinity();
                parentMatrix[i][j] = -1;
            }
        }
    }
};

void menu() {
    cout << "\t1. Clear value of parent and distance Matrix\n\t"
            "2. Implement Floyd-Warshall\n\t3. Implement Johnson’s Algorithm\n\t"
            "4. Print Shortest path\n\t5. pPrint graph\n\t6. Print distance Matrix D"
            "\n\t7. Prints predecessor matrix P\n\t8. Exit" << endl;
}

int main() {
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

        if (choice == 1)
            g.cleanSPInfo();
        else if (choice == 2)
            g.floydWarshall();
        else if (choice == 3)
            g.johnsonsAlgo();
        else if (choice == 4) {
            cout << "Enter u and v ";
            int s, d;
            cin >> s >> d;
            g.printShortestPath(s, d);
        } else if (choice == 5) {
//            g.printGraph();
        } else if (choice == 6) {
            g.printDistanceMatrix();
        } else if (choice == 7){
            g.printPredecessorMatrix();
        } else{
            break;
        }
    }

}