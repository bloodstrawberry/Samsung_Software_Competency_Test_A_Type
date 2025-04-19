MAX = 15 + 5
MAX_Q = 50 + 5

MAP = [[0] * MAX for _ in range(MAX)] # 배양 용기

class QUERY:
    def __init__(self, r1: int, c1: int, r2: int, c2: int):
        self.r1 = r1
        self.c1 = c1
        self.r2 = r2
        self.c2 = c2

query = [QUERY(0, 0, 0, 0)] * MAX_Q

class MICRO:
    def __init__(self, id: int, minR: int, minC: int, maxR: int, maxC: int, size: int):
        self.id = id
        self.minR = minR
        self.minC = minC
        self.maxR = maxR
        self.maxC = maxC
        self.size = size

micro = [MICRO(0, 0, 0, 0, 0, 0) for _ in range(MAX_Q)]
mcnt = 0

dead = [False] * MAX_Q # id로 따로 관리

class RC:
    def __init__(self, r: int, c: int):
        self.r = r
        self.c = c

queue = [RC(0, 0) for _ in range(MAX * MAX)]
visit = [[False] * MAX for _ in range(MAX)]

# ↑, →, ↓, ←
dr = [-1, 0, 1, 0]
dc = [0, 1, 0, -1]

def input_data():
    global N, Q
    
    N, Q = map(int, input().split())
    
    for q in range(1, Q + 1):
        r1, c1, r2, c2 = map(int, input().split())
        query[q] = QUERY(r1, c1, r2, c2)

def print_map(map): # for debug
    for r in range(0, N + 1):
        print(*map[r][0:N + 1])
    print("")

def print_micro(m): # for debug
    print(f"id {m.id}] ({m.minR}, {m.minC}) ~ ({m.maxR}, {m.maxC}) / size {m.size} [dead={dead[m.id]}]")

def print_micro_all(): # for debug
    for i in range(mcnt):
        print_micro(micro[i])

def insert(id, r1, c1, r2, c2):
    for r in range(r1, r2):
        for c in range(c1, c2):
            MAP[r][c] = id

def BFS(r, c):
    rp, wp = 0, 0
    
    queue[wp].r = r
    queue[wp].c = c    
    wp += 1
    
    visit[r][c] = True
    
    minR = maxR = r
    minC = maxC = c
    while rp < wp:
        out = queue[rp]
        rp += 1
        
        for i in range(4):
            nr = out.r + dr[i]
            nc = out.c + dc[i]
            
            if MAP[out.r][out.c] != MAP[nr][nc] or visit[nr][nc]: continue
            
            queue[wp].r = nr
            queue[wp].c = nc
            wp += 1
            
            visit[nr][nc] = True
            
            minR = min(minR, nr)
            maxR = max(maxR, nr)
            minC = min(minC, nc)
            maxC = max(maxC, nc)
            
    return MICRO(MAP[r][c], minR, minC, maxR, maxC, wp)

def find_live_micro():
    global mcnt
    
    mcnt = 0
    for r in range(N):
        for c in range(N):
            visit[r][c] = False

    check = [False] * MAX_Q
    for r in range(N):
        for c in range(N):
            id = MAP[r][c]
            if id == 0 or dead[id] or visit[r][c]: continue
            
            m = BFS(r, c)
            
            if check[id]:
                dead[id] = True
                continue
            
            check[id] = True
            micro[mcnt] = m
            mcnt += 1

    tcnt = mcnt
	
    mcnt = 0
    for i in range(tcnt):
        if dead[micro[i].id] == True: continue
        
        micro[mcnt] = micro[i]
        mcnt += 1
 
def is_priority(a, b):
    if a.size != b.size: return a.size > b.size
    return a.id < b.id

def sort_micro():
    for i in range(mcnt - 1):
        for k in range(i + 1, mcnt):
            if is_priority(micro[i], micro[k]) == False:
                micro[i], micro[k] = micro[k], micro[i]

def check_move(newMAP, m, fr, fc):
    sr, sc = m.minR, m.minC
    er, ec = m.maxR, m.maxC
    
    for r in range(sr, er + 1):
        for c in range(sc, ec + 1):
            # 미생물 사각형 범위에 다른 미생물 or 비어있는 경우
            if MAP[r][c] != m.id or MAP[r][c] == 0: continue
            
            newR = fr - sr + r
            newC = fc - sc + c
            
            # 격자 밖을 넘어가는 경우
            if newR >= N or newC >= N: return False
            
            # 새 용기에 이미 다른 미생물이 있는 경우
            if newMAP[newR][newC] != 0: return False
            
    return True

def move(newMAP, m, fr, fc):
    sr, sc = m.minR, m.minC
    er, ec = m.maxR, m.maxC
    
    for r in range(sr, er + 1):
        for c in range(sc, ec + 1):
            
            # 미생물 사각형 범위에 다른 미생물 or 비어있는 경우
            if MAP[r][c] != m.id or MAP[r][c] == 0: continue
            
            newR = fr - sr + r
            newC = fc - sc + c
            
            newMAP[newR][newC] = m.id

def move_micro(newMAP, m):
    for r in range(N):
        for c in range(N):
            if check_move(newMAP, m, r, c) == True:
                move(newMAP, m, r, c)
                return

def move_all():
    newMAP = [[0] * MAX for _ in range(MAX)]
    
    for i in range(mcnt):
        move_micro(newMAP, micro[i])
        
    for r in range(N):
        for c in range(N):
            MAP[r][c] = newMAP[r][c]

def get_size(id):
    for i in range(mcnt):
        if micro[i].id == id: return micro[i].size
        
    return -1

def get_score(maxID):
    company = [[False] * MAX_Q for _ in range(MAX_Q)]
    for r in range(N):
        for c in range(N):
            if MAP[r][c] == 0: continue
            
            for i in range(4):
                nr = r + dr[i]
                nc = c + dc[i]
                
                id1 = MAP[r][c]
                id2 = MAP[nr][nc]
                
                if id1 == id2 or id2 == 0: continue
                
                company[id1][id2] = True
                company[id2][id1] = True
                
    score = 0
    for i in range(1, maxID):
        for k in range(i + 1, maxID + 1):
            if company[i][k] == False: continue            
            
            size1 = get_size(i)
            size2 = get_size(k)
            
            score += (size1 * size2)
            
    return score

def simulate():
    for id in range(1, Q + 1):
        r1, c1, r2, c2 = query[id].r1, query[id].c1, query[id].r2, query[id].c2
        
        # 미생물 투입
        insert(id, r1, c1, r2, c2)
        
        # 배양 용기 이동
        find_live_micro()
        sort_micro()
        move_all()
        
        # 실험 결과 기록
        print(get_score(id))

# T = int(input())
T = 1
for tc in range(T):  
    input_data()
        
    simulate()