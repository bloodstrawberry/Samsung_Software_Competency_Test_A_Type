import copy

MAX = 8 + 3

EMPTY = 0
WALL = 1
FIRE = 2

MAP = [[0] * MAX for _ in range(MAX)]
tmpMAP = [[0] * MAX for _ in range(MAX)]

num_of_cases = [0] * 5

class RC:
    def __init__(self, r: int, c: int):
        self.r = r
        self.c = c
    
queue = [RC(0, 0) for _ in range(MAX * MAX)]

emptyRoom = [RC(0, 0) for _ in range(MAX * MAX)]
emptyCount = 0

# ↑, →, ↓, ←
dr = [-1, 0, 1, 0]
dc = [0, 1, 0, -1]

def input_data():             
    global N, M
    
    N, M = map(int, input().split())
        
    for r in range(1, N + 1):
        MAP[r][1:M + 1] = map(int, input().split())
                                
def print_map(): # for debug
    for r in range(1, N + 1):
        print(*MAP[r][1:M + 1])
    print("")
   
def print_cases():
    print(*num_of_cases[:3])
   
def BFS():
    global tmpMAP
    
    tmpMAP = copy.deepcopy(MAP)
    
    rp, wp = 0, 0
    
    for r in range(1, N + 1):
        for c in range(1, M + 1):
            if tmpMAP[r][c] == FIRE:
                queue[wp].r = r
                queue[wp].c = c
                wp += 1
            
    while rp < wp:
        out = queue[rp]
        rp += 1
        
        for i in range(4):
            nr = out.r + dr[i]
            nc = out.c + dc[i]
            
            if nr < 1 or nc < 1 or nr > N or nc > M: continue
            if tmpMAP[nr][nc] != 0: continue
            
            queue[wp].r = nr
            queue[wp].c = nc
            wp += 1
            
            tmpMAP[nr][nc] = FIRE

def countEmpty():
    sum = 0
    for r in range(1, N + 1):
        for c in range(1, M + 1):
            if tmpMAP[r][c] == 0: sum += 1
            
    return sum

def DFS(depth, sr):
    global max_answer, MAP
    
    # print_map()
    
    if depth == 3:
        # print_cases()
        
        BFS()
        
        tmp = countEmpty()
        if max_answer < tmp: max_answer = tmp
        
        return
    
    for r in range(sr, N + 1):
        for c in range(1, M + 1):
            if MAP[r][c] != EMPTY: continue
            
            MAP[r][c] = WALL
            DFS(depth + 1, r)
            MAP[r][c] = EMPTY

# T = int(input())
T = 1
for _ in range(T): 
    global max_answer
    
    input_data()     
    
    # setEmptyCount()
    
    max_answer = 0
    
    DFS(0, 1)
    
    print(max_answer)