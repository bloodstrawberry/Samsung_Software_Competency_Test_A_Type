MAX = 20 + 5

EAST = 0
WEST = 1
SOUTH = 2
NORTH = 3
TOP = 4
BOTTOM = 5

EMPTY = 0
WALL = 1
TIME_MACHINE = 2
CUBE = 3
EXIT = 4

RIGHT = 0
LEFT = 1
DOWN = 2
UP = 3

MAP = [[[0] * MAX for _ in range(MAX)] for _ in range(6)]
visit = [[[0] * MAX for _ in range(MAX)] for _ in range(6)]

TIME_WALL = [[[0] * MAX for _ in range(MAX)] for _ in range(6)]

class RC:
    def __init__(self, r: int, c: int):
        self.r = r
        self.c = c

start = RC(0, 0)
end = RC(0, 0)

class PRC:
    def __init__(self, p: int, r: int, c: int):
        self.p = p # plane
        self.r = r        
        self.c = c

queue = [PRC(0, 0, 0) for _ in range(MAX * MAX * 6)]
next = [[[[PRC(0, 0, 0) for _ in range(4)] for _ in range(MAX)] for _ in range(MAX)] for _ in range(6)]

class TIME_INFO:
    def __init__(self, p: int, r: int, c: int, d: int, v: int):
        self.p = p
        self.r = r        
        self.c = c
        self.d = d
        self.v = v

time_info = [TIME_INFO(0, 0, 0, 0, 0) for _ in range(10 + 3)]

# →, ←, ↓, ↑
dr = [0, 0, 1, -1]
dc = [1, -1, 0, 0]
        
def input_data():   
    global N, M, F, MAP, visit, TIME_WALL, start, end
    
    N, M, F = map(int, input().split())
    
	# init
    MAP = [[[0] * MAX for _ in range(MAX)] for _ in range(6)]
    visit = [[[0] * MAX for _ in range(MAX)] for _ in range(6)]
    TIME_WALL = [[[0] * MAX for _ in range(MAX)] for _ in range(6)]
    
    for r in range(1, N + 1):
        MAP[BOTTOM][r][1:N + 1] = map(int, input().split())
    
    for r in range(1, N + 1):
        for c in range(1, N + 1):
            if MAP[BOTTOM][r][c] == EXIT:
                end = RC(r, c)
                
    for i in range(5):
        for r in range(1, M + 1):
            MAP[i][r][1:M + 1] = map(int, input().split())
            
    for r in range(1, M + 1):
        for c in range(1, M + 1):
            if MAP[TOP][r][c] == TIME_MACHINE:
                start = RC(r, c)

	# 시간 이상 현상
    for f in range(F):
        r, c, d, v = map(int, input().split())
        time_info[f].p = BOTTOM
        time_info[f].r = r + 1
        time_info[f].c = c + 1
        time_info[f].d = d
        time_info[f].v = v
                 
def print_map(map, size): # for debug
    for r in range(1, size + 1):
        print(*map[r][1:size + 1])
    print("")

def print_map_all(map): # for debug
	print("BOTTOM")
	print_map(map[BOTTOM], N)

	print("EAST")
	print_map(map[EAST], M)

	print("WEST")
	print_map(map[WEST], M)

	print("SOUTH")
	print_map(map[SOUTH], M)

	print("NORTH")
	print_map(map[NORTH], M)

	print("TOP")
	print_map(map[TOP], M)

def preprocess():
    for i in range(1, M + 1):
        # TOP (1, i)에서 ↑ 가면 NORTH (1, M + 1 - i)
        next[TOP][1][i][UP] = PRC(NORTH, 1, M + 1 - i)
        
        # NORTH (1, i)에서 ↑ 가면 TOP (1, M + 1 - i)
        next[NORTH][1][i][UP] = PRC(TOP, 1, M + 1 - i)

		# ------------------------------------- #

        # TOP (M, i)에서 ↓ 가면 SOUTH (1, i)
        next[TOP][M][i][DOWN] = PRC(SOUTH, 1, i)
        
        # SOUTH (1, i)에서 ↑ 가면 TOP (M, i)
        next[SOUTH][1][i][UP] = PRC(TOP, M, i)

		# ------------------------------------- #

        # TOP (i, M)에서 → 가면 EAST (1, M + 1 - i)
        next[TOP][i][M][RIGHT] = PRC(EAST, 1, M + 1 - i)
        
        # EAST (1, i)에서 ↑ 가면 TOP (M + 1 - i, M)
        next[EAST][1][i][UP] = PRC(TOP, M + 1 - i, M)

		# ------------------------------------- #

        # TOP (i, 1)에서 ← 가면 WEST (1, i)
        next[TOP][i][1][LEFT] = PRC(WEST, 1, i)
        
        # WEST (1, i)에서 ↑ 가면 TOP (i, 1)
        next[WEST][1][i][UP] = PRC(TOP, i, 1)

    # →
    for i in range(1, M + 1):
        # SOUTH (i, M)에서 → 가면 EAST (i, 1)
        next[SOUTH][i][M][RIGHT] = PRC(EAST, i, 1)
        
        # EAST (i, M)에서 → 가면 NORTH (i, 1)
        next[EAST][i][M][RIGHT] = PRC(NORTH, i, 1)
        
        # NORTH (i, M)에서 → 가면 WEST (i, 1)
        next[NORTH][i][M][RIGHT] = PRC(WEST, i, 1)
        
        # WEST (i, M)에서 → 가면 SOUTH (i, 1)
        next[WEST][i][M][RIGHT] = PRC(SOUTH, i, 1)

    # ←
    for i in range(1, M + 1):
        # SOUTH (i, 1)에서 ← 가면 WEST (i, M)
        next[SOUTH][i][1][LEFT] = PRC(WEST, i, M)
        
        # WEST (i, 1)에서 ← 가면 NORTH (i, M)
        next[WEST][i][1][LEFT] = PRC(NORTH, i, M)
        
        # NORTH (i, 1)에서 ← 가면 EAST (i, M)
        next[NORTH][i][1][LEFT] = PRC(EAST, i, M)
        
        # EAST (i, 1)에서 ← 가면 SOUTH (i, M)
        next[EAST][i][1][LEFT] = PRC(SOUTH, i, M)

    # BOTTOM, WEST
    index = 1
    for r in range(1, N + 1):
        for c in range(1, N + 1):
            if MAP[BOTTOM][r][c] == CUBE:                
                next[BOTTOM][r][c - 1][RIGHT] = PRC(WEST, M, index)                           
                next[WEST][M][index][DOWN] = PRC(BOTTOM, r, c - 1)              
                index += 1
                break

    # BOTTOM, EAST
    index = M
    for r in range(1, N + 1):
        for c in range(N, 0, -1):
            if MAP[BOTTOM][r][c] == CUBE:
                next[BOTTOM][r][c + 1][LEFT] = PRC(EAST, M, index)
                next[EAST][M][index][DOWN] = PRC(BOTTOM, r, c + 1)
                index -= 1
                break

    # BOTTOM, NORTH
    index = M
    for c in range(1, N + 1):
        for r in range(1, N + 1):
            if MAP[BOTTOM][r][c] == CUBE:
                next[BOTTOM][r - 1][c][DOWN] = PRC(NORTH, M, index)
                next[NORTH][M][index][DOWN] = PRC(BOTTOM, r - 1, c)
                index -= 1
                break

    # BOTTOM, SOUTH
    index = 1
    for c in range(1, N + 1):
        for r in range(N, 0, -1):
            if MAP[BOTTOM][r][c] == CUBE:
                next[BOTTOM][r + 1][c][UP] = PRC(SOUTH, M, index)
                next[SOUTH][M][index][DOWN] = PRC(BOTTOM, r + 1, c)
                index += 1
                break

def make_time_wall():
    for f in range(F):
        p = time_info[f].p
        r = time_info[f].r
        c = time_info[f].c
        d = time_info[f].d
        v = time_info[f].v

        TIME_WALL[p][r][c] = 1

        while True:
            np = p
            nr = r + dr[d]
            nc = c + dc[d]

            if p == BOTTOM and MAP[BOTTOM][nr][nc] == CUBE:
                np = next[BOTTOM][r][c][d].p
                nr = next[BOTTOM][r][c][d].r
                nc = next[BOTTOM][r][c][d].c
            elif p != BOTTOM and (nr < 1 or nc < 1 or nr > M or nc > M):
                np = next[p][r][c][d].p
                nr = next[p][r][c][d].r
                nc = next[p][r][c][d].c

            if np == BOTTOM and (nr < 1 or nc < 1 or nr > N or nc > N): break
            if MAP[np][nr][nc] == WALL: break
            if nr == end.r and nc == end.c: break

            TIME_WALL[np][nr][nc] = TIME_WALL[p][r][c] + v

            p = np
            r = nr
            c = nc 

def BFS(r, c):
    rp, wp = 0, 0
    
    queue[wp].p = TOP
    queue[wp].r = r
    queue[wp].c = c        
    wp += 1

    visit[TOP][r][c] = 1

    while rp < wp:
        out = queue[rp]
        rp += 1

        if out.p == BOTTOM and out.r == end.r and out.c == end.c:
            return visit[BOTTOM][out.r][out.c] - 1

        for i in range(4):
            np = out.p
            nr = out.r + dr[i]
            nc = out.c + dc[i]

            if out.p == BOTTOM and MAP[BOTTOM][nr][nc] == CUBE:
                nxt = next[BOTTOM][out.r][out.c][i]
                np, nr, nc = nxt.p, nxt.r, nxt.c

            elif out.p != BOTTOM and (nr < 1 or nc < 1 or nr > M or nc > M):
                nxt = next[out.p][out.r][out.c][i]
                np, nr, nc = nxt.p, nxt.r, nxt.c

            if np == BOTTOM and (nr < 1 or nc < 1 or nr > N or nc > N): continue

            if MAP[np][nr][nc] == WALL or visit[np][nr][nc] != 0: continue

            # 시간의 벽
            if TIME_WALL[np][nr][nc] != 0 \
                and visit[out.p][out.r][out.c] + 1 >= TIME_WALL[np][nr][nc]: continue

            queue[wp].p = np
            queue[wp].r = nr
            queue[wp].c = nc
            wp += 1

            visit[np][nr][nc] = visit[out.p][out.r][out.c] + 1

    return -1

# T = int(input())
T = 1
for tc in range(T):  
    input_data()
    
    preprocess()
    
    make_time_wall()
    
    print(BFS(start.r, start.c))