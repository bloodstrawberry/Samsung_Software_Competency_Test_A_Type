import copy

MAX = 10 + 5
INF = 0x7fff0000

BROKEN = 0

MAP = [[0] * MAX for _ in range(MAX)]
tmpMAP = [[0] * MAX for _ in range(MAX)]

class RC:
    def __init__(self, r: int, c: int):
        self.r = r
        self.c = c

queue = [RC(0, 0) for _ in range(MAX * MAX)]

attackTime = [[0] * MAX for _ in range(MAX)]

# →, ↓, ←, ↑ 
dr4 = [0, 1, 0, -1]
dc4 = [1, 0, -1, 0]

# ←, ↖, ↑, ↗, →, ↘, ↓, ↙ 
dr8 = [0, -1, -1, -1, 0, 1, 1, 1]
dc8 = [-1, -1, 0, 1, 1, 1, 0, -1]

def input_data():   
    global N, M, K, MAP, attackTime
    
    N, M, K = map(int, input().split())
        
    for r in range(1, N + 1):
        MAP[r][1:M + 1] = map(int, input().split())
    
    # 시점 0에서 모두 공격
    attackTime = [[0] * MAX for _ in range(MAX)]
        
def print_map(): # for debug
    for r in range(1, N + 1):
        print(*MAP[r][1:M + 1])
    print("")
    
# a가 더 약하면 true
def is_weak(a, b):
	if MAP[a.r][a.c] != MAP[b.r][b.c]:
		return MAP[a.r][a.c] < MAP[b.r][b.c]

	timeA = attackTime[a.r][a.c]
	timeB = attackTime[b.r][b.c]
	if timeA != timeB: return timeA > timeB

	sumA = a.r + a.c
	sumB = b.r + b.c
	if sumA != sumB: return sumA > sumB

	return a.c > b.c

def get_weakest_tower():
    ret = RC(0, 0)
    
    MAP[0][0] = INF # 최악의 값
    for r in range(1, N + 1):
        for c in range(1, M + 1):
            if MAP[r][c] == BROKEN: continue
            
            tmp = RC(r, c)
            if is_weak(tmp, ret) == True:
                ret = RC(tmp.r, tmp.c)
    
    return ret
       
def get_strongest_tower(attacker):
    ret = RC(0, 0)
    
    MAP[0][0] = 0 # 최악의 값
    for r in range(1, N + 1):
        for c in range(1, M + 1):
            if attacker.r == r and attacker.c == c: continue
            if MAP[r][c] == BROKEN: continue
            
            tmp = RC(r, c)
            if is_weak(tmp, ret) == False:
                ret = RC(tmp.r, tmp.c)
    
    return ret     
            
def BFS(start, end): 
    visit = [[0] * MAX for _ in range(MAX)]
    before = [[RC(0, 0) for _ in range(MAX)] for _ in range(MAX)]
    
    rp = wp = 0
    
    sr = start.r
    sc = start.c
    er = end.r
    ec = end.c
    
    queue[wp].r = sr
    queue[wp].c = sc
    wp += 1
    
    visit[sr][sc] = 1
    
    before[sr][sc].r = -1
    before[sr][sc].c = -1
    
    while rp < wp:
        out = queue[rp]
        rp += 1
        
        if out.r == end.r and out.c == end.c:
            power = MAP[sr][sc]
            
            tr, tc = out.r, out.c
            
            MAP[tr][tc] -= power
            
            while True:
                br, bc = before[tr][tc].r, before[tr][tc].c
                
                if br == sr and bc == sc: break
                
                MAP[br][bc] -= (power // 2)
                
                tr, tc = br, bc
            
            return True
        
        for i in range(4):
            nr = (((out.r + dr4[i] + N) - 1) % N) + 1
            nc = (((out.c + dc4[i] + M) - 1) % M) + 1
            
            if MAP[nr][nc] == BROKEN or visit[nr][nc] != 0: continue
            
            queue[wp].r = nr
            queue[wp].c = nc
            wp += 1
            
            visit[nr][nc] = visit[out.r][out.c] + 1
            
            before[nr][nc] = RC(out.r, out.c)
            
    return False
    
def attack(attacker, target, time):
    attackTime[attacker.r][attacker.c] = time
    
    # laser
    if BFS(attacker, target) == True: return
    
    # 포탄
    sr = attacker.r
    sc = attacker.c
    er = target.r
    ec = target.c
    
    power = MAP[sr][sc]
    
    MAP[er][ec] -= power
    
    for i in range(8):
        nr = (((er + dr8[i] + N) - 1) % N) + 1
        nc = (((ec + dc8[i] + M) - 1) % M) + 1
        
        if MAP[nr][nc] == BROKEN: continue
        if nr == sr and nc == sc: continue # 공격자는 영향 x
        
        MAP[nr][nc] -= (power // 2)
    
def set_broken_tower():
    for r in range(1, N + 1):
    	for c in range(1, M + 1):
         	if MAP[r][c] < 0: MAP[r][c] = BROKEN

def maintain_tower():
    for r in range(1, N + 1):
        for c in range(1, M + 1):
            if MAP[r][c] == BROKEN: continue
            if tmpMAP[r][c] != MAP[r][c]: continue
            
            MAP[r][c] += 1
            
def simulate():
    global tmpMAP
    
    for k in range(1, K + 1):
        # 0. 현재 상태 저장
        tmpMAP = copy.deepcopy(MAP)
        
        # 1. 공격자 선정
        attacker = get_weakest_tower()
        
        # 2. 공격자의 공격
        # 2-1. target 탐색
        target = get_strongest_tower(attacker)
        
        # 2-2. target이 없는 경우
        if target.r == 0 and target.c == 0: break
        
        # 2-3. target 공격
        MAP[attacker.r][attacker.c] += (N + M)
        attack(attacker, target, k)
        
        # 3. 포탑 부서짐
        set_broken_tower()
        
        # 4. 포탑 정비
        maintain_tower()
    
def get_answer():
    max = 0
    for r in range(1, N + 1):
        for c in range(1, M + 1):
            if max < MAP[r][c]: max = MAP[r][c]
            
    return max
        
# T = int(input())
T = 1
for tc in range(T):    
    input_data()
    
    simulate()
    
    print(get_answer())