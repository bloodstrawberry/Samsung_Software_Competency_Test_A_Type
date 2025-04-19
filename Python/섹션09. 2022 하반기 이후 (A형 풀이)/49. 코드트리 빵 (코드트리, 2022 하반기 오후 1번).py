import copy

MAX_N = 15 + 5
MAX_M = 30 + 5

INF = 0x7fff0000
BASECAMP = 1
WALL = 2

MAP = [[0] * MAX_N for _ in range(MAX_N)]
BLOCK = [[0] * MAX_N for _ in range(MAX_N)] # 이동 불가 확인

class RC:
    def __init__(self, r: int, c: int):
        self.r = r
        self.c = c

STORE = [RC(0, 0) for _ in range(MAX_M)]
PLAYER = [RC(0, 0) for _ in range(MAX_M)]
queue = [RC(0, 0) for _ in range(MAX_N * MAX_N)]

# ↑, ←, →, ↓
dr = [-1, 0, 0, 1]  
dc = [0, -1, 1, 0]

def input_data():   
    global N, M, MAP, BLOCK
    
    N, M = map(int, input().split())
    
    MAP = [[0] * MAX_N for _ in range(MAX_N)]
    BLOCK = [[0] * MAX_M for _ in range(MAX_M)]
    
    for r in range(1, N + 1):
        MAP[r][1:N + 1] = map(int, input().split())
    
    for m in range(1, M + 1):
        r, c = map(int, input().split())
        STORE[m].r = r
        STORE[m].c = c
        
def print_status(): # for debug
    tmp_map = copy.deepcopy(MAP)
        
    for r in range(1, N + 1):
        for c in range(1, N + 1):
            if tmp_map[r][c] == BASECAMP: tmp_map[r][c] = -1
            
    for r in range(1, N + 1):
        for c in range(1, N + 1):
            if BLOCK[r][c] == WALL: tmp_map[r][c] = -2
            
    for p in range(1, M + 1):
        tmp_map[PLAYER[p].r][PLAYER[p].c] = p
    
    for r in range(1, N + 1):
        print(' '.join('%2d' % num for num in tmp_map[r][1:N + 1]))
    print("")
    
def printBefore(before):  # before는 2차원 배열, N은 크기
    for r in range(1, N + 1):
        for c in range(1, N + 1):
            print(f"({before[r][c].r}, {before[r][c].c})", end=' ')
        print("")
    print("")
        
def get_next_step(index): # BFS
    visit = [[0] * MAX_N for _ in range(MAX_N)]
    before = [[RC(0, 0) for _ in range(MAX_N)] for _ in range(MAX_N)]
    
    rp = wp = 0
    
    sr = PLAYER[index].r
    sc = PLAYER[index].c
    er = STORE[index].r
    ec = STORE[index].c
    
    queue[wp].r = sr
    queue[wp].c = sc
    wp += 1
    
    visit[sr][sc] = 1
    
    before[sr][sc].r = -1
    before[sr][sc].c = -1
    
    while rp < wp:
        out = queue[rp]
        rp += 1
        
        if er == out.r and ec == out.c:
            tr, tc = er, ec
            while True:
                br, bc = before[tr][tc].r, before[tr][tc].c
            
                if br == sr and bc == sc: break
            
                tr, tc = br, bc
            
            return RC(tr, tc)
        
        for i in range(4):
            nr = out.r + dr[i]
            nc = out.c + dc[i]
            
            if nr < 1 or nc < 1 or nr > N or nc > N: continue
            if visit[nr][nc] != 0 or BLOCK[nr][nc] == WALL: continue
            
            queue[wp].r = nr
            queue[wp].c = nc
            wp += 1
            
            visit[nr][nc] = visit[out.r][out.c] + 1
            
            before[nr][nc] = out
            
    return RC(-1, -1)
    
def get_base_camp(index): # BFS
    visit = [[0] * MAX_N for _ in range(MAX_N)]
    
    rp = wp = 0
    
    sr = STORE[index].r
    sc = STORE[index].c
    
    queue[wp].r = sr
    queue[wp].c = sc
    wp += 1
    
    visit[sr][sc] = 1
    
    ret = RC(INF, INF)
    min_distance = INF
    while rp < wp:
        out = queue[rp]
        rp += 1
        
        # basecamp를 찾은 경우
        if MAP[out.r][out.c] == BASECAMP and BLOCK[out.r][out.c] == 0:
            if visit[out.r][out.c] < min_distance:
                min_distance = visit[out.r][out.c]
                ret = out
            elif visit[out.r][out.c] == min_distance:
                if out.r < ret.r: ret = out
                elif out.r == ret.r:
                    if out.c < ret.c:
                        ret = out
            
            continue
        
        for i in range(4):
            nr = out.r + dr[i]
            nc = out.c + dc[i]
            
            if nr < 1 or nc < 1 or nr > N or nc > N: continue
            if visit[nr][nc] != 0 or BLOCK[nr][nc] == WALL: continue
            
            queue[wp].r = nr
            queue[wp].c = nc
            wp += 1
            
            visit[nr][nc] = visit[out.r][out.c] + 1
                        
    return ret

def simulate():
    time = 0
    while True:
        # 1.
        next_step = [RC(0, 0) for _ in range(MAX_M)]
        for p in range(1, time + 1):
            if p > M: break
            if PLAYER[p].r == STORE[p].r and PLAYER[p].c == STORE[p].c: continue
            
            next_step[p] = get_next_step(p)

		# 2.
        count = 0
        for p in range(1, time + 1):
            if p > M: break
            
            if PLAYER[p].r == STORE[p].r and PLAYER[p].c == STORE[p].c:
                count += 1
                continue
            
            nr, nc = next_step[p].r, next_step[p].c
            PLAYER[p].r, PLAYER[p].c = nr, nc
            
            if nr == STORE[p].r and nc == STORE[p].c:
                BLOCK[nr][nc] = WALL
                                
        if count == M: return time
        
        time += 1
        
        # 3.
        if time <= M:
            position = get_base_camp(time)
            BLOCK[position.r][position.c] = WALL
            PLAYER[time] = RC(position.r, position.c)
    
    return -1 # for debug

# T = int(input())
T = 1
for tc in range(T):    
    input_data()
    
    print(simulate())