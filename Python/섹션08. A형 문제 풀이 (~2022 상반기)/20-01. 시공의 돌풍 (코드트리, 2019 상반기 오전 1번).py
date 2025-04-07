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

def rotate_step(sr, sc, n, m, rotate_count):
    er = sr + n - 1
    ec = sc + m - 1

    tmp_map = copy.deepcopy(MAP)

    index = 0
    for c in range(sc, ec + 1):
        arr[index].r = sr
        arr[index].c = c
        index += 1
    for r in range(sr + 1, er + 1):
        arr[index].r = r
        arr[index].c = ec
        index += 1
    for c in range(ec - 1, sc - 1, -1):
        arr[index].r = er
        arr[index].c = c
        index += 1
    for r in range(er - 1, sr, -1):
        arr[index].r = r
        arr[index].c = sc
        index += 1

    for i in range(index):
        new_index = (i - rotate_count) % index
        
        front = arr[new_index]
        
        MAP[front.r][front.c] = tmp_map[arr[i].r][arr[i].c]

def cleaning():
    up_r = tornado[0].r
    down_r = tornado[1].r

    rotate_step(1, 1, up_r, M, 1)
    MAP[up_r][1] = TORNADO_POSITION
    MAP[up_r][2] = 0

    rotate_step(down_r, 1, N - down_r + 1, M, -1)
    MAP[down_r][1] = TORNADO_POSITION
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