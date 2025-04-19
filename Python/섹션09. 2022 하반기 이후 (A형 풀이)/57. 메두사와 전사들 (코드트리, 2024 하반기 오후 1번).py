MAX_N = 50 + 5
MAX_M = 300 + 30

WALL = 1

UP = 0
DOWN = 1
LEFT = 2
RIGHT = 3

STRAIGHT = 1

MAP = [[0] * MAX_N for _ in range(MAX_N)]
visit = [[0] * MAX_N for _ in range(MAX_N)]
scope = [[0] * MAX_N for _ in range(MAX_N)] # 메두사의 시선 처리

class RC:
    def __init__(self, r: int, c: int):
        self.r = r
        self.c = c

start = RC(0, 0)
end = RC(0, 0)
medusa = RC(0, 0)

queue = [RC(0, 0) for _ in range(MAX_N * MAX_N)]
before = [[RC(0, 0) for _ in range(MAX_N)] for _ in range(MAX_N)]
position = [RC(0, 0) for _ in range(MAX_N * MAX_N)] # 메두사의 경로
pcnt = 0 # 메두사의 경로 길이

class RCD:
    def __init__(self, r: int, c: int, dead: bool):
        self.r = r
        self.c = c
        self.dead = dead

warrior = [RCD(0, 0, 0) for _ in range(MAX_M)]

class ANSWER:
    def __init__(self, distance: int, stone: int, attack: int):
        self.distance = distance # 모든 전사가 이동한 거리의 합
        self.stone = stone # 메두사로 인해 돌이 된 전사의 수
        self.attack = attack # 메두사를 공격한 전사의 수

answer = ANSWER(0, 0, 0)

# ↑, ↓, ←, → (상, 하, 좌, 우)
dr = [-1, 1, 0, 0]
dc = [0, 0, -1, 1]

def input_data():   
    global N, M, start, end, pcnt
    
    N, M = map(int, input().split())
    sr, sc, er, ec = map(int, input().split())
    
    start = RC(sr + 1, sc + 1)
    end = RC(er + 1, ec + 1)
    
    pcnt = 0
    
    values = list(map(int, input().split()))
    
    for m in range(M):
        warrior[m].r = values[2 * m] + 1
        warrior[m].c = values[2 * m + 1] + 1
        warrior[m].dead = False
    
    for r in range(1, N + 1):
        MAP[r][1:N + 1] = map(int, input().split())
          
def print_map(map): # for debug
    for r in range(1, N + 1):
        print(*map[r][1:N + 1])
    print("")

def print_status(): # for debug
    tmp_map = [[0] * MAX_N for _ in range(MAX_N)]
    
    tmp_map[medusa.r][medusa.c] = -1
    
    for m in range(M):
        if warrior[m].dead == True: continue
        
        r, c = warrior[m].r, warrior[m].c
        
        tmp_map[r][c] = M
    
    print_map(tmp_map)

def BFS():
    global pcnt
    
    rp, wp = 0, 0
    
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

        if er == out.r and ec == out.c:
            tr, tc = er, ec
            
            position[pcnt].r = er
            position[pcnt].c = ec
            pcnt += 1
            
            while True:
                br, bc = before[tr][tc].r, before[tr][tc].c # 이전 좌표
                
                if br == sr and bc == sc: break
                
                position[pcnt].r = br
                position[pcnt].c = bc
                pcnt += 1
                
                tr, tc = br, bc
            
            for i in range(pcnt // 2):
                position[i], position[pcnt - 1 - i] = position[pcnt - 1 - i], position[i]
        
        for i in range(4):
            nr = out.r + dr[i]
            nc = out.c + dc[i]
            
            if nr < 1 or nc < 1 or nr > N or nc > N: continue
            if visit[nr][nc] != 0 or MAP[nr][nc] == WALL: continue
            
            queue[wp].r = nr
            queue[wp].c = nc
            wp += 1
            
            visit[nr][nc] = visit[out.r][out.c] + 1
            
            before[nr][nc] = RC(out.r, out.c)
        
def move_medusa(index):
    global medusa
    
    medusa = position[index]

    for m in range(M):
        if warrior[m].dead == True: continue

        wr, wc = warrior[m].r, warrior[m].c

        if wr == medusa.r and wc == medusa.c:
            warrior[m].dead = True

def straight(r, c, dir, value):
    sr, sc = r, c

    while True:
        nr = sr + dr[dir]
        nc = sc + dc[dir]

        if nr < 1 or nc < 1 or nr > N or nc > N: break

        scope[nr][nc] = value
        
        sr, sc = nr, nc

def diagonal(r, c, dir, n_dir, value):
    step = 1
    while True:
        sr = r + (dr[dir] + dr[n_dir]) * step
        sc = c + (dc[dir] + dc[n_dir]) * step

        if sr < 1 or sc < 1 or sr > N or sc > N: break

        scope[sr][sc] = value

        while True:
            nr = sr + dr[dir]
            nc = sc + dc[dir]

            if nr < 1 or nc < 1 or nr > N or nc > N: break

            scope[nr][nc] = value
            
            sr, sc = nr, nc

        step += 1

# ↑, ↓, ←, → (상, 하, 좌, 우 / 0, 1, 2, 3)     
def left_look(r, c, dir, value):
    change_dir = [2, 3, 1, 0]
    left_dir = change_dir[dir]
    
    diagonal(r, c, dir, left_dir, value)

def right_look(r, c, dir, value):
    change_dir = [3, 2, 0, 1]
    right_dir = change_dir[dir]
    
    diagonal(r, c, dir, right_dir, value)

def count_stone_warrior(dir):
    global scope
    
    scope = [[0] * MAX_N for _ in range(MAX_N)]

    mr, mc = medusa.r, medusa.c

    straight(mr, mc, dir, STRAIGHT)
    left_look(mr, mc, dir, LEFT)
    right_look(mr, mc, dir, RIGHT)

    for m in range(M):
        if warrior[m].dead == True: continue

        wr, wc = warrior[m].r, warrior[m].c

        if scope[wr][wc] == STRAIGHT: straight(wr, wc, dir, 0)
        elif scope[wr][wc] == LEFT:
            straight(wr, wc, dir, 0)
            left_look(wr, wc, dir, 0)
        elif scope[wr][wc] == RIGHT:
            straight(wr, wc, dir, 0)
            right_look(wr, wc, dir, 0)

    count = 0
    for m in range(M):
        if warrior[m].dead == True: continue

        wr, wc = warrior[m].r, warrior[m].c

        if scope[wr][wc] != 0: count += 1

    return count

def look_at():
    global answer
    
    max_count, max_dir = 0, 0
    for i in range(4):
        tmp = count_stone_warrior(i)
        if max_count < tmp:
            max_count = tmp
            max_dir = i

    count_stone_warrior(max_dir)
    
    answer.stone = max_count

def check_row(w):
    mr = medusa.r
    wr = w.r

    # mr > wr -> 메두사는 아래에
    # mr = wr -> 같은 행, 상하로 움직일 수 없음.
    # mr < wr -> 메두사는 위에
    return mr - wr

def check_col(w):
    mc = medusa.c
    wc = w.c

    # mc > wc -> 메두사는 오른쪽에
    # mc = wc -> 같은 열, 좌우로 움직일 수 없음.
    # mc < wc -> 메두사는 왼쪽에
    return mc - wc

def check_scope(w, dir):
    nr = w.r + dr[dir]
    nc = w.c + dc[dir]

    if scope[nr][nc] != 0: return False
    
    return True

def move_warrior(first):
    for m in range(M):
        w = warrior[m]

        if w.dead: continue
        if scope[w.r][w.c] != 0: continue

        up_down = check_row(w)
        left_right = check_col(w)

        direction = -1

        # 메두사를 향해서 이동하므로 격자의 바깥으로 나가지 않는다.
        if first == True:
            if up_down < 0 and check_scope(w, UP): direction = UP
            elif up_down > 0 and check_scope(w, DOWN): direction = DOWN
            elif left_right < 0 and check_scope(w, LEFT): direction = LEFT
            elif left_right > 0 and check_scope(w, RIGHT): direction = RIGHT
        else:
            if left_right < 0 and check_scope(w, LEFT): direction = LEFT
            elif left_right > 0 and check_scope(w, RIGHT): direction = RIGHT
            elif up_down < 0 and check_scope(w, UP): direction = UP
            elif up_down > 0 and check_scope(w, DOWN): direction = DOWN

        if direction == -1: continue

        nr = w.r + dr[direction]
        nc = w.c + dc[direction]

        warrior[m].r = nr
        warrior[m].c = nc

        answer.distance += 1

        if nr == medusa.r and nc == medusa.c:
            answer.attack += 1
            warrior[m].dead = True

def simulate():
    global answer
    
    if pcnt == 0:
        print(-1)
        return

    for p in range(pcnt - 1):
        answer = ANSWER(0, 0, 0)

        move_medusa(p)
        
        look_at()
        
        move_warrior(True)
        move_warrior(False)

        print(answer.distance, answer.stone, answer.attack)

    print(0)
                
# T = int(input())
T = 1
for tc in range(T):  
    input_data()
    
    BFS()
    
    simulate()