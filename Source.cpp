#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include <stdlib.h>
using namespace std;
const int MAP_SIZE = 20;
const int NUM_VERTICES = 400;
#include "AVL.h"
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
    Graph g(NUM_VERTICES);

    g.createGraph(map);
    int spawn = 0;
    int crystal = 0;
    int destination = 0;
    for (int i = 0; i < MAP_SIZE; i++)
        for (int j = 0; j < (MAP_SIZE * 2); j += 2)
            if (map[i][j] == '*') {
                crystal = i * MAP_SIZE + (j/2);
                break;
            }
    int x, y;
    int option,suboption;
    bool valid = false;
    do
    {
        system("cls");
        cout << "\t\t\t\t\tTHE QUEST FOR THE CRYSTAL KINGDOM\n\n";
        cout << "1. Shortest Path between any two areas of the forest\n";
        cout << "2. Shortest Path from current location to Crystal\n";
        cout << "3. Minimum Spanning Tree\n";
        cout << "0. Exit the program\n";
        cout << "\nOption : ";
        cin >> option;

        switch (option) {
        case  1:
            system("cls");
            cout << "\t\t\t\t\tTHE QUEST FOR THE CRYSTAL KINGDOM\n\n";
            valid = false;
            while (!valid) {
                cout << "Enter Starting position(x<space>y) : "; cin >> x >> y;
                spawn = x * MAP_SIZE + (y / 2);
                cout << "Enter Destination(x<space>y) : "; cin >> x >> y;
                destination = x * MAP_SIZE + (y / 2);
                if (spawn <= destination)
                    valid = true;
                else
                    cout << "Invalid coordinates! Please Try Again.\n";
            }
            system("cls");
            cout << "\t\t\t\t\tTHE QUEST FOR THE CRYSTAL KINGDOM\n\n";
            cout << "1. Dijkstra's Algorithm\n";
            cout << "2. Floyd's Algorithm\n";
            cout << "0. Back\n";
            cout << "\nOption : ";
            cin >> suboption;
            switch (suboption)
            {
                case 1:
                    system("cls");
                    cout << "\t\t\t\t\tTHE QUEST FOR THE CRYSTAL KINGDOM\n\n";
                    g.find_shortest_Dijkstras(spawn, destination, map);
                    cout << "Press Enter To Continue.";
                    cin.ignore();
                    break;
                case 2:
                    system("cls");
                    cout << "\t\t\t\t\tTHE QUEST FOR THE CRYSTAL KINGDOM\n\n";
                    g.find_shortest_Floyds(spawn, destination, map);
                    cout << "Press Enter To Continue.";
                    cin.ignore();
                    break;
                case 0:
                default:
                    break;
            }
            break;
        case 2:
            system("cls");
            cout << "\t\t\t\t\tTHE QUEST FOR THE CRYSTAL KINGDOM\n\n";
            spawn = 0;
            destination = crystal;
            system("cls");
            cout << "\t\t\t\t\tTHE QUEST FOR THE CRYSTAL KINGDOM\n\n";
            cout << "1. Dijkstra's Algorithm\n";
            cout << "2. Floyd's Algorithm\n";
            cout << "0. Back\n";
            cout << "\nOption : ";
            cin >> suboption;
            switch (suboption)
            {
            case 1:
                system("cls");
                cout << "\t\t\t\t\tTHE QUEST FOR THE CRYSTAL KINGDOM\n\n";
                g.find_shortest_Dijkstras(spawn, destination, map);
                cout << "Press Enter To Continue.";
                cin.ignore();
                break;
            case 2:
                system("cls");
                cout << "\t\t\t\t\tTHE QUEST FOR THE CRYSTAL KINGDOM\n\n";
                g.find_shortest_Floyds(spawn, destination, map);
                cout << "Press Enter To Continue.";
                cin.ignore();
                break;
            case 0:
            default:
                break;
            }
            break;
        case 3:
            system("cls");
            cout << "\t\t\t\t\tTHE QUEST FOR THE CRYSTAL KINGDOM\n\n";
            cout << "1. Prim's Algorithm\n";
            cout << "2. Kruskal's Algorithm\n";
            cout << "0. Back\n";
            cout << "\nOption : ";
            cin >> suboption;
            switch (suboption)
            {
            case 1:
                system("cls");
                cout << "\t\t\t\t\tTHE QUEST FOR THE CRYSTAL KINGDOM\n\n";
                g.create_MST_Prims();
                cout << "Press Enter To Continue.";
                cin.ignore();
                break;
            case 2:
                system("cls");
                cout << "\t\t\t\t\tTHE QUEST FOR THE CRYSTAL KINGDOM\n\n";
                g.create_MST_Kruskals();
                cout << "Press Enter To Continue.";
                cin.ignore();
                break;
            case 0:
            default:
                break;
            }
        case 0:
            exit(0);
            break;
        default:
            cout << "Invalid Input! Please Try Again.";
            break;
        }

    } while (1);
}