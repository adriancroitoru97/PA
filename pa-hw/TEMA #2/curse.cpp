#include <bits/stdc++.h>

using namespace std;

#define NMAX 10001

/**
 * @brief Depth-first search from 'node',
 *        used to determine the topological sort.
 * 
 * @param node the source node
 * @param adj adjacency list
 * @param visited visited nodes
 * @param topsort vector in which the topological sort is created
 */
void dfs(int node, vector<int> adj[],
         vector<int>& visited, vector<int>& topsort) {
    visited[node] = 1;

    for (auto& neigh : adj[node]) {
        if (!visited[neigh]) {
            dfs(neigh, adj, visited, topsort);
        }
    }

    topsort.push_back(node);
}

int main() {
    ifstream fin("curse.in");
    ofstream fout("curse.out");

    // adjacency list used to represent the relations between
    // cars. adj[x] - all cars slower than `x`.
    vector<int> adj[NMAX];

    int N, M, A;
    fin >> N >> M >> A;

    vector<vector<int>> trainings(A, vector<int>(N));
    for (int i = 0; i < A; i++) {
        for (int j = 0; j < N; j++) {
            fin >> trainings[i][j];
        }
    }

    // go thourgh the trainings and add all the relations between
    // cars in the adjacency list. Those will be used for the topological
    // sort in order to find out the ordered cars
    for (int i = 0; i < A - 1; i++) {
        for (int j = 0; j < N; j++) {
            if (trainings[i][j] != trainings[i + 1][j]) {
                adj[trainings[i][j]].push_back(trainings[i + 1][j]);
                break;
            }
        }
    }

    // topological sort algorithm used for determining sorted cars
    vector<int> topsort;
    vector<int> visited(M + 1, 0);
    for (int car = 1; car <= M; car++) {
        if (!visited[car]) {
            dfs(car, adj, visited, topsort);
        }
    }
    reverse(topsort.begin(), topsort.end());

    // print the descendingly sorted cars
    for (unsigned int i = 0; i < topsort.size(); i++) {
        fout << topsort[i] << " ";
    }

    return 0;
}
