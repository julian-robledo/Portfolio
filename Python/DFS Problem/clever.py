# Author: Julian Robledo, jrobledo2017@my.fit.edu
# Course: CSE 2050, Fall 2019
# Project: How Clever is That?
from sys import (stdin, stdout)


def dfs(key, path, num_paths):
    # This is a standard dfs recursive function, that tracks when all nodes
    # have been traversed, and increases a counter based on the number of paths
    # that traverse all nodes.
    VISITED[key] = True
    path.append(key)

    # If it has traversed all nodes and the last node is (5, 5), increment valid paths.
    if len(path) == NUM_GRASS_TILES and key == (5, 5):
        num_paths[0] += 1

    # Else, for every adjacent node in current node, if it's not visited and not an
    # obstacle, traverse it.
    else:
        for i in GRID[key]:
            if not VISITED[i] and i not in OBSTACLE_NODES:
                dfs(i, path, num_paths)

    # if all adjacent nodes have been visited or all are obstacles, return to the previous
    # node, and mark this one as not visited.
    path.pop()
    VISITED[key] = False


# Dictionary to track which nodes have been visited
VISITED = {(1, 1): False,
           (1, 2): False,
           (1, 3): False,
           (1, 4): False,
           (1, 5): False,
           (2, 1): False,
           (2, 2): False,
           (2, 3): False,
           (2, 4): False,
           (2, 5): False,
           (3, 1): False,
           (3, 2): False,
           (3, 3): False,
           (3, 4): False,
           (3, 5): False,
           (4, 1): False,
           (4, 2): False,
           (4, 3): False,
           (4, 4): False,
           (4, 5): False,
           (5, 1): False,
           (5, 2): False,
           (5, 3): False,
           (5, 4): False,
           (5, 5): False}

# Since the grid is a constant 5x5, it's hard coded in as a dict.
GRID = {(1, 1): [(1, 2), (2, 1)],
        (1, 2): [(1, 1), (1, 3), (2, 2)],
        (1, 3): [(1, 2), (1, 4), (2, 3)],
        (1, 4): [(1, 3), (1, 5), (2, 4)],
        (1, 5): [(1, 4), (2, 5)],
        (2, 1): [(1, 1), (2, 2), (3, 1)],
        (2, 2): [(2, 1), (1, 2), (2, 3), (3, 2)],
        (2, 3): [(2, 2), (1, 3), (2, 4), (3, 3)],
        (2, 4): [(2, 3), (1, 4), (2, 5), (3, 4)],
        (2, 5): [(2, 4), (1, 5), (3, 5)],
        (3, 1): [(2, 1), (3, 2), (4, 1)],
        (3, 2): [(3, 1), (2, 2), (3, 3), (4, 2)],
        (3, 3): [(3, 2), (2, 3), (3, 4), (4, 3)],
        (3, 4): [(3, 3), (2, 4), (3, 5), (4, 4)],
        (3, 5): [(3, 4), (2, 5), (4, 5)],
        (4, 1): [(3, 1), (4, 2), (5, 1)],
        (4, 2): [(4, 1), (3, 2), (4, 3), (5, 2)],
        (4, 3): [(4, 2), (3, 3), (4, 4), (5, 3)],
        (4, 4): [(4, 3), (3, 4), (4, 5), (5, 4)],
        (4, 5): [(4, 4), (3, 5), (5, 5)],
        (5, 1): [(4, 1), (5, 2)],
        (5, 2): [(5, 1), (4, 2), (5, 3)],
        (5, 3): [(5, 2), (4, 3), (5, 4)],
        (5, 4): [(5, 3), (4, 4), (5, 5)],
        (5, 5): [(5, 4), (4, 5)]}

# Calculates the number of available tiles on the grid
NUM_OBSTACLES = int(stdin.readline())
NUM_GRASS_TILES = len(GRID) - NUM_OBSTACLES

# Following two loops create the list of obstacle nodes.
OBSTACLE_LOCATIONS = []
for line in stdin:
    TEMP = [tuple(int(i) for i in line.split())]
    OBSTACLE_LOCATIONS.append(TEMP)

OBSTACLE_NODES = []
for i in range(NUM_OBSTACLES):
    OBSTACLE_NODES.append(OBSTACLE_LOCATIONS[i][0])

NUM_PATHS = [0]

# Runs dfs with the constant starting point of (1, 1)
dfs((1, 1), [], NUM_PATHS)
stdout.write("{}".format(NUM_PATHS[0]))
