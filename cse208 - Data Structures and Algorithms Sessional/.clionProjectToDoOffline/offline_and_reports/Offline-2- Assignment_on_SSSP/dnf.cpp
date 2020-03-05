// Done by rng70

#include <bits/stdc++.h>

#define pi pair<int, int>
#define not_finite 99999999

using namespace std;

class Graph {
    int vertices;
    int edges;
    vector<vector<pi > > edgeLists;
    bool directed;
public:
    explicit Graph(bool directed = false) {
        this->directed = directed;
    }

//    ~Graph(){
//        delete[][] edgeLists;
//    }
    void set_nVertices_mEdges(int nVertices, int n_edges) {
        this->vertices = nVertices;
        this->edges = n_edges;
        edgeLists.resize(nVertices, vector<pair<int, int> >());
    }

    void removeEdge(int u, int v, int weight) {
        vector<pair<int, int> >::iterator it;
        pi p(weight, v);
        if (!directed) {
            pi m(weight, u);
            it = find(edgeLists[v].begin(), edgeLists[v].end(), m);
            if (it != edgeLists[v].end()) {
                edgeLists[v].erase(it);
            }
        }
        it = find(edgeLists[u].begin(), edgeLists[u].end(), p);
        if (it != edgeLists[u].end())
            edgeLists[u].erase(it);
    }

    void addEdge(int u, int v, int weight) {

        if (!directed) {
            pi p(weight, u);
            if (find(edgeLists[v].begin(), edgeLists[v].end(), p) == edgeLists[v].end()) {
                edgeLists[v].push_back(p);
            }
        }
        pi m(weight, v);
        if (find(edgeLists[u].begin(), edgeLists[u].end(), m) == edgeLists[u].end()) {
            edgeLists[u].push_back(m);
        }
    }

    static void printDijkstraPath(int distance, vector<int> &dijkstra_path) {
        cout << "Dijkstra Algorithm:" << endl;
        cout << distance << endl;
        vector<int>::iterator it;
        for (it = dijkstra_path.begin(); it != dijkstra_path.end(); it++) {
            cout << *it;
            advance(it, 1);
            if (it != dijkstra_path.end())
                cout << " -> ";
            advance(it, -1);
        }
        cout << endl;
    }

    void printGraph() {
        cout << " magi " << endl;
        for (int i = 0; i < vertices; i++) {
            cout << "vertex[" << i << "] : " << endl;
            for (int j = 0; j < edgeLists[i].size(); j++) {
                cout << '\t' << edgeLists[i][j].second << " " << edgeLists[i][j].first << endl;
            }
            cout << endl;
        }
    }

    void Dijkstra(int source, int destination) {
        vector<long long> distance(vertices, not_finite);
//        vector<int> distance(vertices);
//        for (auto &I:distance)
//            I = INFINITY;
        vector<int> dijkstra_path;
        distance[source] = 0;
        if (destination == source) {
            cout << " Distance form " << source << " to " << destination << " is " << distance[destination] << endl;
            return;
        }
        priority_queue<pi, vector<pi >, greater<> > priorityQueue;
        priorityQueue.push(make_pair(distance[source], source));

        while (!priorityQueue.empty()) {
            pi temp_source_distance = priorityQueue.top();
            priorityQueue.pop();
            cout << temp_source_distance.second << " tmp_s -- " << endl;
            for (int i = 0; i < edgeLists[temp_source_distance.second].size(); i++) {
                pi p = edgeLists[temp_source_distance.second][i];
                int weight = p.first;
                int node = p.second;
                cout << '\t' << node << " inputed " << endl;
                if (distance[node] > distance[temp_source_distance.second] + weight) {
                    distance[node] = distance[temp_source_distance.second] + weight;
                    priorityQueue.push(make_pair(distance[node], node));
                }

            }
            dijkstra_path.push_back(temp_source_distance.second);
        }
        printDijkstraPath(distance[destination], dijkstra_path);
    }

    void BellmanFord(int source, int destination) {
        vector<int> distance(vertices, not_finite);
//        vector<int> distance(vertices);
//        for (auto &I:distance)
//            I = INFINITY;
        vector<int> bellman_path(vertices);
        distance[source] = 0;
        bellman_path[source] = -1;
        if (destination == source) {
            cout << " Distance form " << source << " to " << destination << " is " << distance[destination] << endl;
            return;
        }
        for (int i = 0; i < vertices; i++) {
            vector<pi > p = edgeLists[i];
            for (int j = 0; j < p.size(); j++) {
                int cur_source = p[j].second;
                if (distance[cur_source] > distance[i] + p[j].second) {
                    distance[cur_source] = distance[i] + p[j].second;
                    bellman_path[cur_source] = p[j].second;
                }
            }
        }
        for (int i = 0; i < vertices; i++) {
            vector<pi > p = edgeLists[i];
            for (int j = 0; j < p.size(); j++) {
                int cur_source = p[j].second;
                if (distance[cur_source] > distance[i] + p[j].second) {
                    cout << "Negative cycle detected" << endl;
                }
            }
        }
        cout << " Bellman distance : " << distance[destination] << endl;
    }
};

void menu() {
    cout << "Enter your choice" << endl;
    cout << "\t1. Run Dijkstra\n\t2. Run BellmanFord\n\t3. Print Graph\n\t4. Exit" << endl;
}

pair<int, int> readLastLine(const string &filename) {
    int source, destination;
    ifstream inputFile;
    inputFile.open(filename);

    // read last line
    inputFile.seekg(-1, ios_base::end);
    if (inputFile.peek() != '\n') {
//        // start searching for \n occurrence
//        while(true){
//            char ch;
//            inputfile.get(ch);
//            cout << " In loop "  << endl;
//            if((int)inputfile.tellg()<1){
//                // last and first lines are same
//                cout << " fuck you file " << endl;
//                inputfile.seekg(0);
//                break;
//            }
//            else if(ch == '\n'){
//                break;
//            }else{
//                inputfile.seekg(-2, ios_base::cur);
//            }
//        }
        inputFile.seekg(-1, ios_base::cur);
        int i = inputFile.tellg();
//        cout << " In loop " << i << endl;
        for (i; i > 0; i--) {
            if (inputFile.peek() == '\n') {
                // found;
                inputFile.get();
                break;
            }
            // move one charecter back
            inputFile.seekg(i, ios_base::beg);
        }
    }
    inputFile >> source >> destination;
//    cout << source << " s - d " << destination << endl;
    return make_pair(source, destination);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    string filename = "D:\\.assignments-And-Offlines-on-Data-Structure-and-Algorithms\\cse208 - Data "
                      "Structures and Algorithms Sessional\\.clionProjectToDoOffline\\offline_and_reports\\"
                      "Offline-2- Assignment_on_SSSP\\input and output files\\input.txt";

    ifstream inputFile;
    inputFile.open(filename);
    int vertices, edges;
    inputFile >> vertices >> edges;
//    cout << vertices << " v - e " << edges << endl;
    int source, destination;
    Graph g(true);
    g.set_nVertices_mEdges(vertices, edges);
    int f_node, s_node, weight;
    while (inputFile >> f_node >> s_node >> weight) {
        g.addEdge(f_node, s_node, weight);
//        cout << f_node << " " << s_node << " " << weight << " f s w " << endl;
    }
    inputFile.close();
    pair<int, int> p = readLastLine(filename);
    source = p.first;
    destination = p.second;
//    cout << source << " sjdfklsj " << destination << endl;
    while (true) {
        menu();
        int choice;
        cin >> choice;
        if (choice == 4)
            break;
        else if (choice == 1) {
//            cout << "Enter source and destination nodes respectively : ";
//            int source, destination;
//            cin >> source >> destination;
            g.Dijkstra(source, destination);
        } else if (choice == 2) {
//            cout << "Enter source and destination nodes respectively : ";
//            int source, destination;
//            cin >> source >> destination;
            g.BellmanFord(source, destination);
        } else if (choice == 3) {
            g.printGraph();
        }

    }
}
