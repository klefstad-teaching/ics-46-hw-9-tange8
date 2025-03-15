#include <iostream>
#include <vector>
#include "dijkstras.h"

using namespace std;

int main() {
    Graph G;
    string filename;

    cout << "Enter the graph file name: ";
    cin >> filename;

    try {
        file_to_graph(filename, G);
    } catch (const runtime_error& e) {
        cerr << e.what() << endl;
        return 1;
    }

    int source;
    cout << "Enter the source vertex: ";
    cin >> source;

    if (source < 0 || source >= G.numVertices) {
        cerr << "Error: Invalid source vertex!" << endl;
        return 1;
    }

    vector<int> previous;
    vector<int> distances = dijkstra_shortest_path(G, source, previous);

    cout << "\nShortest distances from vertex " << source << ":" << endl;
    for (int i = 0; i < G.numVertices; i++) {
        cout << "To vertex " << i << ": ";
        if (distances[i] == INF) {
            cout << "No path" << endl;
        } else {
            cout << distances[i] << endl;
        }
    }

    int destination;
    cout << "\nEnter a destination vertex to find the shortest path: ";
    cin >> destination;

    if (destination < 0 || destination >= G.numVertices) {
        cerr << "Error: Invalid destination vertex!" << endl;
        return 1;
    }

    vector<int> path = extract_shortest_path(distances, previous, destination);
    print_path(path, distances[destination]);

    return 0;
}
