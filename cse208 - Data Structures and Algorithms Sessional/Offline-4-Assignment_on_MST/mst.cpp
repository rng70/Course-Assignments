#include <bits/stdc++.h>
#include <limits>

#define vi vector<int>
#define pi pair<int, int>
#define pb push_back
#define FOR(i, a) for(int i=0;i<a;i++)
#define all(v) v.begin(),v.end()
using namespace std;

ifstream in(
        R"(D:\.assignments-And-Offlines-on-Data-Structure-and-Algorithms\cse208 - Data Structures and Algorithms Sessional\.clionProjectToDoOffline\offline_and_reports\Offline-4-Assignment_on_MST\data.txt)");

ofstream out(
        R"(D:\.assignments-And-Offlines-on-Data-Structure-and-Algorithms\cse208 - Data Structures and Algorithms Sessional\.clionProjectToDoOffline\offline_and_reports\Offline-4-Assignment_on_MST\output.txt)",
        ios_base::app);

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
    vector<Edge> E;
public:
    Graph(bool d, bool f = false) : dir(d), f_n(f) {}

    void setVertices(int n) {
        this->V = n;
        vert.resize(V);
        d.resize(V, INT_MAX);
    }

    int getVertices() {
        return V;
    }

    vector<Edge> &getEdges() {
        return E;
    }

    bool getWriteOption() {
        return f_n;
    }

    bool addEdge(int u, int v, double w) {
        if ((u >= 0 && u < V) && (v >= 0 && v < V)) {
            double W = getWeight(u, v);
            if (W != INT_MAX && W != w) {
                E.emplace_back(u, v, w); // passing three different integer and appending them as Edge object;
                // Same as passing Edge(u, v, w) in push_back
                // .i.e E.push_back(Edge(u, v, w)
                if (!dir)
                    E.emplace_back(v, u, w);
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
        if (!dir)
            removeEdge(v, u);
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

    void edgeToList(vector<vector<pi > > &adjList) {
        for (Edge e : E) {
            adjList[(int) e.get()].pb({(int) e.get('v'), (int) e.get('w')});
        }
    }

    void printGraph() {
        if (f_n)
            out << "Graph: " << endl;
        if (!f_n)
            cout << "Graph:" << endl;
        vector<vector<pi > > adjList(V);
        edgeToList(adjList);
        FOR(i, V) {
            if (!f_n)
                cout << i << " : ";
            if (f_n)
                out << i << " : ";
            int t = 1;
            for (auto v:adjList[i]) {
                if (!f_n)
                    cout << v.first << "(" << v.second << ")";
                if (f_n)
                    out << v.first << "(" << v.second << ")";
                if (t != adjList[i].size()) {
                    if (!f_n)
                        cout << " --> ";
                    if (f_n)
                        out << " --> ";
                }
                t++;
            }
            if (!f_n)
                cout << endl;
            if (f_n)
                cout << endl;
        }
    }
};

class DisjointSets {
    int *parent, *rank;
    int n;

    void makeSet() {
        for (int i = 0; i <= n; i++) {
            rank[i] = 0;
            parent[i] = i;
        }
    }

public:
    DisjointSets(int N) : n(N) {
        parent = new int[n + 1];
        rank = new int[n + 1];
        makeSet();
    }

    int Find(int u) {
        if (u != parent[u])
            parent[u] = Find(parent[u]);
        return parent[u];
    }

    void Union(int x, int y) {
        x = Find(x), y = Find(y);
        if (rank[x] > rank[y])
            parent[y] = x;
        else
            parent[x] = y;
        if (rank[x] == rank[y])
            rank[y]++;
    }
};

void menu() {
    cout << "\t1. Prim's Algorithm\n\t2. Kruskal's Algorithm\n\t3. Print Graph\n\t4. Exit" << endl;
}

void primAlgorithm(Graph &g, int start) {
    // this function is implemented in O(E log(V))
    // storing root node
    int root = start;

    // necessary variables
    int min_cost = 0;
    vi parent(g.getVertices(), -1);
    vi key(g.getVertices(), INT_MAX);
    bool visited[g.getVertices()];

    // setting necessary values
    memset(visited, false, sizeof(visited));

    // declaring adjacency list
    vector<vector<pi > > adjLists(g.getVertices());
    g.edgeToList(adjLists);
    //  g.printAdjList(adjLists);

    // declaring minimum priority queue
    priority_queue<pair<int, pi >, vector<pair<int, pi > >, greater<> > pq;
    pq.push({0, {start, start}});

    // path store
    vector<pi > path;

    while (!pq.empty()) {
        pair<int, pi > p = pq.top();
        pq.pop();

        start = p.second.first;
        //checking cycle
        if (visited[start])
            continue;
        min_cost += p.first;
        visited[start] = true;
        path.push_back(p.second);

        for (auto adjList:adjLists[start]) {
            if (!visited[adjList.first] && key[adjList.first] > adjList.second) {
                key[adjList.first] = adjList.second;
                pq.push({adjList.second, {adjList.first, start}});
            }
        }
    }
    if (!g.getWriteOption()) {
        cout << min_cost << endl << "Prim's algorithm:" << endl;
        cout << "Root node = " << root << endl;
        for (int i = 1; i < path.size(); i++) {
            cout << path[i].first << " " << path[i].second << endl;
        }
    } else {
        out << min_cost << endl << "Prim's algorithm:" << endl;
        out << "Root node = " << root << endl;
        for (int i = 1; i < path.size(); i++) {
            out << path[i].first << " " << path[i].second << endl;
        }
    }
}

void primAlgorithm2(Graph &g, int start) {
    // this function is implemented in O(E log(E))
    // storing root node
    int root = start;

    // necessary variables
    int min_cost = 0;
    vi parent(g.getVertices(), -1);
    bool visited[g.getVertices()];

    // setting necessary values
    memset(visited, false, sizeof(visited));

    // declaring adjacency list
    vector<vector<pi > > adjLists(g.getVertices());
    g.edgeToList(adjLists);
    //  g.printAdjList(adjLists);

    // declaring minimum priority queue
    priority_queue<pair<int, pi >, vector<pair<int, pi > >, greater<> > pq;
    pq.push({0, {start, start}});

    // path store
    vector<pi > path;

    while (!pq.empty()) {
        pair<int, pi > p = pq.top();
        pq.pop();

        start = p.second.first;
        //checking cycle
        if (visited[start])
            continue;
        min_cost += p.first;
        visited[start] = true;
        path.push_back(p.second);

        for (auto adjList:adjLists[start]) {
            if (!visited[adjList.first]) {
                pq.push({adjList.second, {adjList.first, start}});
            }
        }
    }
    if (!g.getWriteOption()) {
        cout << min_cost << endl << "Prim's algorithm:" << endl;
        cout << "Root node = " << root << endl;
        for (int i = 1; i < path.size(); i++) {
            cout << path[i].first << " " << path[i].second << endl;
        }
    } else {
        out << min_cost << endl << "Prim's algorithm:" << endl;
        out << "Root node = " << root << endl;
        for (int i = 1; i < path.size(); i++) {
            out << path[i].first << " " << path[i].second << endl;
        }
    }
}

void kruskalAlgorithm(Graph &g) {
    vector<pi > p;
    int w = 0;
    sort(all(g.getEdges()), [&](Edge &a, Edge &b) { return a.get('w') < b.get('w'); });

    DisjointSets disjointSets(g.getVertices());
    vector<Edge>::iterator it;
    for (it = g.getEdges().begin(); it != g.getEdges().end(); it++) {
        int u = it->get();
        int v = it->get('v');

        int parent_u = disjointSets.Find(u);
        int parent_v = disjointSets.Find(v);
        if (parent_u != parent_v) {
            w += it->get('w');
            disjointSets.Union(u, v);
            p.emplace_back(u, v);
        }
    }
    if (!g.getWriteOption()) {
        cout << w << endl << "Kruskal's algorithm:" << endl;
        for (auto &i:p) {
            cout << i.first << " " << i.second << endl;
        }
    } else {
        out << w << endl << "Kruskal's algorithm:" << endl;
        for (auto &i:p) {
            out << i.first << " " << i.second << endl;
        }
    }
}

void input(Graph &g) {
    int choice;
    while (true) {
        menu();
        cin >> choice;

        if (choice == 1) {
            primAlgorithm(g, 3);
        } else if (choice == 2) {
            kruskalAlgorithm(g);
        } else if (choice == 3) {
            g.printGraph();
        } else if (choice == 4) {
            break;
        }
    }
}

void consoleInput(bool wr = false) {
    Graph g(false, wr);

    int N, M;
    cin >> N >> M;
    g.setVertices(N);

    int u, v, w;
    while (M--) {
        cin >> u >> v >> w;
        g.addEdge(u, v, w);
    }
    if (!wr)
        cout << "Graph created" << endl;
    else {
        out << "---------------Start---------------" << endl;
        out << "Graph created" << endl;
    }
    input(g);
}

void fileInput(bool wr = true) {
    Graph g(false, wr);
    if (wr) out << "---------------Start---------------" << endl;

    int N, M;
    in >> N >> M;
    g.setVertices(N);

    int u, v, w;
    while (M--) {
        in >> u >> v >> w;
        g.addEdge(u, v, w);
    }
    if (wr)
        out << "Graph created" << endl;
    else
        cout << "Graph Created" << endl;
    input(g);
}

void input() {
    string i, o;
    bool fi = false, fo = false;
    cout << "Do you want file input?(Y/N):";
    cin >> i;
    if (i == "Y" || i == "y") fi = true;
    cout << "Do you want file output?(Y/N):";
    cin >> o;
    if (o == "Y" || o == "y") fo = true;

    if (fi && fo)
        fileInput();
    else if (fi && !fo)
        fileInput(false);
    else if (!fi && !fo)
        consoleInput();
    else
        consoleInput(true);
}

int main() {
    input();
}