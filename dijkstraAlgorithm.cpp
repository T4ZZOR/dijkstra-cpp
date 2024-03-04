// created by Michal Czerwinski - T4ZZOR

#include <iostream>
#include <vector>
#include <queue>
using namespace std;

typedef pair<int, int> npair;

// create node 
struct node {
    int connected;
    int distance;
};

// create base vector - empty vector with main nodes, no connections and inf weights 
vector<vector<node>> createBaseVector(int vert) {
    vector<vector<node>> shortestPathsTemp(vert);
    int inf = 1e9;

    shortestPathsTemp[0].push_back({ 0, 0 });
    for (int i = 1; i < vert; i++) {
        shortestPathsTemp[i].push_back({ NULL, inf });
    }

    return shortestPathsTemp;
}

// print visualise nodes and shortest path to another node
void printShortestPathsConnections(vector<vector<node>>& shortestPaths) {
    cout << endl;
    cout << "====SHORTEST-PATHS====" << endl;
    for (int i = 0; i < shortestPaths.size(); i++) {
        cout << i << "->" << shortestPaths[i][0].connected << " weight:" << shortestPaths[i][0].distance << endl;
    }
    cout << "======================" << endl;
}

// find and print path from start to destination
void findPath(vector<vector<node>>& shortestPaths, int start, int dest) {
    vector<int> path;
    int currentNode = dest;

    // create path vector
    for (int i = 0; i < shortestPaths.size(); i++) {
        int neighborNode = shortestPaths[currentNode][0].connected;
        path.insert(path.begin(), currentNode);

        if (currentNode == start) {
            break;
        }

        currentNode = neighborNode;
    }

    // print all path from start to destination
    cout << "path from: [" << start << "] to: [" << dest << "] = ";
    for (auto node : path) {
        cout << node << " ";
    }
    cout << endl;
}

vector<vector<node>> dijkstraAlgorithm(vector<vector<node>>& graph, int vert) {
    vector<vector<node>> shortestPaths = createBaseVector(vert);

    // inicialize priority queue for check distances between nodes
    priority_queue<npair, vector<npair>, greater<npair>> pq;
    pq.push({ 0, 0 }); // start, cost

    // main loop to check all shortest paths
    while (!pq.empty()) {
        // inicialize two current checked nodes
        int currentNode = pq.top().first;
        int currentDistance = pq.top().second;
        pq.pop();

        // else update the distance
        for (const node& neighbor : graph[currentNode]) {
            int newDistance = currentDistance + neighbor.distance;

            // check the new distance with neighbor
            if (newDistance < shortestPaths[neighbor.connected][0].distance) {
                shortestPaths[neighbor.connected][0] = { currentNode, newDistance };
                pq.push({ neighbor.connected, newDistance });
            }
        }
    }
    return shortestPaths;
}

int main() {
    // inicjalize graph of nodes
    int verticles = 6;
    vector<vector<node>> graph(verticles);

    // add sample data
    graph[0].push_back({ 1, 2 });
    graph[0].push_back({ 3, 8 });
    graph[1].push_back({ 4, 6 });
    graph[1].push_back({ 3, 5 });
    graph[3].push_back({ 4, 3 });
    graph[3].push_back({ 5, 2 });
    graph[4].push_back({ 2, 9 });
    graph[4].push_back({ 5, 1 });
    graph[5].push_back({ 2, 3 });

    // create vector with the shortest paths
    vector<vector<node>> shortestPaths = dijkstraAlgorithm(graph, verticles);

    // find shortest path [start] to [dest]
    findPath(shortestPaths, 0, 2);
    findPath(shortestPaths, 0, 4);

    printShortestPathsConnections(shortestPaths);

    return 0;
};
