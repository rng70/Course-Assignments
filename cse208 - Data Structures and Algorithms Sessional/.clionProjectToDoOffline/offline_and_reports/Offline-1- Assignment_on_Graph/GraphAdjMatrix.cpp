#include<bits/stdc++.h>

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
    rear = (rear + 1) % queueMaxSize;  // circular queue implementation
    length--;
    return item;
}

Queue::~Queue() {
    if (data) delete[] data; //deallocate memory
    data = 0; //set to NULL
}

//****************Queue class ends here************************


//******************Graph class starts here**************************
class Graph {
    int nVertices, nEdges;
    bool directed;
    int **matrix; //adjacency matrix to store the graph
    //define other variables required for bfs such as color, parent, and dist
    //you must use pointers and dynamic allocation
    int *getDistance;
    int *color;
    int *parent;
    int *getIndegree;
    int *getOutdegree;

public:
    Graph(bool dir = false);

    ~Graph();

    void set_nVertices(int n);
    bool addEdge(int u, int v);
    void removeEdge(int u, int v);
    bool isEdge(int u, int v);
    int getInDegree(int u);
    int getOutDegree(int u);
    void printAdjVertices(int u);
    bool hasCommonAdjacent(int u, int v);
    int getDist(int u, int v);
    void printGraph();
    void bfs(int source, char mode='T'); //will run bfs in the graph
    void dfs(int source, char mode = 'T');
    void dfsUtil(int source, char mode);
    void time(int totalNumberOfVertices, char functionName);
    void generateRandomGraph(int totalNumberOfVertices, int edges);

    void generateRandomGraphWithoutVertices(int edges);
};


Graph::Graph(bool dir) {
    nVertices = 0;
    nEdges = 0;
    matrix = 0;
    directed = dir; //set direction of the graph
    //define other variables to be initialized
    getDistance = 0;
    color = 0;
    getIndegree = 0;
    getOutdegree = 0;
}

void Graph::set_nVertices(int n) {
    this->nVertices = n;

    delete[] getOutdegree;
    getOutdegree = new int[nVertices];
    if (directed) {
        delete[] getIndegree;
        getIndegree = new int[nVertices];
        for (int i = 0; i < nVertices; i++) {
            getIndegree[i] = 0;
        }
    }
    for (int i = 0; i < nVertices; i++) {
        getOutdegree[i] = 0;
    }

    //allocate space for the matrix
    matrix = new int *[nVertices];
    for (int i = 0; i < nVertices; i++) {
        matrix[i] = new int[nVertices];
        for (int j = 0; j < nVertices; j++)
            matrix[i][j] = 0; //initialize the matrix cells to 0
    }

}

bool Graph::addEdge(int u, int v) {
    //write your code here
    if (u < 0 || u >= nVertices || v < 0 || v >= nVertices || isEdge(u,v)) return false;
    if(matrix[u][v]==0){
        this->nEdges++;
        matrix[u][v] = 1;
        if (!directed) {
            matrix[v][u] = 1;
            getOutdegree[u] += 1;
            getOutdegree[v] += 1;
        } else {
            getIndegree[v] += 1;
            getOutdegree[u] += 1;
        }
    }
    return true;
}

void Graph::removeEdge(int u, int v) {
    //write this function
    if (u < 0 || u >= nVertices || v < 0 || v >= nVertices) return;

    if (!directed) {
        matrix[u][v] = 0;
        if (matrix[v][u] != 0) {
            this->nEdges--;
            matrix[v][u] = 0;
            getOutdegree[v] -= 1;
            getOutdegree[u] -= 1;
        }
    } else {
        if (matrix[u][v] == 1) {
            this->nEdges--;
            matrix[u][v] = 0;
            getOutdegree[u] -= 1;
            getIndegree[v] -= 1;
            nEdges--;
        }
    }
}

bool Graph::isEdge(int u, int v) {
    //returns true if (u,v) is an edge, otherwise should return false
    if (u < 0 || u >= nVertices || v < 0 || v >= nVertices) return false;
    if (!directed) {
        return matrix[u][v] && matrix[v][u];
    } else {
        return matrix[u][v] == 1;
    }
}

int Graph::getInDegree(int u) {
    //returns the degree of vertex u
    if (u < 0 || u >= nVertices)
        return 0;
    return getIndegree[u];
}
int Graph::getOutDegree(int u) {
    //returns the degree of vertex u
    if (u < 0 || u >= nVertices)
        return 0;
    return getOutdegree[u];
}

void Graph::printAdjVertices(int u) {
    //prints all adjacent vertices of a vertex u
    if (u < 0 || u >= nVertices)
        return;
    for (int i = 0; i < nVertices; i++) {
        if (matrix[u][i]) {
            printf("%d ", i);
        }
    }
    printf("\n");
}

bool Graph::hasCommonAdjacent(int u, int v) {
    //returns true if vertices u and v have common adjacent vertices
    if (u < 0 || v < 0 || u >= nVertices || v >= nVertices)
        return false;

    for (int i = 0; i < nVertices; i++) {
        if (matrix[u][i] == 1 && matrix[v][i] == 1) {
            return true;
        }
    }
    return false;
}

void Graph::bfs(int source, char mode) {
    //write this function
    color = new int[nVertices];
    getDistance = new int[nVertices];
    parent = new int[nVertices];

    for (int i = 0; i < nVertices; i++) {
        color[i] = WHITE;
        getDistance[source] = INFINITY;
    }
    if (source < 0 || source >= nVertices) return;
    Queue q;
    color[source] = GREY;
    parent[source] = source;
    getDistance[source] = 0;
    q.enqueue(source);
    if(mode == 'N')
        cout << " Nodes : ";

    while (!q.empty()) {
        source = q.dequeue();
        if(mode == 'N')
            cout << source << " ";
        for (int i = 0; i < nVertices; i++) {
            if (matrix[source][i]) {
                if (color[i] == WHITE) {
                    color[i] = GREY;
                    parent[i] = source;
                    getDistance[i] = getDistance[source] + 1;
                    q.enqueue(i);
                }
            }
        }
        color[source] = BLACK;
    }
    if(mode == 'N')
        cout << endl;
}
void Graph::dfsUtil(int source, char mode) {
    if (mode == 'N')
        cout << source << " " ;
    color[source] = GREY;
    for (int i=0;i<nVertices;i++)
    {
        if(matrix[source][i] && color[i] == WHITE)
        {
            parent[i] = source;
            dfsUtil(i, mode);
        }
    }
    color[source] = BLACK;
}

void Graph::dfs(int source, char mode)
{
    color = new int[nVertices];
    parent = new int[nVertices];
    for(int i=0;i<nVertices;i++)
    {
        color[i] = WHITE;
    }
    parent[source] = -1;
    dfsUtil(source, mode);
    if (mode == 'N')
        cout << endl;

}
void Graph::time(int totalNumberofVertices, char functionName) {
    std::chrono::time_point<std::chrono::system_clock> start, end;

    Graph g = new Graph(this->directed);

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

            }
        }
    }
}
void time(int totalNumberofVertices, char functionName, bool directed) {
    std::chrono::time_point<std::chrono::system_clock> start, end;

    Graph g = new Graph(directed);
    ofstream outputFile;
    outputFile.open("matrix_result.txt");
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
int Graph::getDist(int u, int v) {
    //returns the shortest path distance from u to v
    //must call bfs using u as the source vertex, then use distance array to find the distance
    if(u<0 || v<0 || u>=nVertices || v>=nVertices)
        return INFINITY;
    bfs(u);
    return getDistance[v];
}


void Graph::printGraph() {
    printf("\nNumber of vertices: %d, Number of edges: %d\n", nVertices, nEdges);
    for (int i = 0; i < nVertices; i++) {
        printf("%d:", i);
        for (int j = 0; j < nVertices; j++) {
            if (matrix[i][j] == 1)
                printf(" %d", j);
        }
        printf("\n");
    }
}

Graph::~Graph() {
    //write your destructor here
    delete[] matrix;
    matrix = nullptr;
    delete[] getDistance;
    getDistance = 0;
    delete[] color;
    color = 0;
    delete[] getIndegree;
    getIndegree = 0;
    delete[] getOutdegree;
    getOutdegree = 0;
    delete[] parent;
    parent = 0;
}


//**********************Graph class ends here******************************

void getDirectedOrUndirected() {
    printf("Enter your choice:\n");
    printf("1. directed graph   2. undirected graph\n");
}

void menuByFunction()
{
    printf("\t 0. Generate Random Graph\n\t1. Add edge\n\t2. Remove Edge\n\t3. isEdge\n\t4. getInDegree\n\t"
           "5. getOutDegree\n\t6.Adjacent vertices\n\t7. hasCommonAdjacent\n\t8. getDistance\n\t");
    printf("9. Print Graph\n\t10. Time Analysis\n\t11. BFS\n\t12. Exit.\n");
}

//******main function to test your code*************************
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
    printf("Enter maximum number of vertices: ");
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
            scanf("%d",&u);
            printf("Enter second node : ");
            scanf("%d", &v);

            bool val = g.addEdge(u, v);
            if(val)
                printf("Adding successful\n");
            else
                printf("Adding unsuccessful\n");
        } else if (ch == 2) {
            int u, v;
            printf("Enter first node : ");
            scanf("%d",&u);
            printf("Enter second node : ");
            scanf("%d", &v);
            g.removeEdge(u, v);
        } else if (ch == 3) {
            int u, v;
            printf("Enter first node : ");
            scanf("%d",&u);
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
        }
        else if (ch == 5) {
            int u;
            printf("Enter node : ");
            scanf("%d", &u);
            printf("%d \n", g.getOutDegree(u));
        }else if (ch == 6) {
            int u;
            printf("Enter node : ");
            scanf("%d", &u);
            g.printAdjVertices(u);
        } else if (ch == 7) {
            int u, v;
            printf("Enter first node : ");
            scanf("%d",&u);
            printf("Enter second node : ");
            scanf("%d", &v);
            bool t;
            t = g.hasCommonAdjacent(u, v);
            if (t) printf("YES\n");
            else printf("NO\n");
        } else if (ch == 8) {
            int u, v;
            printf("Enter first node : ");
            scanf("%d",&u);
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
        } else if(ch == 10){
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
        }else if(ch == 11){
            int source;
            cout << "Enter source : " << endl;
            cin >> source;
            g.bfs(source, 'N');
        }else if (ch == 12) {
            break;
        }
    }

}


