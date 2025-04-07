MAX = 50 + 5

class ATOM:
    def __init__(self, r: int, c: int, m: int, s: int, d: int):
        self.r = r
        self.c = c
        self.m = m # 질량
        self.s = s # 속력
        self.d = d # 방향

atom = [ATOM(0, 0, 0, 0, 0) for _ in range(100000 + 5000)]
acnt = 0

# ↑, ↗, →, ↘, ↓, ↙, ←, ↖
dr = [-1, -1, 0, 1, 1, 1, 0, -1]
dc = [0, 1, 1, 1, 0, -1, -1, -1]

class INFO:
    def __init__(self, m: int, s: int, d: int, even: int, odd: int, count: int):
        self.m = 0 # 질량
        self.s = 0 # 속력
        self.d = 0 # 방향
        self.even = 0 # 상하좌우
        self.odd = 0 # 대각선
        self.count = 0 # 원자의 개수

def input_data():
    global N, M, K, atom, acnt
    
    N, M, K = map(int, input().split())
    
    acnt = 0
    for _ in range(M):
        r, c, m, s, d = map(int, input().split())
        
        atom[acnt] = ATOM(r, c, m, s, d)
        acnt += 1

def print_atom(): # for debug
    for i in range(acnt):
        print(atom[i].r, atom[i].c, atom[i].m, atom[i].s, atom[i].d, end=' ')
    print("")

def simulate():
    global atom, acnt
    
    for _ in range(K):
        MAP = [[INFO(0, 0, 0, 0, 0, 0) for _ in range(MAX)] for _ in range(MAX)]

        # 1. 원자는 자신의 속력만큼 이동
        for i in range(acnt):
            d = atom[i].d
            s = atom[i].s
            m = atom[i].m

            nr = atom[i].r + dr[d] * (s % N)
            nc = atom[i].c + dc[d] * (s % N)
            
            if nr > N: nr -= N
            if nc > N: nc -= N
            if nr < 1: nr += N
            if nc < 1: nc += N
            
            # 2. 합성
            MAP[nr][nc].m += m
            MAP[nr][nc].s += s
            MAP[nr][nc].d = d # 원자가 1개인 경우 유효
            
            if d % 2 == 0: MAP[nr][nc].even += 1
            else: MAP[nr][nc].odd += 1
            
            MAP[nr][nc].count += 1

        # MAP을 보고 atom 배열 생성
        acnt = 0
        for r in range(1, N + 1):
            for c in range(1, N + 1):
                if MAP[r][c].count == 0: continue
                
                if MAP[r][c].count == 1:
                    atom[acnt] = ATOM(r, c, MAP[r][c].m, MAP[r][c].s, MAP[r][c].d)
                    acnt += 1                    
                    continue
                
                # 2.d 질량이 0인 원자는 소멸
                if MAP[r][c].m // 5 == 0: continue
                
                # 2.b 합쳐진 원자는 4개의 원자로 분해
                dir = [0, 0, 0, 0]
                if MAP[r][c].even == MAP[r][c].count \
                    or MAP[r][c].odd == MAP[r][c].count:
                    dir = [0, 2, 4, 6]
                else:
                    dir = [1, 3, 5, 7]
                
                for i in range(4):
                    atom[acnt] = ATOM(r, c, MAP[r][c].m // 5, MAP[r][c].s // MAP[r][c].count, dir[i])
                    acnt += 1

def get_answer():
    sum = 0
    for i in range(acnt):
        sum += atom[i].m
    
    return sum

# T = int(input())
T = 1
for _ in range(T):     
    input_data()     
    
    simulate()
    
    print(get_answer())