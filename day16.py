import heapq
DIRECTIONS = [(0, 1), (1, 0), (0, -1), (-1, 0)]  
DIRECTION_NAMES = ['E', 'S', 'W', 'N']

def parse_input(filename):
    with open(filename, 'r') as file:
        maze = [list(line.strip()) for line in file]
    start = end = None
    for i, row in enumerate(maze):
        for j, char in enumerate(row):
            if char == 'S':
                start = (i, j)
            elif char == 'E':
                end = (i, j)
    return maze, start, end

def in_bounds(maze, x, y):
    return 0 <= x < len(maze) and 0 <= y < len(maze[0]) and maze[x][y] != '#'

def solve_maze(filename):
    maze, start, end = parse_input(filename)
    rows, cols = len(maze), len(maze[0])
    pq = [(0, start[0], start[1], 0)]  
    visited = set() 

    while pq:
        score, x, y, direction = heapq.heappop(pq)
        if (x, y) == end:
            return score
        if (x, y, direction) in visited:
            continue
        visited.add((x, y, direction))
        dx, dy = DIRECTIONS[direction]
        nx, ny = x + dx, y + dy
        if in_bounds(maze, nx, ny):
            heapq.heappush(pq, (score + 1, nx, ny, direction))
        cw_direction = (direction + 1) % 4 
        ccw_direction = (direction - 1) % 4 
        heapq.heappush(pq, (score + 1000, x, y, cw_direction))
        heapq.heappush(pq, (score + 1000, x, y, ccw_direction))
    return -1  

if __name__ == "__main__":
    print( solve_maze("input.txt") )