# Algorithm Design - Project 2

All problems were implemented in `C++`, using `STL`. The problems involved
`graph algorithms`, such as **Dijkstra's Shortest Path**, **Topological Sort**,
**Graph Traversal**.

## Task #2 - Fortificatii
The cities were represented as nodes in an undirected graph.
`Dijkstra's Shortest Path` algorithm was used to compute
the distances from the capital to all other cities.\
The algorithm was slightly modified such as computed shortest path not to go
through barbarian cities, because we are interested in finding **direct paths**
between barbarians and our cities.

Then, an `ordered vector` containing the distances between the capital
and all barbarians, **through all possible paths**, is created.

The final goal is to fill this vector with `K` fortifications, such that
in the end the minimum element to be as high as possible.
This was done using an algorithm similar to the `water pouring` approach.

Time complexity: `O(B * logB + N + M * logN)`,
where `B` - number of barbarians,
      `N` - number of cities,
      `M` - number of routes

## Task #3 - Beamdrone
The approach begins by filling a visited matrix. A value of `0` stands for
an `unvisited node`, `1` stands for `visited`,
while `-1` is used to mark the walls.

A `traversal` algorithm is used to compute minimum costs from `source`
to every other node. Given a node, all its neighbours from row and column
are added in a queue and visited. Every `neighbour cost` will be
the `parent's cost + 1`. If a wall comes along in the traversal of
a row/column, the traversal on that way stops. If a node in the traversal is
already visited, it is being ignored. This happens because the first visit of
a node will guarantee the shortest cost from source to it.\
When the destination node is reached, the algorithm stops,
as there is no need to further compute costs for another nodes.

Time complexity: `O(N * M * (N + M))`,
where `N` and `M` - dimensions of the grid.

## Task #4 - Curse

The trainings' register is traversed and the cars are represented as
nodes in a graph. A car `A` better than a car `B` will be represented
as an edge from `A` to `B`.

In order to find the order of the cars, a `topological sort` is applied
on the previously created graph. The algorithm was implemented
using the `depth-first search` algorithm.
The reversed order of this traversal is the actual output for the problem.

Time complexity: `O(A * N + M * (A + N))`,
where `A` - number of trainings,
      `N` - number of routes,
      `M` - number of cars.

## License
[Adrian Croitoru](https://github.com/adriancroitoru97)
