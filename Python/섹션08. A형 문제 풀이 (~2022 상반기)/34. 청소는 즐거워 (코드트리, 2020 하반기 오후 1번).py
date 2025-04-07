
MAX = 500 + 20

MAP = [[0] * MAX for _ in range(MAX)]
snail = [[0] * MAX for _ in range(MAX)]

class RCD:
    def __init__(self, r: int, c: int, dir: int):
        self.r = r
        self.c = c
        self.dir = dir

track = [RCD(0, 0, 0) for _ in range(MAX * MAX)]
tcnt = 0

# ←, ↓, →, ↑
dr = [0, 1, 0, -1]
dc = [-1, 0, 1, 0]

def input_data():
    global N
    
    N = int(input())
    
    for r in range(1, N + 1):
        MAP[r][1:N + 1] = map(int, input().split())

def print_map(map):
    for r in range(1, N + 1):
        print(*map[r][1:N + 1])
    print()

# ←, ↓, →, ↑
ratio = [
    [
        [0,  0, 2, 0, 0],
        [0, 10, 7, 1, 0],
        [5,  0, 0, 0, 0],
        [0, 10, 7, 1, 0],
        [0,  0, 2, 0, 0],
    ],
    [
        [0,  0, 0,  0, 0],
        [0,  1, 0,  1, 0],
        [2,  7, 0,  7, 2],
        [0, 10, 0, 10, 0],
        [0,  0, 5,  0, 0],
    ],
    [
        [0, 0, 2,  0, 0],
        [0, 1, 7, 10, 0],
        [0, 0, 0,  0, 5],
        [0, 1, 7, 10, 0],
        [0, 0, 2,  0, 0],
    ],
    [
        [0,  0, 5,  0, 0],
        [0, 10, 0, 10, 0],
        [2,  7, 0,  7, 2],
        [0,  1, 0,  1, 0],
        [0,  0, 0,  0, 0],
    ]
]

def make_snail():
    global tcnt
    
    sr = sc = (N + 1) // 2
    direction = 0
    index = 1
    size = 0

    snail[sr][sc] = index
    index += 1
    
    track[tcnt].r = sr
    track[tcnt].c = sc    
    tcnt += 1

    for i in range(2 * N - 1):
        if i % 2 == 0: size += 1
        
        for s in range(size):
            nr = sr + dr[direction]
            nc = sc + dc[direction]
            
            snail[nr][nc] = index
            index += 1
            
            sr, sc = nr, nc
            
            track[tcnt].r = nr
            track[tcnt].c = nc
            tcnt += 1
    
        direction += 1
        if direction == 4: direction = 0
    
    tcnt = N * N
    for i in range(tcnt - 1):
        r, c = track[i].r, track[i].c
        nr, nc = track[i + 1].r, track[i + 1].c
        
        if nc - c == -1: track[i].dir = 0 # 왼쪽
        elif nc - c == 1: track[i].dir = 2 # 오른쪽
        elif nr - r == -1: track[i].dir = 3 # 위쪽
        elif nr - r == 1: track[i].dir = 1 # 아래쪽
    
    track[tcnt - 1].dir = 0

def clean(sr, sc, dir):
    center = MAP[sr][sc]
    tmp_map = [[0] * 5 for _ in range(5)]

    for r in range(5):
        for c in range(5):
            tr = sr + r - 2
            tc = sc + c - 2
            
            dust = center * ratio[dir][r][c] // 100
            
            tmp_map[r][c] = dust
            MAP[sr][sc] -= dust

    tmp_map[2 + dr[dir]][2 + dc[dir]] = MAP[sr][sc]
    MAP[sr][sc] = 0

    ret = 0
    for r in range(5):
        for c in range(5):
            tr = sr + r - 2
            tc = sc + c - 2
            
            if tr < 1 or tc < 1 or tr > N or tc > N: ret += tmp_map[r][c]
            else: MAP[tr][tc] += tmp_map[r][c]

    return ret

def simulate():
    out_dust = 0
    for i in range(tcnt - 1):
        r = track[i + 1].r
        c = track[i + 1].c
        dir = track[i].dir
        
        out_dust += clean(r, c, dir)
        
    return out_dust

# T = int(input())
T = 1
for tc in range(T):
    input_data()
    
    make_snail()
    
    print(simulate())