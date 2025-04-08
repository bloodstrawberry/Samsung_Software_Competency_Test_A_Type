import copy

MAX_N = 50 + 5
MAX_M = 10 + 3
INF = 0x7fff0000

VIRUS = 0
WALL = 1
HOSPITAL = 2

MAP = [[0] * MAX_N for _ in range(MAX_N)]
tmpMAP = [[0] * MAX_N for _ in range(MAX_N)]

num_of_cases = [0] * MAX_M

class RC:
    def __init__(self, r: int, c: int):
        self.r = r
        self.c = c

queue = [RC(0, 0) for _ in range(MAX_N * MAX_N)]

hospital = [RC(0, 0) for _ in range(MAX_M)]
hcnt = 0

# ↑, →, ↓, ←
dr = [-1, 0, 1, 0]
dc = [0, 1, 0, -1]

def input_data():
    global N, M, MAP, hospital, hcnt
    
    N, M = map(int, input().split())
    
    for r in range(1, N + 1):
        MAP[r][1:N + 1] = map(int, input().split())

    # 전처리
    for r in range(1, N + 1):
        for c in range(1, N + 1):
            if MAP[r][c] == WALL: MAP[r][c] = -1
            elif MAP[r][c] == HOSPITAL:
                hospital[hcnt].r = r
                hospital[hcnt].c = c
                hcnt += 1
                
                MAP[r][c] = -2
                
def print_map(): # for debug
    for r in range(1, N + 1):
        print(' '.join('%2d' % num for num in tmpMAP[r][1:N + 1]))
    print("")
                
def print_cases():
    print(*num_of_cases[:3])
    print("")
                
def check_virus():
    for r in range(1, N + 1):
        for c in range(1, N + 1):
            if tmpMAP[r][c] == VIRUS:
                return True
            
    return False

def BFS():
    global tmpMAP
    
    tmpMAP = copy.deepcopy(MAP)
    
    for i in range(M):
        index = num_of_cases[i]
        
        hr, hc = hospital[index].r, hospital[index].c
        
        tmpMAP[hr][hc] = 1
    
    rp, wp = 0, 0
    
    for r in range(1, N + 1):
        for c in range(1, N + 1):
            if tmpMAP[r][c] == 1:
                queue[wp].r = r
                queue[wp].c = c
                wp += 1
                
    while rp < wp:
        out = queue[rp]
        rp += 1
        
        for i in range(4):
            nr = out.r + dr[i]
            nc = out.c + dc[i]
            
            if nr < 1 or nc < 1 or nr > N or nc > N: continue
            
            if tmpMAP[nr][nc] == 0:
                queue[wp].r = nr
                queue[wp].c = nc
                wp += 1
                
                tmpMAP[nr][nc] = tmpMAP[out.r][out.c] + 1
            elif tmpMAP[nr][nc] == -2:
                if check_virus() == True:
                    queue[wp].r = nr
                    queue[wp].c = nc
                    wp += 1
                    
                    tmpMAP[nr][nc] = tmpMAP[out.r][out.c] + 1
            
def get_answer():
    max = 0
    for r in range(1, N + 1):
        for c in range(1, N + 1):
            if tmpMAP[r][c] == 0: return INF
            if max < tmpMAP[r][c]: max = tmpMAP[r][c]
            
    return max - 1

def DFS(depth, start):
    global min_answer
    
    if depth == M:
        # print_cases()
        
        BFS()
        
        tmp = get_answer()
        if tmp < min_answer: min_answer = tmp
        
        return

    for i in range(start, hcnt):
        num_of_cases[depth] = i        
        DFS(depth + 1, i + 1)

# T = int(input())
T = 1
for tc in range(T):
    global min_answer
    
    input_data()
    
    min_answer = INF
    
    DFS(0, 0)
    
    if min_answer == INF: print(-1)
    else: print(min_answer)