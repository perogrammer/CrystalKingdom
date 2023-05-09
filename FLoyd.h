class Floyds {
public:
	void shortestPath(AdjacencyList& adjList, int source,int destination, string* map) {
		
		int** distanceMatrix = new int*[NUM_VERTICES];
		int** parent = new int*[NUM_VERTICES];


		for (size_t i = 0; i < NUM_VERTICES; i++) {
			distanceMatrix[i] = new int[NUM_VERTICES];
			parent[i] = new int[NUM_VERTICES];
			for (size_t j = 0; j < NUM_VERTICES; j++) {
				distanceMatrix[i][j] = INT_MAX;
				parent[i][j] = -1;
			}
		}
		for (size_t i = 0; i < NUM_VERTICES; i++)
		{
			for (Node* curr = adjList.getAdjNode(i); curr != nullptr; curr = curr->next) {
				int j = curr->vertex;
				int w = curr->weight;
				if (i == j)
					distanceMatrix[i][j] = 0;
				else {
					distanceMatrix[i][j] = w;
					parent[i][j] = i;
				}
			}
		}

		//find and store shortest path
		for (size_t k = 0; k < NUM_VERTICES; k++)
			for (size_t i = 0; i < NUM_VERTICES; i++)
				for (size_t j = 0; j < NUM_VERTICES; j++)
					if ((distanceMatrix[i][k] != INT_MAX && distanceMatrix[k][j] != INT_MAX) && (distanceMatrix[i][j] > distanceMatrix[i][k] + distanceMatrix[k][j])) {
						distanceMatrix[i][j] = distanceMatrix[i][k] + distanceMatrix[k][j];
						parent[i][j] = parent[k][j];
					}
		cout << "Shortest path from " << source << " to " << destination << ": ";

		string strpath = "";
		
		int* path = new int[10];
		int curr = destination;
		int i = 0;
		while (curr != source) {
			path[i++] = curr;
			int tempi = curr / MAP_SIZE;
			int tempj = (curr % MAP_SIZE) * 2;
			strpath += map[tempi][tempj];
			strpath += ">-";
			curr = parent[source][curr];
		}
		int tempi = source / MAP_SIZE;
		int tempj = (source % MAP_SIZE) * 2;
		strpath += map[tempi][tempj];
		strpath += ">-";
		for (size_t j = strpath.length()-3 ; j < strpath.length(); j--) {
			cout << strpath[j];
		}
		cout << endl;
		cout << source;
		for (size_t count = i; count > 0; count--)
		{
			cout << "->" << path[--i];
		}
	}
};
