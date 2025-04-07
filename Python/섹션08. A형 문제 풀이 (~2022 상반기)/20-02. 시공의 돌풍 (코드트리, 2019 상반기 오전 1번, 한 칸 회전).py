import copy

MAX = 50 + 10
TORNADO_POSITION = -1

MAP = [[0] * MAX for _ in range(MAX)]

class RC:
    def __init__(self, r: int, c: int):
        self.r = r
        self.c = c

tornado = [RC(0, 0) for _ in range(2)]
tcnt = 0
arr = [RC(0, 0) for _ in range(MAX * MAX)]  # for rotate

# ↑, →, ↓, ←
dr = [-1, 0, 1, 0]
dc = [0, 1, 0, -1]

def input_data():
    global N, M, time, tornado, tcnt
    
    N, M, time = map(int, input().split())

    for r in range(1, N + 1):
        MAP[r][1:N + 1] = map(int, input().split())
        
    for r in range(1, N + 1):
        for c in range(1, M + 1):
            if MAP[r][c] == TORNADO_POSITION:
                tornado[tcnt].r = r
                tornado[tcnt].c = c
                tcnt += 1
                
def print_map():  # for debug
    for r in range(1, N + 1):
        print(MAP[r][1:M + 1])

def diffusion():
    tmp_map = [[0] * MAX for _ in range(MAX)]

    for r in range(1, N + 1):
        for c in range(1, M + 1):
            if MAP[r][c] <= 0: continue

            dust, count = 0, 0
            for i in range(4):
                nr = r + dr[i]
                nc = c + dc[i]

                if nr < 1 or nc < 1 or nr > N or nc > M: continue
                if MAP[nr][nc] == TORNADO_POSITION: continue

                dust = MAP[r][c] // 5
                
                tmp_map[nr][nc] += dust
                count += 1

            MAP[r][c] -= (dust * count)

    for r in range(1, N+1):
        for c in range(1, M+1):
            MAP[r][c] += tmp_map[r][c]

def cleaning():
    up_r = tornado[0].r
    down_r = tornado[1].r

    # (1, 1) ~ (up_r, M)의 반시계 방향 회전
    for r in range(up_r - 1, 1, -1): MAP[r][1] = MAP[r - 1][1]
    for c in range(1, M): MAP[1][c] = MAP[1][c + 1]
    for r in range(1, up_r): MAP[r][M] = MAP[r + 1][M]
    for c in range(M, 1, -1): MAP[up_r][c] = MAP[up_r][c - 1]

    MAP[up_r][2] = 0

    # (down_r, 1) ~ (N, M)의 시계 방향 회전
    for r in range(down_r + 1, N): MAP[r][1] = MAP[r + 1][1]
    for c in range(1, M): MAP[N][c] = MAP[N][c + 1]
    for r in range(N, down_r, -1): MAP[r][M] = MAP[r - 1][M]
    for c in range(M, 1, -1): MAP[down_r][c] = MAP[down_r][c - 1]

    MAP[down_r][2] = 0

def get_answer():
    sum = 0
    for r in range(1, N + 1):
        for c in range(1, M + 1):
            if MAP[r][c] != TORNADO_POSITION: sum += MAP[r][c]
            
    return sum

# T = int(input())
T = 1
for tc in range(T):    
    input_data()
    
    for t in range(time):
        diffusion()
        cleaning()
        # print_map()
    
    print(get_answer())