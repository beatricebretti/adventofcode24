from itertools import product

with open('input.txt') as file:
    grid = [list(line.strip()) for line in file]

dirs = ((-1, 0), (0, 1), (1, 0), (0, -1))
dirs_all = (*dirs, (-1, -1), (-1, 1), (1, 1), (1, -1))
indicies = set(range(len(grid)))

def build_graph(grid, match_condition):
    graph = {}
    for y, x in product(indicies, repeat=2):
        val = grid[y][x]
        graph.setdefault((y, x), [])
        for dy, dx in dirs:
            if 0 <= (y2 := y + dy) < len(grid) and 0 <= (x2 := x + dx) < len(grid[0]) and grid[y2][x2] == val:
                graph[(y, x)].append((y2, x2))
    return graph

def get_components(graph):
    visited, components = set(), []
    for node in graph:
        if node not in visited:
            component = []
            stack = [node]
            while stack:
                n = stack.pop()
                if n not in visited:
                    visited.add(n)
                    component.append(n)
                    stack.extend(graph[n])
            components.append(component)
    return components

def calc_fence(region):
    return sum(
        1 for y in range(len(region)) for x in range(len(region[0])) 
        if (x == 0 or region[y][x] != region[y][x-1]) or (y == 0 or region[y][x] != region[y-1][x])
    )

def create_region(points):
    min_y, min_x = min(y for y, _ in points), min(x for _, x in points)
    region = [['.' for _ in range(max(x for _, x in points) - min_x + 1)] for _ in range(max(y for y, _ in points) - min_y + 1)]
    for y, x in points: region[y - min_y][x - min_x] = 'O'
    return region

graph = build_graph(grid, lambda a, b: a == b)
regions = get_components(graph)

print(sum(len(region) * calc_fence(create_region(region)) for region in regions))
print(sum(len(region) * len({(y*2, x*2) for y, x in region}) for region in regions))