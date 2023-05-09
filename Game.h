struct Node {
	int vertex;
	int weight;
	Node* next;
	Node(int v, int w, Node* n = nullptr) : vertex(v), weight(w), next(n) {}
};

class AdjacencyList {
	
	Node** adjList;
	int numVertices;
public:
	int getLinearIndex(int i, int j) {
		return i * MAP_SIZE + j;
	}
	AdjacencyList(int _numVertices) :numVertices(_numVertices), adjList(new Node* [_numVertices]) {
		for (int i = 0; i < numVertices; i++)
			adjList[i] = nullptr;
	}
	Node* getAdjNode(int u) {
		return adjList[u];
	}
	void createAdjacencyList(string*& map) {
		int adj[MAP_SIZE][MAP_SIZE]{ 0 };
		bool isObstacle = false;
		for (int i = 0; i < MAP_SIZE; i++) {
			for (int j = 0; j < (MAP_SIZE * 2); j += 2) {
				int linearIndex = getLinearIndex(i, j / 2);
				
				if (map[i][j] == '#')
					isObstacle = true;
				if (j < 2*(MAP_SIZE - 1)) {
					//forwards
					if (map[i][j + 2] == '#' || isObstacle)
						addEdge(linearIndex, linearIndex + 1, 100);
					else
						addEdge(linearIndex, linearIndex + 1);
				}
				//backwards
				if (j > 0) {
					if (map[i][j - 2] == '#' || isObstacle)
						addEdge(linearIndex, linearIndex - 1, 100);
					else
						addEdge(linearIndex, linearIndex - 1);
				}
				//upwards
				if (linearIndex > MAP_SIZE - 1) {
					if (map[i - 1][j] == '#' || isObstacle)
						addEdge(linearIndex, linearIndex - MAP_SIZE, 100);
					else
						addEdge(linearIndex, linearIndex - MAP_SIZE);
				}
				//downwards
				if (linearIndex < (MAP_SIZE) * (MAP_SIZE - 1) - 1) {
					if (map[i + 1][j] == '#' || isObstacle)
						addEdge(linearIndex, linearIndex + MAP_SIZE, 100);
					else
						addEdge(linearIndex, linearIndex + MAP_SIZE);
				}
				isObstacle = false;
			}
		}
	}
	void addEdge(int u, int v, int w = 1) {
		adjList[u] = new Node(v, w, adjList[u]);
	}
	void print() const {
		int numEdges = 0;
		for (int i = 0; i < numVertices; i++)
		{
			cout << i << " : ";
			for (Node* curr = adjList[i]; curr != nullptr; curr = curr->next, numEdges++)
			{
				cout << '(' << curr->vertex << ',' << curr->weight << ")->";
			}
			cout <<"N"<< endl;
		}
		cout << "number of edges in spanning tree = " << numEdges;
	}
	//this function no works so no judge 
	void printTree() {
		char** grid = new char* [MAP_SIZE * 2];
		for (int i = 0; i < MAP_SIZE*2; i++) {
			grid[i] = new char[MAP_SIZE*2];
			for (int j = 0; j < MAP_SIZE*2; j++) {
				grid[i][j] = ' ';
			}
		}
		for (int i = 0; i < MAP_SIZE*2; i+=2) {
			for (int j = 0; j < (MAP_SIZE * 2); j +=2) {
					grid[i][j]='*';
				int linearIndex = getLinearIndex(i, j / 2);
				for (Node* curr = adjList[i]; curr != nullptr; curr = curr->next)
				{
					//forwards
					if (j < 2 * (MAP_SIZE - 1)) {
						if (curr->vertex == linearIndex+1)
							grid[i][j+1]='-';
					}
					//backwards
					if (j > 0) {
						if (curr->vertex == linearIndex-1)
							grid[i][j - 1] = '-';
					}
					//upwards
					if (linearIndex > MAP_SIZE - 1) {
						if (curr->vertex == getLinearIndex((i-1)/2,j))
							grid[i-1][j] = '|';
					}
					//downwards
					if (linearIndex < (MAP_SIZE) * (MAP_SIZE - 1) - 1) {
						if (curr->vertex == getLinearIndex((i + 1)/2, j))
							grid[i+1][j] = '|';
					}
				}
			}
		}
		for (int i = 0; i < MAP_SIZE*2; i++) {
			for (int j = 0; j < (MAP_SIZE * 2); j ++) {
				cout << grid[i][j];
			}
			cout << endl;
		}
	}
};
#include "Dijkstra.h"
#include "FLoyd.h"
#include "Prim.h"
#include "Kruskal.h"
class Graph : public Prims, Dijkstras, Kruskals, Floyds {
	AdjacencyList list;
	AdjacencyList MST;
public:
	Graph(int numVertices) :list(numVertices),MST(0) {}
	void createGraph(string* map) {
		list.createAdjacencyList(map);
		//uncomment to see adj List of whole map
		//list.print();
	}
	void create_MST_Prims() {
		MST = Prims::MST(list);
		MST.print();
	}
	void create_MST_Kruskals() {
		MST = Kruskals::MST(list);
		MST.print();
	}
	void find_shortest_Dijkstras(int source,int destination,string* map) {
		Dijkstras::shortestPath(list, source, destination, map);
	}
	void find_shortest_Floyds(int source, int destination, string* map) {
		Floyds::shortestPath(list, source, destination, map);
	}
};
