class Kruskals {
    int edges[NUM_VERTICES][3];
    int numEdges;

public:
    int findParent(int node, int* parent) {
        for (int i = 0; i < NUM_VERTICES; i++) {
            if (parent[i] == node) {
                return parent[i];
            }
        }
        return -1;
    }

    void merge(int u, int v, int* parent,int* rank) {
        int rootU = findParent(u, parent);
        int rootV = findParent(v, parent);
        parent[rootU] = rootV;
        if (rank[u] < rank[v])
            parent[u] = v;
        else if (rank[v] < rank[u])
            parent[v] = u;
        else {
            parent[v] = u;
            rank[u]++;
        }
    }

    void bubbleSort(int arr[][3], int n) {
        for (int i = 0; i < n - 1; i++) 
            for (int j = 0; j < n - i - 1; j++) 
                if (arr[j][2] > arr[j + 1][2]) 
                    swap(arr[j], arr[j + 1]); 
    }
    AdjacencyList MST(AdjacencyList& adj) {
        numEdges = 0;
        int* parent = new int[NUM_VERTICES];
        int* rank = new int[NUM_VERTICES];
        
        for (int i = 0; i < NUM_VERTICES; i++) {
            parent[i] = i;
            rank[i] = 0;           
        }
        for (int u = 0; u < NUM_VERTICES; u++) {
            for (Node* curr = adj.getAdjNode(u); curr != nullptr; curr = curr->next, numEdges++) {
                int v = curr->vertex;
                int w = curr->weight;
                edges[numEdges][0] = u;
                edges[numEdges][1] = v;
                edges[numEdges][2] = w;
            }
        }
        bubbleSort(edges, numEdges);
        AdjacencyList adjMST(NUM_VERTICES);
        int u1 = findParent(MAP_SIZE, parent); 
        int v1 = findParent(MAP_SIZE + 1,  parent);
        adjMST.addEdge(u1, v1);
        adjMST.addEdge(v1, u1);
        for (int i = 0; i < numEdges; i++) {
            int u = edges[i][0];
            int v = edges[i][1];
            int w = edges[i][2];
            if (findParent(u, parent) != findParent(v, parent)) {
                adjMST.addEdge(u, v, w);
                merge(u, v, parent, rank);
            }
        }
        cout << "No of Edges: " << numEdges << endl;
        cout << "No of Vertices: " << NUM_VERTICES << endl;

        return adjMST;
    }
};
