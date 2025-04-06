import copy

MAX = 100 + 5

MAP = [[0] * MAX for _ in range(MAX)]  # 나무
snail = [[0] * MAX for _ in range(MAX)]


class PERSON:
    def __init__(self, r: int, c: int, dir: int, dead: bool):
        self.r = r
        self.c = c
        self.dir = dir        
        self.dead = dead

runner = [PERSON(0, 0, 0, False) for _ in range(MAX * MAX)]
rcnt = 0

tagger_info = [PERSON(0, 0, 0, False) for _ in range(MAX * MAX * 2)]
tcnt = 0

# ↑, →, ↓, ←
dr = [-1, 0, 1, 0]
dc = [0, 1, 0, -1]

def input_data():
    global N, M, H, K, rcnt, tcnt, runner, MAP
    
    N, M, H, K = map(int, input().split())

    rcnt, tcnt = 0, 0

	# runner
    for _ in range(M):
        r, c, d = map(int, input().split())
        
        runner[rcnt].dead = False
        
        runner[rcnt].r = r
        runner[rcnt].c = c
        
        runner[rcnt].dir = d
        
        rcnt += 1
        
        
	# MAP init
    MAP = [[0] * MAX for _ in range(MAX)]

    for _ in range(H):
        r, c = map(int, input().split())
        MAP[r][c] = 1

def print_map(map): # for debug
    for r in range(1, N + 1):
        print(*map[r][1:N + 1])
    print("")

def make_snail():
    global tcnt, tagger_info, snail
    
    sr = sc = (N + 1) // 2
    direction = 0
    index = 1
    size = 0

    snail[sr][sc] = index
    index += 1

    tagger_info[tcnt].r = sr
    tagger_info[tcnt].c = sc
    tcnt += 1

    for i in range(2 * N - 1):
        if i % 2 == 0: size += 1

        for s in range(size):
            nr = sr + dr[direction]
            nc = sc + dc[direction]

            snail[nr][nc] = index
            index += 1

            sr, sc = nr, nc

            tagger_info[tcnt].r = nr
            tagger_info[tcnt].c = nc            
            tcnt += 1

        direction += 1
        
        if direction == 4: direction = 0

    tcnt = N * N
    for i in range(tcnt):
        tagger_info[tcnt + i] = copy.deepcopy(tagger_info[tcnt - i - 2])
        
    tcnt = 2 * N * N - 2

    for i in range(tcnt - 1):
        r, c = tagger_info[i].r, tagger_info[i].c
        nr, nc = tagger_info[i + 1].r, tagger_info[i + 1].c

        if nr - r == -1: tagger_info[i].dir = 0 # 위
        elif nr - r == 1: tagger_info[i].dir = 2 # 아래
        elif nc - c == 1: tagger_info[i].dir = 1 # 오른쪽
        elif nc - c == -1: tagger_info[i].dir = 3 # 왼쪽

    tagger_info[tcnt - 1].dir = 0

def get_distance(r1, c1, r2, c2):
    return abs(r1 - r2) + abs(c1 - c2)

def move_runner(k):
    tagger = tagger_info[k % tcnt]
    changeDir = [2, 3, 0, 1]

    for i in range(rcnt):
        if runner[i].dead: continue

        sr, sc = runner[i].r, runner[i].c
        distance = get_distance(tagger.r, tagger.c, sr, sc)

        if distance > 3: continue

        dir = runner[i].dir
        
        nr = sr + dr[dir]
        nc = sc + dc[dir]

        if nr < 1 or nc < 1 or nr > N or nc > N:
            dir = changeDir[dir]
            runner[i].dir = dir
            
            nr = sr + dr[dir]
            nc = sc + dc[dir]

        if nr == tagger.r and nc == tagger.c: continue

        runner[i].r, runner[i].c = nr, nc

def move_tagger(k):
    tagger = tagger_info[(k + 1) % tcnt]
    
    catch_count = 0
    for d in range(3):
        nr = tagger.r + dr[tagger.dir] * d
        nc = tagger.c + dc[tagger.dir] * d

        if nr < 1 or nc < 1 or nr > N or nc > N: break
        if MAP[nr][nc] == 1: continue # 나무

        for i in range(rcnt):
            if runner[i].dead == True: continue
            
            if runner[i].r == nr and runner[i].c == nc:
                runner[i].dead = True
                catch_count += 1

    return catch_count * (k + 1)

def simulate():
    score = 0
    for k in range(K):
        move_runner(k)        
        score += move_tagger(k)
        
    return score

# T = int(input())
T = 1
for tc in range(T):    
    input_data()
    
    make_snail()
    
    print(simulate())