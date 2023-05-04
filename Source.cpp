#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
using namespace std;
const int MAP_SIZE = 20;
#include "AVL.h"
#include "Dijkstra.h"
#include "FLoyd.h"
#include "Prim.h"
#include "Kruskal.h"
#include "Game.h"
int main() {
    srand(time(NULL));
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
    createAdjacencyMatrix(map);
    //for (auto i : map)
    //    cout << i << endl;
}