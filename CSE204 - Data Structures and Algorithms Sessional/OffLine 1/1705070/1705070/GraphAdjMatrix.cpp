#include<stdio.h>
#include<stdlib.h>

#define NULL_VALUE -999999
#define INFINITY 999999
#define WHITE 1
#define GREY 2
#define BLACK 3

int nothingimp()
{
    int arr[] = {1000, 2000, 4000, 8000, 16000};
            ofstream file;
            file.open("result_matrix2.txt");
            file<<" V "<<" E "<<" Time \n";
            for(int i : arr){
                int nEdge = i, prev;
                Graph graph = new Graph(dir);
                graph.setnVertices(i);
                while(nEdge <= i*(i-1)/8){
                    graph.random_generate(nEdge - prev);
                    uniform_int_distribution<> dis(0, n-1);
                    long long total = 0;
                    for(int j = 0; j < 10; ++j){
                        int u = dis(gen);
                        auto start = high_resolution_clock::now();
                        graph.bfs(u, true);
                        auto stop = high_resolution_clock::now();
                        auto duration = duration_cast<nanoseconds>(stop - start);
                        total += duration.count();
                    }

                    file<<i<<" "<<nEdge<<" "<<total/10<<"\n";
                    prev = nEdge;
                    nEdge *= 2;
                }     
            }
            file.close();
}

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
    if (length == 0) return true;
    else return false;
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
    int *getIndegree;
    int *getOutdegree;

public:
    Graph(bool dir = false);

    ~Graph();

    void setnVertices(int n);

    void addEdge(int u, int v);

    void removeEdge(int u, int v);

    bool isEdge(int u, int v);

    int getDegree(int u, bool out);

    void printAdjVertices(int u);

    bool hasCommonAdjacent(int u, int v);

    int getDist(int u, int v);

    void printGraph();

    void bfs(int source); //will run bfs in the graph
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

void Graph::setnVertices(int n) {
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

void Graph::addEdge(int u, int v) {
    //write your code here
    if (u < 0 || u >= nVertices || v < 0 || v >= nVertices) return;
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

int Graph::getDegree(int u, bool out = true) {
    //returns the degree of vertex u
    if (u < 0 || u >= nVertices)
        return 0;
    if (!directed || out) {
        return getOutdegree[u];
    } else {
        return getIndegree[u];
    }

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

void Graph::bfs(int source) {
    //write this function
    bool *visited = new bool[nVertices];
    for (int i = 0; i < nVertices; i++) {
        visited[i] = false;
        color[i] = WHITE;
        getDistance[source] = INFINITY;
    }
    if (source < 0 || source >= nVertices) return;
    Queue q;
    visited[source] = true;
    color[source] = GREY;
    getDistance[source] = 0;
    q.enqueue(source);

    while (!q.empty()) {
        source = q.dequeue();
        for (int i = 0; i < nVertices; i++) {
            if (matrix[source][i]) {
                if (!visited[i] && color[i] == WHITE) {
                    visited[i] = true;
                    color[i] = GREY;
                    getDistance[i] = getDistance[source] + 1;
                    q.enqueue(i);
                }
            }
        }
        color[source] = BLACK;
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
}


//**********************Graph class ends here******************************


//******main function to test your code*************************
int main(void) {
    int n;
    int choice;
    bool dir;
    printf("Enter your choice:\n");
    printf("1. directed graph   2. undirected graph\n");
    scanf("%d", &choice);
    if (choice == 1)dir = true;
    else if (choice == 2)dir = false;

    Graph g(dir);
    printf("Enter number of vertices: ");
    scanf("%d", &n);
    g.setnVertices(n);

    while (1) {
        printf("\t1. Add edge \n\t");
        printf("2. Remove Edge\n\t3. isEdge\n\t4. getDegree\n\t5. Adjacent vertices"
               "\n\t6. hasCommonAdjacent\n\t7. getDistance\n\t");
        printf("8. Print Graph\n\t9. Exit.\n");

        int ch;
        scanf("%d", &ch);
        if (ch == 1) {
            int u, v;
            printf("Enter first node : ");
            scanf("%d",&u);
            printf("Enter second node : ");
            scanf("%d", &v);

            g.addEdge(u, v);
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
            printf("\t1: In Degree\n\t2: Out Degree");
            int t;
            scanf("%d", &t);
            if (t == 2)
                printf("%d \n", g.getDegree(u));
            else if (t == 1)
                printf("%d \n", g.getDegree(u, false));
        } else if (ch == 5) {
            int u;
            printf("Enter node : ");
            scanf("%d", &u);
            g.printAdjVertices(u);
        } else if (ch == 6) {
            int u, v;
            printf("Enter first node : ");
            scanf("%d",&u);
            printf("Enter second node : ");
            scanf("%d", &v);
            bool t;
            t = g.hasCommonAdjacent(u, v);
            if (t) printf("YES\n");
            else printf("NO\n");
        } else if (ch == 7) {
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
        } else if (ch == 8) {
            g.printGraph();
        } else if (ch == 9) {
            break;
        }
    }

}
