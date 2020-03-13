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
//        if(searchEdge(u, v)!= nullptr){
//            e.set(searchEdge(u, v), 'w', w);
//        }
    }

    double getShortestPathWeight(int u, int v) {
        return distanceMatrix[u][v];
    }

    void printShortestPath(int u, int v) {
        ofstream out("output.txt", ios_base::app);
        cout << "Shortest Path Weight: " << getShortestPathWeight(u, v) << endl;
        if (f_n)
            out << "Shortest Path Weight: " << getShortestPathWeight(u, v) << endl;

        int p = v;
        vi nodes;
        vi weight;
        while (p != u) {
            nodes.push_back(p);
//            cout << "G " << p << " " << parentMatrix[u][p] << " " << getWeight(u, parentMatrix[u][p]);
            weight.push_back(getWeight((int) parentMatrix[u][p], p));
            p = (int) parentMatrix[u][p];
        }
        reverse(nodes.begin(), nodes.end());
        reverse(weight.begin(), weight.end());
        int t = 0;
        cout << "Path: " << u << " --> ";
        if (f_n)
            out << "Path: " << u << " --> ";
        int c = 1;
        for (auto n:nodes) {
            if (c != nodes.size()) {
                cout << n << "(" << weight[t] << ") --> ";
                if (f_n)
                    out << n << "(" << weight[t] << ") --> ";
            } else {
                cout << n << "(" << weight[t] << ")";
                if (f_n)
                    out << n << "(" << weight[t] << ")";
            }
            t++;
            c++;
        }
        cout << endl;
        if (f_n)
            out << endl;
    }

    void printDistanceMatrix() {
        ofstream out("output.txt", ios_base::app);
        if (f_n)
            out << "Distance Matrix:" << endl;
        cout << "Distance Matrix:" << endl;
        FOR(i, V) {
            if (i == 0)
                continue;
            FOR(j, V) {
                if (j == 0)
                    continue;
                if (distanceMatrix[i][j] == numeric_limits<double>::infinity()) {
                    cout << "INF ";
                    if (f_n)
                        out << "INF ";
                    continue;
                }
                cout << distanceMatrix[i][j] << " ";
                if (f_n)
                    out << distanceMatrix[i][j] << " ";
            }
            cout << endl;
            if (f_n)
                out << endl;
        }
    }

    void printPredecessorMatrix() {
        ofstream out("output.txt", ios_base::app);
        if (f_n)
            out << "Predecessor Matrix:" << endl;
        cout << "Predecessor Matrix:" << endl;
        FOR(i, V) {
            if (i == 0)
                continue;
            FOR(j, V) {
                if (j == 0)
                    continue;
                if ((int) parentMatrix[i][j] == -1) {
                    cout << "NIL ";
                    if (f_n)
                        out << "NIL ";
                    continue;
                }
                cout << (int) parentMatrix[i][j] << " ";
                if (f_n)
                    out << (int) parentMatrix[i][j] << " ";
            }
            cout << endl;
            if (f_n)
                out << endl;
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
            if(i==0)
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

    void floydWarshall() {
        FOR(i, V) {
            FOR(j, V) {
                if (i == j)
                    distanceMatrix[i][j] = 0;
                else {
                    distanceMatrix[i][j] = getWeight(i, j);
                    parentMatrix[i][j] = i;
                }
            }
        }
        FOR(k, V) {
            FOR(i, V) {
                FOR(j, V) {
                    if ((distanceMatrix[i][j] > distanceMatrix[i][k] + distanceMatrix[k][j])) {
                        distanceMatrix[i][j] = distanceMatrix[i][k] + distanceMatrix[k][j];
                        parentMatrix[i][j] = parentMatrix[k][j];
                    } else
                        parentMatrix[i][j] = parentMatrix[i][j];
                }
            }
        }
    }

    bool BellmanFord() {
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

        vector<vector<pi > > adjList(V);
        edgeToList(adjList);

        bool visited[V];
        for (auto &i:visited) {
            i = false;
        }

        distanceMatrix[n][n] = 0;
        pq.push({0, n});

        while (!pq.empty()) {
            int u = pq.top().second;
            pq.pop();
            if (visited[u])
                continue;

            for (auto e : adjList[u]) {
                if (distanceMatrix[n][e.first] > distanceMatrix[n][u] + e.second &&
                    distanceMatrix[n][u] != numeric_limits<double>::infinity()) {
                    distanceMatrix[n][e.first] = distanceMatrix[n][u] + e.second;
                    pq.push({distanceMatrix[n][e.first], e.first});
                    parentMatrix[n][e.first] = u;
                }
            }
            visited[u] = true;
        }
    }

    void johnsonsAlgo() {
        ofstream out("output.txt", ios_base::app);
        FOR(i, V) {
            if (i == 0)
                continue;
            addEdge(0, i, 0);
        }
        if (BellmanFord()) {
            cout << "Negative cycle detected" << endl;
            if (f_n)
                out << "Negative cycle detected" << endl;
            return;
        }
        for (Edge e:E) {
            reweightEdge((int) e.get(), (int) e.get('v'), e.get('w') + (double)
                    d[(int) e.get()] - (double) d[(int) e.get('v')]);
        }
        FOR(i, V) {
            if (i == 0)
                continue;
            Dijkstra(i);
            for (Edge e:E) {
                reweightEdge((int) e.get(), (int) e.get('v'), e.get('w') - (double)
                        d[(int) e.get()] + (double) d[(int) e.get('v')]);
            }
            FOR(j, V) {
                distanceMatrix[i][j] += d[j] - d[i];
            }
        }
        FOR(i, V) {
            removeEdge(0, i);
        }

    }
};

void menu() {
    cout << "\t1. Clear value of parent and distance Matrix\n\t"
            "2. Implement Floyd-Warshall\n\t3. Implement Johnson’s Algorithm\n\t"
            "4. Print Shortest path\n\t5. pPrint graph\n\t6. Print distance Matrix D"
            "\n\t7. Prints predecessor matrix P\n\t8. Exit" << endl;
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
            g.cleanSPInfo();
            cout << "APSP matrices cleared" << endl;
        } else if (choice == 2) {
            g.floydWarshall();
            cout << "Floyd-Warshall algorithm implemented" << endl;
        } else if (choice == 3) {
            g.johnsonsAlgo();
            cout << "Johnson's algorithm implemented" << endl;
        } else if (choice == 4) {
            cout << "Enter u and v ";
            int s, d;
            cin >> s >> d;
            g.printShortestPath(s, d);
        } else if (choice == 5) {
            g.printGraph();
        } else if (choice == 6) {
            g.printDistanceMatrix();
        } else if (choice == 7) {
            g.printPredecessorMatrix();
        } else {
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

        if (choice == 1) {
            g.cleanSPInfo();
            out << "APSP matrices cleared" << endl;
        } else if (choice == 2) {
            g.floydWarshall();
            out << "Floyd-Warshall algorithm implemented" << endl;
        } else if (choice == 3) {
            g.johnsonsAlgo();
            out << "Johnson's algorithm implemented" << endl;
        } else if (choice == 4) {
            int s, d;
            in >> s >> d;
            g.printShortestPath(s, d);
        } else if (choice == 5) {
            g.printGraph();
        } else if (choice == 6) {
            g.printDistanceMatrix();
        } else if (choice == 7) {
            g.printPredecessorMatrix();
        } else {
            out << "---------------End---------------" << endl << endl;
            break;
        }
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
