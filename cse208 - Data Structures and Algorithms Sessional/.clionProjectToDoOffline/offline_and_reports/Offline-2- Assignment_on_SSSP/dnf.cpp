#include <bits/stdc++.h>

#define pi pair<int, int>

using namespace std;

class Graph {
    int vertices;
    vector<vector<pi > > edgeLists;
    bool directed;
public:
    Graph(bool directed, int vertices) {
        this->directed = directed;
        this->vertices = vertices;
        edgeLists.resize(vertices);
    }

//    void removeEdge(int u, int v, int weight) {
//        vector<pair<int, int> >::iterator it;
//        pi p(weight, v);
//        if (!directed) {
//            pi m(weight, u);
//            it = find(edgeLists[v].begin(), edgeLists[v].end(), m);
//            if (it != edgeLists[v].end()) {
//                edgeLists[v].erase(it);
//            }
//        }
//        it = find(edgeLists[u].begin(), edgeLists[u].end(), p);
//        if (it != edgeLists[u].end())
//            edgeLists[u].erase(it);
//    }

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

    static void printDnBFPath(int destination, vector<int> &dijkstra_path) {

        string path = " ";
        while (true) {
            if (destination == -1) {
                break;
            }
            path += to_string(destination);
            if (dijkstra_path[destination] != -1)
                path += +" -> ";
            destination = dijkstra_path[destination];
        }
        reverse(path.begin(), path.end());
        cout << path << endl;
    }

    void printGraph() {
        cout << " magi " << endl;
        for (int i = 0; i < vertices; i++) {
            cout << "vertex[" << i << "] : " << endl;
            for (auto &j : edgeLists[i]) {
                cout << '\t' << j.second << " " << j.first << endl;
            }
            cout << endl;
        }
    }

    void Dijkstra(int source, int destination) {

        vector<int> distance(vertices, INT_MAX);
        vector<int> dijkstra_path(vertices, -1);
        distance[source] = 0;

        priority_queue<pi, vector<pi >, greater<> > priorityQueue;
        priorityQueue.push(make_pair(distance[source], source));

        while (!priorityQueue.empty()) {
            pi temp_source_distance = priorityQueue.top();
            priorityQueue.pop();
            for (int i = 0; i < edgeLists[temp_source_distance.second].size(); i++) {
                pi p = edgeLists[temp_source_distance.second][i];
                int weight = p.first;
                int node = p.second;
                if (distance[node] > distance[temp_source_distance.second] + abs(weight)) {
                    distance[node] = distance[temp_source_distance.second] + abs(weight);
                    priorityQueue.push(make_pair(distance[node], node));
                    dijkstra_path[node] = temp_source_distance.second;
                }
            }
        }
        cout << "Dijkstra Algorithm:" << endl;
        cout << distance[destination] << endl;
        printDnBFPath(destination, dijkstra_path);
    }

    void BellmanFord(int source, int destination) {

        vector<int> distance(vertices, INT_MAX);
        vector<int> bellman_path(vertices, -1);
        distance[source] = 0;

        for(int m=1;m<vertices;m++){
            for (int i = 0; i < vertices; i++) {
                vector<pi > p = edgeLists[i];
                for (auto &j : p) {
                    int cur_source = j.second;
                    if (distance[i] != INT_MAX && distance[cur_source] > distance[i] + j.first) {
                        distance[cur_source] = distance[i] + j.first;
                        bellman_path[cur_source] = i;
                    }
                }
            }
        }
        cout << "Bellman Ford Algorithm:" << endl;
        for (int i = 0; i < vertices; i++) {
            vector<pi > p = edgeLists[i];
            for (auto &j : p) {
                int cur_source = j.second;
                if (distance[i] != INT_MAX && distance[cur_source] > distance[i] + j.first) {
                    cout << "Negative cycle detected" << endl;
                    return;
                }
            }
        }
        cout << distance[destination] << endl;
        printDnBFPath(destination, bellman_path);
    }
};

void menu() {
    cout << "Enter your choice" << endl;
    cout << "\t1. Run Dijkstra\n\t2. Run BellmanFord\n\t3. Print Graph\n\t4. Exit" << endl;
}

int main() {
    string filename = "D:\\.assignments-And-Offlines-on-Data-Structure-and-Algorithms\\cse208 - Data "
                      "Structures and Algorithms Sessional\\.clionProjectToDoOffline\\offline_and_reports\\"
                      "Offline-2- Assignment_on_SSSP\\input and output files\\input.txt";

    ifstream inputFile;
    inputFile.open(filename);
    int vertices, edges, source, destination;
    inputFile >> vertices >> edges;

    Graph g(true, vertices);
    int f_node, s_node, weight;
    while(edges--){
        inputFile >> f_node >> s_node >> weight;
        g.addEdge(f_node, s_node, weight);
    }
    inputFile >> source >> destination ;
    inputFile.close();

    while (true) {
        menu();
        int choice;
        cin >> choice;
        if (choice == 4)
            break;
        else if (choice == 1) {
            g.Dijkstra(source, destination);
        } else if (choice == 2) {
            g.BellmanFord(source, destination);
        } else if (choice == 3) {
            g.printGraph();
        }

    }
}
