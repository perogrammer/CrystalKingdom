class AdjacencyList {
	struct Node {
		int vertex;
		int weight;
		Node* next;
		Node(int v, int w, Node* n = nullptr) : vertex(v), weight(w), next(n) {}
	};
	Node** adjList;
	int numVertices;
public:
	AdjacencyList(int _numVertices) :numVertices(_numVertices), adjList(new Node* [_numVertices]) {
		for (int i = 0; i < numVertices; i++)
			adjList[i] = nullptr;
	}
	void addEdge(int u, int v, int w = 1) {
		adjList[u] = new Node(v, w, adjList[u]);
	}
	void print() const {
		for (int i = 0; i < numVertices; i++)
		{
			cout << i << " : ";
			for (Node* curr = adjList[i]; curr != nullptr; curr=curr->next)
			{
				cout << '(' << curr->vertex << ',' << curr->weight << ")->";
			}
			cout << "NULL\n";
		}
	}
};
int getLinearIndex(int i,int j) {
	return i * MAP_SIZE + j;
}
void createAdjacencyMatrix(string* map) {
	int adj[MAP_SIZE][MAP_SIZE]{0};
	const int NUM_VERTICES = MAP_SIZE * MAP_SIZE;
	AdjacencyList list(NUM_VERTICES);
	for (int i = 0; i < MAP_SIZE; i++) {
		for (int j = 0; j < (MAP_SIZE * 2) - 2; j += 2) {
			int linearIndex = getLinearIndex(i, j/2);
			//forwards
			if (map[i][j + 2] == '#')
				list.addEdge(linearIndex, linearIndex + 1, 100);
			else
				list.addEdge(linearIndex, linearIndex + 1);
			//backwards
			if (j != 0) {
				if (map[i][j - 2] == '#')
					list.addEdge(linearIndex, linearIndex - 1, 100);
				else
					list.addEdge(linearIndex, linearIndex - 1);
			}
			//upwards
			if (linearIndex > MAP_SIZE - 1) {
				if (map[i - 1][j] == '#')
					list.addEdge(linearIndex, linearIndex - MAP_SIZE, 100);
				else
					list.addEdge(linearIndex, linearIndex - MAP_SIZE);
			}
			//downwards
			if (linearIndex < (MAP_SIZE) * (MAP_SIZE - 1) - 1) {
				if (map[i + 1][j] == '#')
					list.addEdge(linearIndex, linearIndex + MAP_SIZE, 100);
				else
					list.addEdge(linearIndex, linearIndex + MAP_SIZE);
			}
		}
	}
	list.print();
}
