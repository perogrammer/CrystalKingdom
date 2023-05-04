#include <iostream>
#include <fstream>
#include <string>
using namespace std;
#include "AVL.h"
#include "Dijkstra.h"
#include "FLoyd.h"
#include "Prim.h"
#include "Kruskal.h"
#include "Game.h"
int main() {
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
    for (auto i : map)
        cout << i << endl;



    cout << "asdasda";


}