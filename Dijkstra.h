class Set {
    int** data;
    int size;
    int capacity;
public:
    Set(int capacity = 0) :capacity(capacity), size(0), data( new int*[capacity] ){
        for (int i = 0; i < capacity; i++)
        {
            data[i] = new int[2];
        }
    }
    int getData(int i,int j)const { return data[i][j]; }
    bool empty() { return size == 0; }
    void insert(int distance,int value) {
        if (contains(value)) {
            return;
        }
        int index = 0;
        while (index < size && data[index][0] < distance) {
            index++;
        }
        //bubble up
        for (int i = size; i > index; i--) {
            data[i][0] = data[i - 1][0];
            data[i][1] = data[i - 1][1];
        }
        //insert at correct sorted position
        data[index][0] = distance;
        data[index][1] = value;
        size++;
    }
    void remove(int element) {
        int index = -1;
        //find element
        for (int i = 0; i < size; i++) {
            if (data[i][1] == element) {
                index = i;
                break;
            }
        }
        if (index == -1)
            return;
        //move all data ahead of element one step down  
        for (int i = index; i < size - 1; i++) {
            data[i][0] = data[i + 1][0];
            data[i][1] = data[i + 1][1];
        }
        size--;
    }
    bool contains(int element) {
        int left = 0;
        int right = size - 1;

        while (left <= right) {
            int mid = (left + right) / 2;
            if (data[mid][1] == element) {
                return true;
            }
            else if (data[mid][1] < element) {
                left = mid + 1;
            }
            else {
                right = mid - 1;
            }
        }
        return false;
    }
    void print() {
        for (size_t i = 0; i < size; i++)
        {
            cout << data[i][0] << " ";
        }
    }
};
class Dijkstras {
public:
    void shortestPath(AdjacencyList& adjList, int source, int destination, string* map) {
        int* distance = new int[NUM_VERTICES];
        int* parent = new int[NUM_VERTICES];
        AVLTree inventory;
        for (int i = 0; i < NUM_VERTICES; i++)
        {
            distance[i] = INT_MAX;
            parent[i] = -1;
        }
        Set st(NUM_VERTICES);
        distance[source] = 0;
        st.insert(0, source);
        while (!st.empty()) {
            //get top node
            int nodeDistance = st.getData(0,0);
            int topNode = st.getData(0,1);
            st.remove(topNode);
            for (Node* curr = adjList.getAdjNode(topNode); curr != nullptr; curr = curr->next)
            {
                int v = curr->vertex;
                int w = curr->weight;
                if (distance[v] > nodeDistance + w) {
                    if (st.contains(v) && st.getData(0, 1) == v)
                        st.remove(v);
                    distance[v] = distance[topNode] + w;
                    parent[v] = topNode;
                    st.insert(distance[v], v);
                }
            }
        }
        int* path = new int[10];
        cout << "Shortest Path from soure to destination using Dijkstra's algo is: \n";
        int i = 0;
        string strpath="";
        for (size_t v = destination; v != -1; v = parent[v]) {
            path[i++] = v;
            int tempj = (v % MAP_SIZE) * 2;
            int tempi = v / MAP_SIZE;
            char entity = map[tempi][tempj];
            int id = rand() % 201;
            strpath += entity;
            //updating score
            if (entity == 'J')
                inventory.insert(id, 50);

            else if (entity == 'P')
                inventory.insert(id, 30);

            else if (entity == 'W')
                inventory.insert(id, 70);

            else if (entity == '&')
                inventory.insert(id, -50);

            else if (entity == '$')
                inventory.insert(id, -30);

            else if (entity == '@')
                inventory.insert(id, -70);

            strpath += ">-";
        }
        for (size_t j = strpath.length() - 3; j < strpath.length(); j--) {
            cout << strpath[j];
        }
        cout << endl;
        cout << path[--i];
        for (size_t count = i; count > 0; count--)
        {
            cout << "->" << path[--i];
        }
        cout << endl;
        int total_score = inventory.calculateScore(inventory.root);
        cout << "Total Score : " << total_score;
	}
};
