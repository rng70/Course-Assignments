// Done by rng70

#include <bits/stdc++.h>

using namespace std;

class Graph{
    int vertices;
    int edges;
    vector<vector<int> >edgeLists;
    bool directed;
public:
    Graph(bool directed = false){
        this->directed = directed;
    }
    ~Graph(){

    }
    void set_nVertices(int nVertices){
        this->vertices = nVertices;
        edgeLists.resize(nVertices, vector<int>(0));
    }
    void removeEdge(int u, int v){
        vector<int> :: iterator it;
        if(!directed)
        {
            it = find(edgeLists[v].begin(), edgeLists[v].end(), u);
            if(it != edgeLists[v].end()){
                edgeLists[v].erase(it);
            }
        }
        it = find(edgeLists[u].begin(), edgeLists[u].end(), v);
        if(it!= edgeLists[u].end())
            edgeLists[u].erase(it);
    }
    void addEdge(int u, int v){
        vector<int> :: iterator it;

        if(!directed){
            if(find(edgeLists[v].begin(), edgeLists[v].end(), u)==edgeLists[v].end()){
                edgeLists[v].push_back(u);
            }
        }
        if(find(edgeLists[u].begin(), edgeLists[u].end(), v)==edgeLists[u].end()){
            edgeLists[u].push_back(v);
        }
    }
    void Dijkstra(int source, int destination){
        vector<int> distance(vertices);
        for(auto &i:distance)
        {
            i = INFINITY;
        }
        distance[source] = 0;
        if(destination == source){
            cout << " Distance form " << source << " to " << destination << " is " << distance[destination] << endl;
            return ;
        }
        priority_queue<int, vector<int>, greater<> > priorityQueue;
        priorityQueue.push(source);

        while(!priorityQueue.empty())
        {
            int temp_source = priorityQueue.top();
            priorityQueue.pop();
//            for
        }
    }
};
