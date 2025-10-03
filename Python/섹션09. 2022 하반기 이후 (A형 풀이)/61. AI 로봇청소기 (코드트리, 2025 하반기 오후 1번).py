MAX = 30 + 5
WALL = -1 # 물건
INF = 0x7fff0000

MAP = [[0] * MAX for _ in range(MAX)] 
check = [[False] * MAX for _ in range(MAX)] # 청소기 좌표

class RC:
    def __init__(self, r: int, c: int):
        self.r = r
        self.c = c

cleaner = [RC(0, 0) for _ in range(50 + 5)]
queue = [RC(0, 0) for _ in range(MAX * MAX)]

# →, ↓, ←, ↑
dr = [0, 1, 0, -1]
dc = [1, 0, -1, 0]

def input_data():
    global N, K, L

    N, K, L = map(int, input().split())
                
    for r in range(0, N + 2):
        for c in range(0, N + 2):
            MAP[r][c] = -1

    for r in range(1, N + 1):
        MAP[r][1:N + 1] = list(map(int, input().split()))

    for k in range(1, K + 1):
        r, c = map(int, input().split())
        cleaner[k].r = r
        cleaner[k].c = c

def print_map(): # for debug
    for k in range(1, K + 1):
        print(f"{k}] {cleaner[k].r}, {cleaner[k].c}")
    print()

    for r in range(1, N + 1):
        print(*MAP[r][1:N + 1])
    print()   

def get_position(index):
    ret = RC(INF, INF)
    visit = [[0] * MAX for _ in range(MAX)]
    rp = wp = 0

    sr, sc = cleaner[index].r, cleaner[index].c
    if MAP[sr][sc] > 0:
        return RC(sr, sc)

    queue[wp] = RC(sr, sc); wp += 1
    visit[sr][sc] = 1

    min_distance = INF
    while rp < wp:
        out = queue[rp]; rp += 1

        if MAP[out.r][out.c] > 0 and not check[out.r][out.c]:
            if visit[out.r][out.c] < min_distance:
                min_distance = visit[out.r][out.c]
                ret = RC(out.r, out.c)
            elif visit[out.r][out.c] == min_distance:
                if (out.r < ret.r) or (out.r == ret.r and out.c < ret.c):
                    ret = RC(out.r, out.c)
            continue

        for i in range(4):
            nr, nc = out.r + dr[i], out.c + dc[i]
            if MAP[nr][nc] == WALL or check[nr][nc] or visit[nr][nc] != 0:
                continue
            queue[wp] = RC(nr, nc); wp += 1
            visit[nr][nc] = visit[out.r][out.c] + 1

    if ret.r == INF:
        return RC(sr, sc)
    return ret

def get_direction(index):
    target = cleaner[index]
    total = min(MAP[target.r][target.c], 20)

    for i in range(4):
        nr, nc = target.r + dr[i], target.c + dc[i]
        if MAP[nr][nc] != WALL:
            total += min(MAP[nr][nc], 20)

    max_dir = -1
    max_dust = -1
    change_dir = [2, 3, 0, 1]

    for i in range(4):
        reverse = change_dir[i]
        nr, nc = target.r + dr[reverse], target.c + dc[reverse]
        dust = total
        if MAP[nr][nc] != WALL:
            dust -= min(MAP[nr][nc], 20)
        if max_dust < dust:
            max_dust = dust
            max_dir = i

    return max_dir

def clean(index):
    change_dir = [2, 3, 0, 1]
    target = cleaner[index]
    direction = get_direction(index)
    reverse = change_dir[direction]

    for i in range(4):
        if i == reverse:
            continue
        nr, nc = target.r + dr[i], target.c + dc[i]
        if MAP[nr][nc] == WALL:
            continue
        MAP[nr][nc] = max(0, MAP[nr][nc] - 20)

    MAP[target.r][target.c] = max(0, MAP[target.r][target.c] - 20)

def add_dust():
    for r in range(1, N + 1):
        for c in range(1, N + 1):
            if MAP[r][c] not in (0, WALL):
                MAP[r][c] += 5

def spread_dust():
    tmpMAP = [[0] * MAX for _ in range(MAX)]
    for r in range(1, N + 1):
        for c in range(1, N + 1):
            if MAP[r][c] != 0:
                continue
            s = 0
            for i in range(4):
                nr, nc = r + dr[i], c + dc[i]
                if MAP[nr][nc] == WALL:
                    continue
                s += MAP[nr][nc]
            tmpMAP[r][c] = s // 10

    for r in range(1, N + 1):
        for c in range(1, N + 1):
            MAP[r][c] += tmpMAP[r][c]

def get_dust():
    sum = 0
    for r in range(1, N + 1):
        for c in range(1, N + 1):
            if MAP[r][c] == WALL: continue
            sum += MAP[r][c]
    
    return sum

def simulate():
    for _ in range(L):
        for r in range(1, N + 1):
            for c in range(1, N + 1):
                check[r][c] = False # 청소기 좌표 초기화

        # 0. 현재 청소기 좌표 체크
        for k in range(1, K + 1):
            check[cleaner[k].r][cleaner[k].c] = True

        # 1. 청소기 이동
        for k in range(1, K + 1):
            rc = get_position(k)
            check[cleaner[k].r][cleaner[k].c] = False
            cleaner[k].r, cleaner[k].c = rc.r, rc.c
            check[cleaner[k].r][cleaner[k].c] = True

        # 2. 청소
        for k in range(1, K + 1): clean(k)

        # 3. 먼지 축적
        add_dust()
        
        # 4. 먼지 확산
        spread_dust()

        # 5. 출력
        print(get_dust())
                   
# T = int(input())
T = 1
for tc in range(T):  
    input_data()
        
    simulate()