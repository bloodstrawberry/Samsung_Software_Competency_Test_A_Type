MAX = 20 + 5

EAST = 1
WEST = 2
NORTH = 3
SOUTH = 4

MAP = [[0] * MAX for _ in range(MAX)]

visit = [[False] * MAX for _ in range(MAX)]
score_board = [[0] * MAX for _ in range(MAX)]

class CUBE:
    def __init__(self, up: int, left: int, top: int, right: int, down: int, bottom: int):
        self.up = up
        self.left = left
        self.top = top
        self.right = right
        self.down = down
        self.bottom = bottom        

cube = CUBE(0, 0, 0, 0, 0, 0)

class RC:
    def __init__(self, r: int, c: int):
        self.r = r
        self.c = c

queue = [RC(0, 0) for _ in range(MAX * MAX)]   

# -, 동, 서, 북, 남 
dr = [0, 0, 0, -1, 1]
dc = [0, 1, -1, 0, 0]

def input_data():             
    global N, M
    
    N, M = map(int, input().split())
    
    for r in range(1, N + 1):
        MAP[r][1:N + 1] = map(int, input().split())

def print_map(): # for debug
    for r in range(1, N + 1):
        print(*MAP[r][1:N + 1])
    print("")
    
def print_cube(): # for debug
    print(cube.up)
    print(cube.left, cube.top, cube.right)
    print(cube.down)
    print(cube.bottom)
    print("")
    
def move_east():
    tmp = [cube.up, cube.left, cube.top, cube.right, cube.down, cube.bottom]
    
    cube.top = tmp[1]
    cube.right = tmp[2]
    cube.bottom = tmp[3]
    cube.left = tmp[5]

def move_west():
    tmp = [cube.up, cube.left, cube.top, cube.right, cube.down, cube.bottom]
    
    cube.top = tmp[3]
    cube.right = tmp[5]
    cube.bottom = tmp[1]
    cube.left = tmp[2]
    
def move_north():
    tmp = [cube.up, cube.left, cube.top, cube.right, cube.down, cube.bottom]
    
    cube.up = tmp[2]
    cube.top = tmp[4]
    cube.down = tmp[5]
    cube.bottom = tmp[0]
    
def move_south():
    tmp = [cube.up, cube.left, cube.top, cube.right, cube.down, cube.bottom]
    
    cube.up = tmp[5]
    cube.top = tmp[0]
    cube.down = tmp[2]
    cube.bottom = tmp[4]
        
def BFS(r, c):
    number = MAP[r][c]
    
    rp, wp = 0, 0
    
    queue[wp].r = r
    queue[wp].c = c
    wp += 1
    
    visit[r][c] = True
    
    while rp < wp:
        out = queue[rp]
        rp += 1
        
        for i in range(1, 5):
            nr = out.r + dr[i]
            nc = out.c + dc[i]
            
            if nr < 1 or nc < 1 or nr > N or nc > N: continue
            
            if MAP[nr][nc] != number or visit[nr][nc] == True: continue
            
            queue[wp].r = nr
            queue[wp].c = nc
            wp += 1
            
            visit[nr][nc] = True
    
    for i in range(wp):
        r, c = queue[i].r, queue[i].c        
        score_board[r][c] = number * wp

def make_score_board():
    global visit
    
    visit = [[False] * MAX for _ in range(MAX)]
    
    for r in range(1, N + 1):
        for c in range(1, N + 1):
            if visit[r][c] == True: continue
            
            BFS(r, c)
            
def simulate():
    # 동 : 1, 서 : 2, 북 : 3, 남 : 4
    changeDir = [0, 2, 1, 4, 3]
    changeClock = [0, 4, 3, 1, 2]
    changeCounterClock = [0, 3, 4, 2, 1]

    sr, sc = 1, 1
    dir = EAST

    cube.up = 5
    cube.left = 4
    cube.top = 1
    cube.right = 3
    cube.down = 2
    cube.bottom = 6

    score = 0
    for _ in range(M):
        nr = sr + dr[dir]
        nc = sc + dc[dir]

        if nr < 1 or nc < 1 or nr > N or nc > N:
            dir = changeDir[dir]
            nr = sr + dr[dir]
            nc = sc + dc[dir]

        if dir == EAST: move_east()
        elif dir == WEST: move_west()
        elif dir == NORTH: move_north()
        elif dir == SOUTH: move_south()

        score += score_board[nr][nc]

        A = cube.bottom
        B = MAP[nr][nc]

        if A > B: dir = changeClock[dir]
        elif A < B: dir = changeCounterClock[dir]

        sr, sc = nr, nc
    
    return score       
                
# T = int(input())
T = 1
for _ in range(T):
    input_data()
    
    make_score_board()
    
    print(simulate())