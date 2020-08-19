#include <cstdio>
#include <chrono>
#include <iostream>
#include <fstream>
#include <random>

#define NULL_VALUE -999999
#define INFINITY 999999
#define WHITE 1
#define GREY 2
#define BLACK 3

using namespace std;

std::random_device dev;
std::mt19937 rng(dev());

class Queue {
    int queueInitSize;
    int queueMaxSize;
    int *data;
    int length;
    int front;
    int rear;
public:
    Queue();

    ~Queue();

    void enqueue(int item); //insert item in the queue
    int dequeue(); //returns the item according to FIFO
    bool empty(); //return true if Queue is empty
};

Queue::Queue() {
    queueInitSize = 2;
    queueMaxSize = queueInitSize;
    data = new int[queueMaxSize]; //allocate initial memory
    length = 0;
    front = 0;
    rear = 0;
}

void Queue::enqueue(int item) {
    if (length == queueMaxSize) {
        int *tempData;
        //allocate new memory space for tempList
        queueMaxSize = 2 * queueMaxSize;
        tempData = new int[queueMaxSize];
        int i, j;
        j = 0;
        for (i = rear; i < length; i++) {
            tempData[j++] = data[i]; //copy items from rear
        }
        for (i = 0; i < rear; i++) {
            tempData[j++] = data[i]; //copy items before rear
        }
        rear = 0;
        front = length;
        delete[] data; //free the memory allocated before
        data = tempData; //make list to point to new memory
    }
    data[front] = item; //store new item
    front = (front + 1) % queueMaxSize;
    length++;
}

bool Queue::empty() {
    return length == 0;
}

int Queue::dequeue() {
    if (length == 0) return NULL_VALUE;
    int item = data[rear];
    rear = (rear + 1) % queueMaxSize;   // circular queue implementation
    length--;
    return item;
}


Queue::~Queue() {
    if (data) delete[] data; //deallocate memory
    data = 0; //set to NULL
}
//-----------------------------------------
//implementation of queue class has ended
//-----------------------------------------
//-----------------------------------------
//implementation of ArrayLists class starting
//-----------------------------------------

class ArrayList {
    int *list;
    int length;
    int listMaxSize;
    int listInitSize;
public:
    ArrayList();

    ~ArrayList();

    int searchItem(int item);

    void insertItem(int item);

    void removeItem(int item);

    void removeItemAt(int item);

    int getItem(int position);

    int getLength();

    bool empty();

    void printList();
};


ArrayList::ArrayList() {
    listInitSize = 2;
    listMaxSize = listInitSize;
    list = new int[listMaxSize];
    length = 0;
}

void ArrayList::insertItem(int newitem) {
    int *tempList;
    if (length == listMaxSize) {
        //allocate new memory space for tempList
        listMaxSize = 2 * listMaxSize;  // doubling memory when array is full
        tempList = new int[listMaxSize];
        int i;
        for (i = 0; i < length; i++) {
            tempList[i] = list[i]; //copy all items from list to tempList
        }
        delete[] list; //free the memory allocated before
        list = tempList; //make list to point to new memory
    };
    list[length] = newitem; //store new item
    length++;
}

int ArrayList::searchItem(int item) {
    int i = 0;
    for (i = 0; i < length; i++) {
        if (list[i] == item) return i;
    }
    return NULL_VALUE;
}

void ArrayList::removeItemAt(int position) //do not preserve order of items
{
    if (position < 0 || position >= length) return; //nothing to remove
    list[position] = list[length - 1];
    length--;
}

void ArrayList::removeItem(int item) {
    int position;
    position = searchItem(item);
    if (position == NULL_VALUE) return; //nothing to remove
    removeItemAt(position);
}

int ArrayList::getItem(int position) {
    if (position < 0 || position >= length) return NULL_VALUE;
    return list[position];
}

int ArrayList::getLength() {
    return length;
}

bool ArrayList::empty() {
    return length == 0;
}

void ArrayList::printList() {
    int i;
    for (i = 0; i < length; i++)
        printf("%d ", list[i]);
    printf("Current size: %d, current length: %d\n", listMaxSize, length);
}

ArrayList::~ArrayList() {
    if (list) delete[] list;
    list = 0;
}
//--------------------------------------------
//implementation of ArrayLists class has ended
//--------------------------------------------
//-------------------------------------
//implementation of Graph class started
//-------------------------------------

class Graph {
    int nVertices, nEdges;
    bool directed;
    ArrayList *adjList;
    //for bfs handle
    int *color;
    int *countIndegree;
    int *countDistance;
    int *parent;

public:
    Graph(bool dir = false);

    ~Graph();

    void set_nVertices(int n);

    void removeEdge(int u, int v);

    void printAdjVertices(int u);

    void printGraph();

    void bfs(int source, char mode = 'T'); //will run bfs in the graph
    void dfs(int source); //will run dfs in the graph
    void DFSUtil(int source, bool *v);

    bool addEdge(int u, int v);

    bool isEdge(int u, int v);

    bool hasCommonAdjacent(int u, int v);

    int getInDegree(int u);

    int getOutDegree(int u);

    int getDist(int u, int v);

    void time(int totalNumberOfVertices, char functionName);

    void generateRandomGraph(int totalNumberOfVertices, int edges);

    void generateRandomGraphWithoutVertices(int edges);
};

Graph::Graph(bool dir) {
    nVertices = 0;
    nEdges = 0;
    adjList = 0;
    directed = dir; //set direction of the graph
    //define other variables to be initialized
    color = 0;
    parent = 0;
    countIndegree = 0;
    countDistance = 0;
}

void Graph::set_nVertices(int n) {
    this->nVertices = n;
    if (adjList != 0) delete[] adjList; //delete previous list
    adjList = new ArrayList[nVertices];

    // for color function
//    if (color != 0) delete[] color;
//    if (parent != 0) delete[] parent;
    color = new int[nVertices];
    parent = new int[nVertices];
    if (directed) {
        if (countIndegree != 0) {
            delete[] countIndegree;
        }
        countIndegree = new int[nVertices];
        for (int i = 0; i < nVertices; i++) {
            countIndegree[i] = 0;
        }
    }
}

bool Graph::addEdge(int u, int v) {
    if (u < 0 || v < 0 || u >= nVertices || v >= nVertices)
        return false; //vertex out of range && edge already exists
    this->nEdges++;
    adjList[u].insertItem(v);
    if (!directed)
        adjList[v].insertItem(u);
    else {
        // set in_degree && out_degree
        countIndegree[v] = countIndegree[v] + 1;
    }
    return true;
}

void Graph::removeEdge(int u, int v) {
    //write this function
    if (u < 0 || v < 0 || u >= nVertices || v >= nVertices) return; //vertex out of range
    if (!directed) {
        int t = adjList[u].searchItem(v);
        if (t != NULL_VALUE) {
            this->nEdges--;
            adjList[u].removeItem(v);
            adjList[v].removeItem(u);
        }
    } else {
        int t = adjList[u].searchItem(v);
        if (t != NULL_VALUE) {
            this->nEdges--;
            adjList[u].removeItem(v);
            countIndegree[v] = countIndegree[v] - 1;
        }
    }
}

bool Graph::isEdge(int u, int v) {
    //returns true if (u,v) is an edge, otherwise should return false
    if (!directed) {
        return adjList[u].searchItem(v) != NULL_VALUE && adjList[v].searchItem(u) != NULL_VALUE;
    } else {
        return adjList[u].searchItem(v) != NULL_VALUE;
    }
}

int Graph::getInDegree(int u) {
    //returns the degree of vertex u
    if (u < 0 || u >= nVertices)
        return NULL_VALUE;
    return countIndegree[u];
}

int Graph::getOutDegree(int u) {
    if (u < 0 || u >= nVertices)
        return NULL_VALUE;
    return adjList[u].getLength();
}

bool Graph::hasCommonAdjacent(int u, int v) {
    //returns true if vertices u and v have common adjacent vertices
    if (u < 0 || v < 0 || u >= nVertices || v >= nVertices)
        return false;
    for (int i = 0; i < adjList[u].getLength(); i++) {
        if (adjList[v].searchItem(adjList[u].getItem(i)) != NULL_VALUE) {
            return true;
        }
    }
    return false;
}

void Graph::printAdjVertices(int u) {
    //prints all adjacent vertices of a vertex u
    if (u < 0 || u >= nVertices)
        return;
    adjList[u].printList();
}

void Graph::bfs(int source, char mode) {
    //complete this function
    //initialize BFS variables for all n vertices first
    if (source < 0 || source >= nVertices) return;
    color = new int[nVertices];
    countDistance = new int[nVertices];
    for (int i = 0; i < nVertices; i++) {
        color[i] = WHITE;
        countDistance[i] = INFINITY;
    }
    Queue q;
    color[source] = GREY;
    if (mode == 'N')
        cout << " Nodes : " << source << " ";
    countDistance[source] = 0;
    parent[source] = source;
    q.enqueue(source);
    while (!q.empty()) {
        int h = q.dequeue();
        if (mode == 'N')
            cout << h << " ";
        for (int i = 0; i < adjList[h].getLength(); i++) {
            int s = adjList[h].getItem(i);
            if (color[s] == WHITE) {
                color[s] = GREY;
                countDistance[s] = countDistance[h] + 1;
                parent[s] = h;
                q.enqueue(s);
            }
        }
        color[h] = BLACK;
    }
    if(mode == 'N')
        cout << endl;
}

void Graph::DFSUtil(int source, bool *visited) {
    visited[source] = true;

    for (int i = 0; i < adjList[source].getLength(); i++) {
        int s = adjList[source].getItem(i);
        if (!visited[s]) {
            DFSUtil(s, visited);
        }
    }
}

void Graph::dfs(int source) {
    if (source < 0 || source >= nVertices) return;

    bool *visited = new bool[nVertices];
    color = new int[nVertices];
    countDistance = new int[nVertices];
    for (int i = 0; i < nVertices; i++) {
        visited[i] = false;
        color[i] = WHITE;
        countDistance[i] = INFINITY;
    }
    color[source] = GREY;
    DFSUtil(source, visited);
}

int Graph::getDist(int u, int v) {
    //returns the shortest path distance from u to v
    //must call bfs using u as the source vertex, then use distance array to find the distance
    if (u < 0 || v < 0 || u >= nVertices || v >= nVertices)
        return INFINITY;
    bfs(u);
    return countDistance[v];
}

void Graph::printGraph() {
    printf("\nNumber of vertices: %d, Number of edges: %d\n", nVertices, nEdges);
    for (int i = 0; i < nVertices; i++) {
        printf("%d:", i);
        for (int j = 0; j < adjList[i].getLength(); j++) {
            printf(" %d", adjList[i].getItem(j));
        }
        printf("\n");
    }
}

void Graph::time(int totalNumberofVertices, char functionName) {
    std::chrono::time_point<std::chrono::system_clock> start, end;

    Graph g = new Graph(directed);

    if (functionName == 'B') {

//        cout << "In time" << endl;
        for (int vertices = 1000; vertices <= totalNumberofVertices; vertices *= 2) {
            g.set_nVertices(vertices);
            int edge = vertices;
            for (int edges = edge; edges <= (edge * edge - edge) / 8; edges *= 2) {
                g.generateRandomGraph(vertices, edges);
                std::uniform_int_distribution<std::mt19937::result_type> dist6(0, vertices);
                int randomSource = dist6(rng);
                auto total_time_needed = 0ULL;
                int avg_number = 10;
                for (int counter = 1; counter <= avg_number; counter++) {
                    start = std::chrono::high_resolution_clock::now();
                    g.bfs(randomSource, 'T');
                    end = std::chrono::high_resolution_clock::now();
                    total_time_needed += std::chrono::duration_cast<chrono::nanoseconds>(end - start).count();
                }
                auto one_time = total_time_needed / avg_number;

                cout << "Vertices - " << vertices << " Edges " << edges;
                cout << " Total time needed = " << one_time << endl;

            }
        }
    } else {
        for (int vertices = 1000; vertices <= totalNumberofVertices; vertices *= 2) {
            g.set_nVertices(vertices);
            int edge = vertices;
            for (int edges = edge; edges <= (edge * edge - edge) / 8; edges *= 2) {
                g.generateRandomGraph(vertices, edges);
                std::uniform_int_distribution<std::mt19937::result_type> dist6(0, vertices);
                int randomSource = dist6(rng);
                auto total_time_needed = 0ULL;
                int avg_number = 10;
                for (int counter = 1; counter <= avg_number; counter++) {
                    start = std::chrono::high_resolution_clock::now();
                    g.dfs(randomSource);
                    end = std::chrono::high_resolution_clock::now();
                    total_time_needed += std::chrono::duration_cast<chrono::nanoseconds>(end - start).count();
                }
                auto one_time = total_time_needed / avg_number;

                cout << "Vertices - " << vertices << " Edges " << edges;
                cout << " Total time needed = " << one_time << endl;

            }
        }
    }
}

void time(int totalNumberofVertices, char functionName, bool directed) {
    std::chrono::time_point<std::chrono::system_clock> start, end;

    Graph g = new Graph(directed);

    ofstream outputFile;
    ifstream inputFile;
    inputFile.open("list_result.txt");
    inputFile.close();

    outputFile.open("list_result.txt");
    outputFile << "Vertices  Edges  Times" << endl;

    if (functionName == 'B') {

//        cout << "In time" << endl;
        for (int vertices = 1000; vertices <= totalNumberofVertices; vertices *= 2) {
            g.set_nVertices(vertices);
            int edge = vertices;
            for (int edges = edge; edges <= (edge * edge - edge) / 8; edges *= 2) {
                g.generateRandomGraph(vertices, edges);
                std::uniform_int_distribution<std::mt19937::result_type> dist6(0, vertices);
                int randomSource = dist6(rng);
                auto total_time_needed = 0ULL;
                int avg_number = 10;
                for (int counter = 1; counter <= avg_number; counter++) {
                    start = std::chrono::high_resolution_clock::now();
                    g.bfs(randomSource);
                    end = std::chrono::high_resolution_clock::now();
                    total_time_needed += std::chrono::duration_cast<chrono::nanoseconds>(end - start).count();
                }
                auto one_time = total_time_needed / avg_number;

                cout << "Vertices - " << vertices << " Edges " << edges;
                cout << " Total time needed = " << one_time << endl;
                outputFile << vertices << "  " << edges << "  " << one_time << endl;
            }
        }
    } else {
//        cout << "In time" << endl;
        for (int vertices = 1000; vertices <= totalNumberofVertices; vertices *= 2) {
            g.set_nVertices(vertices);
            int edge = vertices;
            for (int edges = edge; edges <= (edge * edge - edge) / 8; edges *= 2) {
                g.generateRandomGraph(vertices, edges);
                std::uniform_int_distribution<std::mt19937::result_type> dist6(0, vertices);
                int randomSource = dist6(rng);
                auto total_time_needed = 0ULL;
                int avg_number = 10;
                for (int counter = 1; counter <= avg_number; counter++) {
                    start = std::chrono::high_resolution_clock::now();
                    g.dfs(randomSource);
                    end = std::chrono::high_resolution_clock::now();
                    total_time_needed += std::chrono::duration_cast<chrono::nanoseconds>(end - start).count();
                }
                auto one_time = total_time_needed / avg_number;

                cout << "Vertices - " << vertices << " Edges " << edges;
                cout << " Total time needed = " << one_time << endl;
                outputFile << vertices << "  " << edges << "  " << one_time << endl;
            }
        }
    }
    outputFile.close();
}

void Graph::generateRandomGraphWithoutVertices(int edges) {
    for (int j = 0; j < edges;) {
        // distribution in range [0, totalNumberOfVertices]
        std::uniform_int_distribution<std::mt19937::result_type> dist6(0, edges);

        int u = dist6(rng), v = dist6(rng);
//        cout << u << "--u || v-- " << v << " for edge & vertex test" << endl;
        if (u != v && addEdge(u, v))
            j++;
    }
}

void Graph::generateRandomGraph(int totalNumberOfVertices, int edges) {
    for (int j = 0; j < edges;) {
        // distribution in range [0, totalNumberOfVertices]
        std::uniform_int_distribution<std::mt19937::result_type> dist6(0, totalNumberOfVertices);

        int u = dist6(rng), v = dist6(rng);
//            cout << u << "--u || v-- " << v << " for edge & vertex test" << endl;
        if (u != v && addEdge(u, v))
            j++;
    }
}

Graph::~Graph() {
    //write your destructor here
    delete[] adjList;
    adjList = 0;
    delete[] countDistance;
    countDistance = 0;
    delete[] color;
    color = 0;
    delete[] countIndegree;
    countIndegree = 0;
    delete[] parent;
    parent = 0;
}

void getDirectedOrUndirected() {
    printf("Enter your choice:\n");
    printf("1. directed graph   2. undirected graph\n");
}

void menuByFunction() {
    printf("\t 0. Generate Random Graph\n\t1. Add edge\n\t");
    printf("2. Remove Edge\n\t3. isEdge\n\t4. getInDegree\n\t5. getOutDegree\n\t6.Adjacent vertices"
           "\n\t7. hasCommonAdjacent\n\t8. getDistance\n\t");
    printf("9. Print Graph\n\t10.Time\n\t11. BFS\n\t12. Exit.\n");
}

//---------------------------------------
//implementation of Graph class has ended
//---------------------------------------
// ----------- main class ---------------
int main() {
    int totalNumberOfVertices;
    int choice;
    bool dir;
    getDirectedOrUndirected();
    scanf("%d", &choice);
    while (true) {
        if (choice == 1) {
            dir = true;
            break;
        } else if (choice == 2) {
            dir = false;
            break;
        } else {
            printf("Invalid input. Continue with valid input.\n");
            getDirectedOrUndirected();
        }
        scanf("%d", &choice);
    }

    Graph g(dir);
    printf("Enter the maximum number of vertices: ");
    scanf("%d", &totalNumberOfVertices);
    g.set_nVertices(totalNumberOfVertices);

    while (true) {
        menuByFunction();
        int ch;
        scanf("%d", &ch);
        if (ch == 0) {
            cout << "Enter the number of edges" << endl;
            int edges;
            cin >> edges;
            g.generateRandomGraph(totalNumberOfVertices, edges);
        }
        if (ch == 1) {
            int u, v;
            printf("Enter first node : ");
            scanf("%d", &u);
            printf("Enter second node : ");
            scanf("%d", &v);

            g.addEdge(u, v);
        } else if (ch == 2) {
            int u, v;
            printf("Enter first node : ");
            scanf("%d", &u);
            printf("Enter second node : ");
            scanf("%d", &v);
            g.removeEdge(u, v);
        } else if (ch == 3) {
            int u, v;
            printf("Enter first node : ");
            scanf("%d", &u);
            printf("Enter second node : ");
            scanf("%d", &v);
            bool t = g.isEdge(u, v);
            if (t) printf("YES\n");
            else printf("NO\n");
        } else if (ch == 4) {
            int u;
            printf("Enter node : ");
            scanf("%d", &u);
            printf("%d \n", g.getInDegree(u));
        } else if (ch == 5) {
            int u;
            printf("Enter node : ");
            scanf("%d", &u);
            printf("%d \n", g.getOutDegree(u));

        } else if (ch == 6) {
            int u;
            printf("Enter node : ");
            scanf("%d", &u);
            g.printAdjVertices(u);
        } else if (ch == 7) {
            int u, v;
            printf("Enter first node : ");
            scanf("%d", &u);
            printf("Enter second node : ");
            scanf("%d", &v);
            bool t;
            t = g.hasCommonAdjacent(u, v);
            if (t) printf("YES\n");
            else printf("NO\n");
        } else if (ch == 8) {
            int u, v;
            printf("Enter first node : ");
            scanf("%d", &u);
            printf("Enter second node : ");
            scanf("%d", &v);
            int d = g.getDist(u, v);
            if (d != INFINITY) {
                printf("Distance is %d\n", d);
            } else {
                printf("Distance is INFINITY");
            }
        } else if (ch == 9) {
            g.printGraph();
        } else if (ch == 10) {
            cout << "Time take for \n\t\t1.BFS\n\t\t2.DFS\n";
            int input;
            cin >> input;
            if (input == 1) {
//                g.time(totalNumberOfVertices, 'B');
                time(totalNumberOfVertices, 'B', dir);
            } else {
//                g.time(totalNumberOfVertices, 'D');
                time(totalNumberOfVertices, 'D', dir);
            }
        }  else if (ch == 11) {
            int source;
            cout << "Enter source : " << endl;
            cin >> source;
            g.bfs(source, 'N');
        }else if (ch == 12) {
            break;
        }
    }
}