import copy

MAX_N = 50 + 5
MAX_M = 100 + 10

MAP = [[0] * MAX_N for _ in range(MAX_N)]
D = [0] * MAX_M
P = [0] * MAX_M

class RC:
    def __init__(self, r: int, c: int):
        self.r = r
        self.c = c

supplement = [RC(0, 0) for _ in range(MAX_N * MAX_N)]
scnt = 0

# ↖, ↗, ↘, ↙
dr4 = [-1, -1, 1, 1]
dc4 = [-1, 1, 1, -1]

# -, →, ↗, ↑, ↖, ←, ↙, ↓, ↘
dr8 = [0, 0, -1, -1, -1, 0, 1, 1, 1]
dc8 = [0, 1, 1, 0, -1, -1, -1, 0, 1]

def input_data():
    global N, M, MAP, scnt
    
    N, M = map(int, input().split())

    MAP = [[0] * MAX_N for _ in range(MAX_N)]

    for r in range(1, N + 1):
        MAP[r][1:N + 1] = map(int, input().split())

    for m in range(M):
        D[m], P[m] = map(int, input().split())

    supplement[0].r, supplement[0].c = N, 1
    supplement[1].r, supplement[1].c = N, 2
    supplement[2].r, supplement[2].c = N - 1, 1
    supplement[3].r, supplement[3].c = N - 1, 2
        
    scnt = 4

def print_map(): # for debug
    for r in range(1, N + 1):
        print(*MAP[r][1:N + 1])
    print("")

def move_supplement(dir, size):
    global supplement
    
    for i in range(scnt):
        nr = supplement[i].r + dr8[dir] * (size % N)
        nc = supplement[i].c + dc8[dir] * (size % N)

        if nr > N: nr -= N
        if nc > N: nc -= N
        if nr < 1: nr += N
        if nc < 1: nc += N

        supplement[i].r = nr
        supplement[i].c = nc

def insert():
    for i in range(scnt):
        r, c = supplement[i].r, supplement[i].c
        MAP[r][c] += 1

def grow():
    for s in range(scnt):
        r, c = supplement[s].r, supplement[s].c
        
        count = 0
        for i in range(4):
            nr = r + dr4[i]
            nc = c + dc4[i]
            
            if MAP[nr][nc] > 0: count += 1
        
        MAP[r][c] += count

def check(r, c):
    for i in range(scnt):
        if supplement[i].r == r and supplement[i].c == c:
            return True
    
    return False

def make_supplement():
    global supplement, scnt
    
    tmp_supplement = [RC(0, 0) for _ in range(MAX_N * MAX_N)] 

    tcnt = 0
    for r in range(1, N + 1):
        for c in range(1, N + 1):
            if MAP[r][c] < 2: continue
            
            # 특수 영양제를 투입한 좌표
            if check(r, c) == True: continue
            
            MAP[r][c] -= 2
            
            tmp_supplement[tcnt].r = r
            tmp_supplement[tcnt].c = c
            tcnt += 1
            
    supplement = copy.deepcopy(tmp_supplement)
    scnt = tcnt

def simulate():
    for m in range(M):
        move_supplement(D[m], P[m])
        insert()
        grow()
        make_supplement()

def get_answer():
    sum = 0
    for r in range(1, N + 1):
        for c in range(1, N + 1):
            sum += MAP[r][c]
    
    return sum
        
# T = int(input())
T = 1
for tc in range(T):
    input_data()
    
    simulate()
    
    print(get_answer())
