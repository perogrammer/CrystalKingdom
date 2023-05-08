#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
using namespace std;
const int MAP_SIZE = 20;
const int NUM_VERTICES = 400;
#include "Game.h"
#include "AVL.h"
int main() {
    //srand(time(NULL));
    ifstream file("map.txt");
    if (!file.is_open()) {
        cout << "Cannot open file!!";
        return 1;
    }
    string map[20],row;
    int i = 0;
    while (getline(file, row)) {
        map[i] = row;
        i++;
    }
    int source = 0;
    int destination = 116;
    Graph g(NUM_VERTICES);
    g.createGraph(map);
    //g.create_MST_Prims();
    //g.create_MST_Kruskals();
    //g.find_shortest_Dijkstras(source,destination);
    g.find_shortest_Floyds(source,destination);
    //for (auto i : map)
    //    cout << i << endl;
}