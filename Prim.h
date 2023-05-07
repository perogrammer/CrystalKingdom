class Prims {
public:
	AdjacencyList MST(AdjacencyList& adj) {
		AdjacencyList adjMST(NUM_VERTICES);
		
		int* key = new int[NUM_VERTICES];
		bool* mst = new bool[NUM_VERTICES];
		int* parent = new int[NUM_VERTICES];
		for (int i = 1; i < NUM_VERTICES; i++) {
			key[i] = INT_MAX;
			parent[i] = -1;
			mst[i] = false;
		} 
		key[0] = 0;
		parent[0] = -1;
		for (int i = 0; i < NUM_VERTICES; i++)
		{
			int min = INT_MAX;
			int u = 0;
			//finding minimum node
			for (int v = 0; v < NUM_VERTICES; v++)
			{
				if (!mst[v] && key[v] < min) {
					u = v;
					min = key[v];
				}
			}
			//mark min node as true
			mst[u] = true;
			//check adjacent nodes
			for (Node* curr = adj.getAdjNode(u); curr != nullptr; curr = curr->next)
			{
				int v = curr->vertex;
				int w = curr->weight;
				if (!mst[v] && w < key[v]) {
					parent[v] = u;
					key[v] = w;
				}
			}
		}
		for (int i = 1; i < NUM_VERTICES; i++)
		{
			adjMST.addEdge(parent[i], i, key[i]);
		}
		return adjMST;
	}
};

