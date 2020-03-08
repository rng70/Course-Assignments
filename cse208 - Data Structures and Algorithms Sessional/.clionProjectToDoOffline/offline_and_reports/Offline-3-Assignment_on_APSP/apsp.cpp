#include <bits/stdc++.h>

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
    vector<int> vert;
    vector<Edge> E;
public:
    Graph(bool d) : dir(d) {}

    void setVertices(int n) {
        this->V = n;
        vert.resize(n);
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
        return INT_MAX;
    }
    void reweightEdge(int u, int v, int w){
       removeEdge(u, v);
       addEdge(u, v, w);
    }
    void floydWarshall(){
        return ;
    }
    bool BellmanFord(){
        return true;
    }
    void Dijkstra(int n){
        return ;
    }
    void johnsonsAlgo(){
        return ;
    }

};

int main() {

}