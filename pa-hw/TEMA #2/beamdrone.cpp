#include <bits/stdc++.h>

using namespace std;

/**
 * @brief Given a cell, it traverses its row and column, computing the
 *        costs for all unvisited elements, as long as there is no wall in the
 *        way. Each neighbour found is added in a queue, in order to repeat
 *        this process for it when its turn comes.
 * 
 * @param N grid's number of rows
 * @param M grid's number of columns
 * @param x the starting point's 'x' coordinate
 * @param y the starting point's 'y' coordinate
 * @param x_dest the finish point's 'x' coordinate
 * @param y_dest the finish point's 'y' coordinate
 * @param costs costs matrix
 * @param visited visited matrix
 * @param q queue of points
 * @return int - 1 if the finish point was reached, 0 otherwise
 */
int instant_traverse(int N, int M, int x, int y, int x_dest, int y_dest,
                     int **costs, int **visited, queue<pair<int, int>> &q) {
    // DIRECTION: UP
    for (int i = x - 1; i >= 0; i--) {
        if (visited[i][y] == -1) {
            // we hit a wall in the way - STOP
            break;
        } else if (visited[i][y] == 1) {
            // already computed the cost of this point
            continue;
        }

        visited[i][y] = 1;
        costs[i][y] = costs[x][y] + 1;
        q.push({i, y});

        if (i == x_dest && y == y_dest) return 1;
    }

    // DIRECTION: DOWN
    for (int i = x + 1; i < N; i++) {
        if (visited[i][y] == -1) {
            // we hit a wall in the way - STOP
            break;
        } else if (visited[i][y] == 1) {
            // already computed the cost of this point
            continue;
        }

        visited[i][y] = 1;
        costs[i][y] = costs[x][y] + 1;
        q.push({i, y});

        if (i == x_dest && y == y_dest) return 1;
    }

    // DIRECTION: EAST
    for (int j = y - 1; j >= 0; j--) {
        if (visited[x][j] == -1) {
            // we hit a wall in the way - STOP
            break;
        } else if (visited[x][j] == 1) {
            // already computed the cost of this point
            continue;
        }

        visited[x][j] = 1;
        costs[x][j] = costs[x][y] + 1;
        q.push({x, j});

        if (x == x_dest && j == y_dest) return 1;
    }

    // DIRECTION: WEST
    for (int j = y + 1; j < M; j++) {
        if (visited[x][j] == -1) {
            // we hit a wall in the way - STOP
            break;
        } else if (visited[x][j] == 1) {
            // already computed the cost of this point
            continue;
        }

        visited[x][j] = 1;
        costs[x][j] = costs[x][y] + 1;
        q.push({x, j});

        if (x == x_dest && j == y_dest) return 1;
    }

    return 0;
}

/**
 * @brief Traverse all cells, adding all the neigbours of a cell in a
 *        queue. It computes the costs from source to all other cells and
 *        stores it in the costs matrix. At the end, the cost from source to
 *        destination is the costs[x_dest][y_dest] element.
 * 
 * @param N grid's number of rows
 * @param M grid's number of columns
 * @param x_source the starting point's 'x' coordinate
 * @param y_source the starting point's 'y' coordinate
 * @param x_dest the finish point's 'x' coordinate
 * @param y_dest the finish point's 'y' coordinate
 * @param costs costs matrix
 * @param visited visited matrix
 */
void traversal(int N, int M, int x_source, int y_source,
               int x_dest, int y_dest, int **costs, int **visited) {
    queue<pair<int, int>> q;
    q.push({x_source, y_source});
    visited[x_source][y_source] = 1;

    while (!q.empty()) {
        pair<int, int> cell = q.front();
        int x = cell.first;
        int y = cell.second;
        q.pop();

        // if the destination was reached, there is no need to further
        // calculate costs, as the first found cost will always be the minimum
        // one, so simply stop the algorithm in order to keep it efficient
        int ans =
            instant_traverse(N, M, x, y, x_dest, y_dest, costs, visited, q);
        if (ans) {
            return;
        }
    }
}

/**
 * @brief Dynamically allocates a matrix.
 * 
 * @param N number of rows
 * @param M number of columns
 * @return int** pointer to matrix
 */
int **malloc_matrix(int N, int M) {
    int **mat = (int **)malloc(N * sizeof(int *));
    for (int i = 0; i < N; i++) {
        mat[i] = (int *)calloc(M, sizeof(int));
    }

    return mat;
}

/**
 * @brief Free a dynamically allocated matrix.
 * 
 * @param N number of rows
 * @param mat pointer to matrix
 */
void free_matrix(int N, int **mat) {
    for (int i = 0; i < N; i++) {
        free(mat[i]);
    }
    free(mat);
}

int main() {
    ifstream fin("beamdrone.in");
    ofstream fout("beamdrone.out");

    int N, M;
    int x1, y1, x2, y2;

    fin >> N >> M;
    fin >> x1 >> y1 >> x2 >> y2;

    // matrix used to note if an element is already visited(1),
    // or not visited yet(0). The walls are specially marked with (-1).
    int **visited = malloc_matrix(N, M);
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            char temp;
            fin >> temp;
            if (temp == 'W') {
                visited[i][j] = -1;
            }
        }
    }

    // matrix used to compute the costs from source(x1, y1) to all other cells
    int **costs = malloc_matrix(N, M);
    costs[x1][y1] = -1;

    traversal(N, M, x1, y1, x2, y2, costs, visited);

    fout << costs[x2][y2];

    free_matrix(N, visited);
    free_matrix(N, costs);

    return 0;
}
