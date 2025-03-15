#include "dijkstras.h"
#include <algorithm>

using namespace std;

//find shortest path
vector<int> dijkstra_shortest_path(const Graph& G, int source, vector<int>& previous) {
    int  vertices = G.numVertices;
    vector<int> distances(vertices, INF);
    previous.assign(vertices, -1);

    //greedy selection queue
    //min-heap priority queue to select the node with the shortest known distance
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq;
    distances[source] = 0;
    pq.push({0, source});

    while (!pq.empty()) {
        int dist = pq.top().first;
        int u = pq.top().second;
        pq.pop(); //extract and remove the node with smallest known distance

        if (dist > distances[u]) continue; //skip if shorter path was alr found

        for (const Edge& edge : G[u]) {
            int v = edge.dst;
            int weight = edge.weight; //update neighboring nodes

            if (distances[u] + weight < distances[v]) { //if a new shorter path was found
                distances[v] = distances[u] + weight;
                previous[v] = u;
                pq.push({distances[v], v});
            }
        }
    }
    return distances;
}

//reutn the shortest path from a prev array 
vector<int> extract_shortest_path(const vector<int>& distances, const vector<int>& previous, int destination) {
    vector<int> path;
    if (distances[destination] == INF) return path;  //no path found

    for (int v = destination; v != -1; v = previous[v]) {
        path.push_back(v); //backtrack from dest to source then append each prev node to the path
    }
    reverse(path.begin(), path.end()); //make sure to reverse
    return path;
}

void print_path(const vector<int>& path, int total) {
    if (path.empty()) {
        cout << "No path found." << endl;
        return;
    }

    for (size_t i = 0; i < path.size(); ++i) {
        cout << path[i];
        cout << endl;
    }
    cout << "Total cost is " << total << endl;
}
