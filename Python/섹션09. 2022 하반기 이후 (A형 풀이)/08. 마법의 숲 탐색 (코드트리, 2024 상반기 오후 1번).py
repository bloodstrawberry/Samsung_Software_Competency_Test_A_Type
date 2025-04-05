MAX = 70 + 10
MAX_K = 1000 + 10

BODY = 1
CENTER = 2
EXIT = 3
GOLEM_ID = 10

MAP = [[0] * MAX for _ in range(MAX)]
start_c = [0] * MAX_K
exid_d = [0] * MAX_K

class RC:
    def __init__(self, r: int, c: int):
        self.r = r
        self.c = c

queue = [RC(0, 0) for _ in range(MAX * MAX)]

class GOLEM:
    def __init__(self, r: int, c: int, dir: int, id: int):
        self.r = r
        self.c = c
        self.dir = dir
        self.id = id
        
# ↑, →, ↓, ←
dr = [-1, 0, 1, 0]
dc = [0, 1, 0, -1]

def input_data():   
    global R, C, K, MAP
    
    R, C, K = map(int, input().split())
    
    MAP = [[0] * MAX for _ in range(MAX)]
        
    for k in range(1, K + 1):
        start_c[k], exid_d[k] = map(int, input().split())
            
def print_map(): # for debug
    for r in range(3, R + 3):
        print(' '.join('%2d' % num for num in MAP[r][1:C + 1]))
    print("")
    
# 남쪽    
def check_south(golem):
    gr, gc = golem.r, golem.c

    if gr == R + 1: return False

    nr = [gr + 1, gr + 2, gr + 1]
    nc = [gc - 1, gc, gc + 1]

    for i in range(3):
        if MAP[nr[i]][nc[i]] != 0: return False

    return True

# 서쪽 + 남쪽
def check_west(golem):
    gr, gc = golem.r, golem.c

    if gc == 2: return False

    nr = [gr - 1, gr, gr + 1]
    nc = [gc - 1, gc - 2, gc - 1]

    for i in range(3):
        if MAP[nr[i]][nc[i]] != 0: return False

    tmp_golem = GOLEM(gr, gc - 1, 0, 0)
    
    return check_south(tmp_golem)

# 서쪽 + 동쪽
def check_east(golem):
    gr, gc = golem.r, golem.c

    if gc == C - 1: return False

    nr = [gr - 1, gr, gr + 1]
    nc = [gc + 1, gc + 2, gc + 1]

    for i in range(3):
        if MAP[nr[i]][nc[i]] != 0: return False

    tmp_golem = GOLEM(gr, gc + 1, 0, 0)
    
    return check_south(tmp_golem)

def set_golem(golem):
    gr, gc, gid, dir = golem.r, golem.c, golem.id, golem.dir

    MAP[gr][gc] = CENTER + gid

    for i in range(4):
        nr = gr + dr[i]
        nc = gc + dc[i]
        
        MAP[nr][nc] = BODY + gid

    MAP[gr + dr[dir]][gc + dc[dir]] = EXIT + gid   
    
def BFS(golem):
    rp, wp = 0, 0
    visit = [[0] * MAX for _ in range(MAX)]
    
    queue[wp].r = golem.r
    queue[wp].c = golem.c
    wp += 1
    
    visit[golem.r][golem.c] = True
    
    max_r = 0
    while rp < wp:
        out = queue[rp]
        rp += 1
        
        if max_r < out.r: max_r = out.r
        
        golem_id = (MAP[out.r][out.c] // GOLEM_ID) * GOLEM_ID
        type = MAP[out.r][out.c] % GOLEM_ID
        
        for i in range(4):
            nr = out.r + dr[i]
            nc = out.c + dc[i]
            
            if nr < 1 or nc < 1 or nr > (R + 2) or nc > C: continue 
            if MAP[nr][nc] == 0 or visit[nr][nc] == True: continue
            
            n_golem_id = (MAP[nr][nc] // GOLEM_ID) * GOLEM_ID
            
            # 뽑은 좌표의 타입이 출구가 아니고
            # 다음 좌표의 ID가 다른 경우
            if type != EXIT and golem_id != n_golem_id: continue
            
            queue[wp].r = nr
            queue[wp].c = nc
            wp += 1
            
            visit[nr][nc] = True
    
    return max_r - 2

def simulate(golem):
    global MAP
    
    g = golem

    while True:
        if check_south(g): g.r += 1
        elif check_west(g):  # 서쪽 + 남쪽
            g.r += 1
            g.c -= 1
            g.dir = (g.dir - 1 + 4) % 4
        elif check_east(g):  # 동쪽 + 남쪽
            g.r += 1
            g.c += 1
            g.dir = (g.dir + 1) % 4
        else:
            break

    if g.r <= 3:
        MAP = [[0] * MAX for _ in range(MAX)]        
        return 0

    set_golem(g)

    return BFS(g)

# T = int(input())
T = 1
for tc in range(T):    
    input_data()
    
    sum = 0
    for k in range(1, K + 1):
        g = GOLEM(1, start_c[k], exid_d[k], k * GOLEM_ID)
        
        row = simulate(g)
        
        # print_map()
        
        sum += row
    
    print(sum)