#include <bits/stdc++.h>

using namespace std;

#define NMAX 100001
#define INF (1LL << 60)

/**
 * @brief Computes the number of equals elements at the beginning of
 *        a vector.
 *        For instance, for v = [1 1 1 2 1 3 1], the function should return 3,
 *        as there are 3 equal elements at the beginning of the vector.
 * 
 * @param v the vector
 * @return int - the number of equal elements at the beginning.
 */
int howManyEquals(vector <long long> v) {
    int nr = 1;
    int len = v.size();

    for (int i = 0; i < len - 1; i++) {
        if (v[i] == v[i + 1]) {
            nr++;
        } else {
            break;
        }
    }

    return nr;
}

/**
 * @brief Comparator used for de Dijkstra's priority queue.
 * 
 */
struct myComp {
    constexpr bool operator()(
        pair<int, long long> const& a,
        pair<int, long long> const& b)
        const noexcept {
        return a.second > b.second;
    }
};

/**
 * @brief Structure containing the Dijkstra's Algorithm result.
 *        Contains a distances and a parents vectors.
 * 
 */
struct DijkstraResult {
    vector<long long> d;
    vector<int> p;

    DijkstraResult(const vector<long long>& d, const vector<int>& p)
        : d(d)
        , p(p) { }
};

/**
 * @brief Computes shortest paths from source to all other cities.
 *        It ignores the paths through barbarian cities.
 * 
 * @param n number of cities
 * @param source source city
 * @param adj the adjacency list of the cities
 * @param B number of barbarian cities
 * @param b the barbarian cities
 * @return DijkstraResult 
 */
DijkstraResult dijkstra(int n, int source, vector<pair<int, int>> adj[],
                        int B, int b[]) {
    vector<long long> d(n + 1, INF);
    vector<int> p(n + 1, 0);
    vector<int> visited(n + 1, 0);

    priority_queue
        <pair<int, long long>, vector<pair<int, long long>>, myComp> pq;
    d[source] = 0;
    p[source] = 0;
    pq.push(make_pair(source, d[source]));

    while (!pq.empty()) {
        pair<int, int> pq_min = pq.top();
        int node = pq_min.first;
        pq.pop();

        if (visited[node]) {
            continue;
        }

        // if the city is barbarian, we cannot find roads through it
        if (binary_search(b, b + B, node)) {
            continue;
        }

        for (pair<int, int> neigh : adj[node]) {
            if (d[node] + neigh.second < d[neigh.first]) {
                d[neigh.first] = d[node] + neigh.second;
                p[neigh.first] = node;
                pq.push(make_pair(neigh.first, d[neigh.first]));
            }
        }

        visited[node] = 1;
    }

    for (int i = 1; i <= n; i++) {
        if (d[i] == INF)
            d[i] = -1;
    }

    return {d, p};
}

int main() {
    ifstream fin("fortificatii.in");
    ofstream fout("fortificatii.out");

    int N, M, K, B, b[100001];
    // adj[node] = adjacency list of node 'node'
    // (neigh, w) pair = edge from 'node' to 'neigh' of cost 'w'
    vector<pair<int, int>> adj[NMAX];

    fin >> N >> M >> K;
    fin >> B;
    for (int i = 0; i < B; i++) {
        fin >> b[i];
    }

    // as there will be many queries to find out if a city is barbarian,
    // the barbarian cities array is initially sorted and the queries will be
    // made using STL's binary search function, for improved efficiency
    sort(b, b + B);

    for (int i = 0; i < M; i++) {
        int xi, yi, ti;
        fin >> xi >> yi >> ti;
        adj[xi].push_back(make_pair(yi, ti));
        adj[yi].push_back(make_pair(xi, ti));
    }

    // computes shortest path from capital to other cities,
    // ignoring paths through barbarian cities
    DijkstraResult res = dijkstra(N, 1, adj, B, b);

    // creating a distances vector, containing all paths distances
    // from source to barbarian cities, sorted in ascending order
    vector<long long> distances;
    for (int i = 0; i < B; i++) {
        for (auto j : adj[b[i]]) {
            if (!binary_search(b, b + B, j.first)) {
                if (res.d[j.first] > -1) {
                    distances.push_back(res.d[j.first] + j.second);
                }
            }
        }
    }
    sort(distances.begin(), distances.end());

    // algorithm which efficiently distributes the fortifications on each path
    // in order to achieve the highest minimum of the distances
    while (1) {
        long long beginningEquals = howManyEquals(distances);
        long long dif;

        if (beginningEquals == (long long)distances.size()) {
            long long med = K / beginningEquals;
            for (int i = 0; i < beginningEquals; i++) {
                distances[i] += med;
            }

            break;
        } else {
            dif = distances[beginningEquals] - distances[0];
            if (K >= beginningEquals * dif) {
                for (int i = 0; i < beginningEquals; i++) {
                    distances[i] += dif;
                }
                K = K - beginningEquals * dif;
            } else {
                long long med = K / beginningEquals;
                for (int i = 0; i < beginningEquals; i++) {
                    distances[i] += med;
                }

                break;
            }
        }
    }

    fout << distances[0];

    return 0;
}
