import copy

MAX = 20 + 5
INF = 0x7fff0000

RED = 0
BLACK = -1
EMPTY = -2

MAP = [[0] * MAX for _ in range(MAX)]

# ↑, →, ↓, ←
dr = [-1, 0, 1, 0]
dc = [0, 1, 0, -1]

class RC:
    def __init__(self, r: int, c: int):
        self.r = r
        self.c = c

queue = [RC(0, 0) for _ in range(MAX * MAX)]

class BOMB:
    def __init__(self, total: int, red: int, r: int, c: int):
        self.total = total # 전체 폭탄 개수
        self.red = red # 빨간 폭탄 개수
        self.r = r # 행
        self.c = c # 열

def input_data():
    global N, M, MAP
    
    N, M = map(int, input().split())
    
    MAP = [[BLACK] * MAX for _ in range(MAX)]
    
    for r in range(1, N + 1):
        MAP[r][1:N + 1] = map(int, input().split())
        
def print_map(map): # for debug
    for r in range(1, N + 1):
        print(*map[r][1:N + 1])
    print("") 
    
def rotate():
    tmp_map = copy.deepcopy(MAP)
    
    for r in range(1, N + 1):
        for c in range(1, N + 1):
            MAP[r][c] = tmp_map[c][N - r + 1]

def BFS(r, c):
    visit = [[False] * MAX for _ in range(MAX)]
    selected_bomb = BOMB(1, 0, r, c)
    
    rp, wp = 0, 0
    
    bomb = MAP[r][c]
    
    queue[wp].r = r
    queue[wp].c = c
    wp += 1
    
    visit[r][c] = True
    
    while rp < wp:
        out = queue[rp]
        rp += 1
        
        for i in range(4):
            nr = out.r + dr[i]
            nc = out.c + dc[i]
        
            if MAP[nr][nc] == BLACK or visit[nr][nc] == True: continue
        
            if MAP[nr][nc] == bomb or MAP[nr][nc] == RED:
                queue[wp].r = nr
                queue[wp].c = nc
                wp += 1
            
                visit[nr][nc] = True
            
                selected_bomb.total += 1
            
                if MAP[nr][nc] == RED: selected_bomb.red += 1
                
    return selected_bomb
    
def delete_bomb(r, c): # BFS
    visit = [[False] * MAX for _ in range(MAX)]
    
    rp, wp = 0, 0
    
    bomb = MAP[r][c]
    MAP[r][c] = EMPTY
    
    queue[wp].r = r
    queue[wp].c = c
    wp += 1
    
    visit[r][c] = True
    
    while rp < wp:
        out = queue[rp]
        rp += 1
        
        for i in range(4):
            nr = out.r + dr[i]
            nc = out.c + dc[i]
        
            if MAP[nr][nc] == BLACK or visit[nr][nc] == True: continue
        
            if MAP[nr][nc] == bomb or MAP[nr][nc] == RED:
                queue[wp].r = nr
                queue[wp].c = nc
                wp += 1
            
                visit[nr][nc] = True
                MAP[nr][nc] = EMPTY

# a가 우선순위가 더 높으면 true
def is_priority(a, b):
	if a.total != b.total: return a.total > b.total
	if a.red != b.red: return a.red < b.red
	if a.r != b.r: return a.r > b.r

	return a.c < b.c

def bomb_down_column(col):
    for r in range(N, 0, -1):
        if MAP[r][col] == BLACK or MAP[r][col] == EMPTY: continue
        
        sr = r
        while True:
            if MAP[sr + 1][col] != EMPTY: break
        
            if MAP[sr + 1][col] == EMPTY:                
                MAP[sr + 1][col], MAP[sr][col] = MAP[sr][col], MAP[sr + 1][col]
                
            sr += 1

def bomb_down():
    for col in range(1, N + 1):
        bomb_down_column(col)

def simulate():
    score = 0
    while True:
        selected_bomb = BOMB(-1, INF, -1, INF)
        for r in range(1, N + 1):
            for c in range(1, N + 1):
                if MAP[r][c] in (BLACK, RED, EMPTY): continue
                
                tmp = BFS(r, c)
                
                if tmp.total == 1: continue
                
                if is_priority(tmp, selected_bomb): selected_bomb = tmp

        if selected_bomb.total == -1: break

        score += (selected_bomb.total ** 2)
        
        delete_bomb(selected_bomb.r, selected_bomb.c)
        
        bomb_down()
        rotate()
        bomb_down()

    return score

# T = int(input())
T = 1
for tc in range(T):
    input_data()
    
    print(simulate())