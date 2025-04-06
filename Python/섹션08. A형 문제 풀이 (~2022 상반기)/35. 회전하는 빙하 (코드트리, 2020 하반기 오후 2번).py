MAX = 64 + 5

MAP = [[0] * MAX for _ in range(MAX)]
tmpMAP = [[0] * MAX for _ in range(MAX)]
L = [0] * (1000 + 50)

visit = [[False] * MAX for _ in range(MAX)]

class RC:
    def __init__(self, r: int, c: int):
        self.r = r
        self.c = c

queue = [RC(0, 0) for _ in range(MAX * MAX)]

# ↑, →, ↓, ←
dr = [-1, 0, 1, 0]  
dc = [0, 1, 0, -1]

def input_data():
    global N, Q, MAP_SIZE
    
    N, Q = map(int, input().split())
    
    MAP_SIZE = 1 << N

    for r in range(1, MAP_SIZE + 1):
        MAP[r][1:MAP_SIZE + 1] = map(int, input().split())

    L[:Q] = map(int, input().split())

def print_map(): # for debug
    for r in range(1, MAP_SIZE + 1):
        print(*MAP[r][1:MAP_SIZE + 1])
    print("") 

def rotate(sr, sc, size):
    half = size // 2

    for r in range(size):
        for c in range(size):
            tmpMAP[r][c] = MAP[sr + r][sc + c]

    # 3 -> 1
    for r in range(half):
        for c in range(half):
            MAP[sr + r][sc + c] = tmpMAP[r + half][c]
    # 1 -> 2
    for r in range(half):
        for c in range(half):
            MAP[sr + r][sc + c + half] = tmpMAP[r][c]
    # 2 -> 4
    for r in range(half):
        for c in range(half):
            MAP[sr + r + half][sc + c + half] = tmpMAP[r][c + half]
    # 4 -> 3
    for r in range(half):
        for c in range(half):
            MAP[sr + r + half][sc + c] = tmpMAP[r + half][c + half]

def melt_ice():
    ICE = [[0] * MAX for _ in range(MAX)]

    for r in range(1, MAP_SIZE + 1):
        for c in range(1, MAP_SIZE + 1):
            if MAP[r][c] == 0: continue
            
            count = 0
            for i in range(4):
                nr = r + dr[i]
                nc = c + dc[i]
                
                if MAP[nr][nc] == 0: count += 1
                
            if count >= 2: ICE[r][c] = 1

    for r in range(1, MAP_SIZE + 1):
        for c in range(1, MAP_SIZE + 1):
            MAP[r][c] -= ICE[r][c]

def simulate():
    for q in range(Q):
        level = L[q]
        divide = 1 << level

        for r in range(1, MAP_SIZE + 1, divide):
            for c in range(1, MAP_SIZE + 1, divide):
                rotate(r, c, divide)

        melt_ice()

def get_ice_count():
    sum = 0
    for r in range(1, MAP_SIZE + 1):
        for c in range(1, MAP_SIZE + 1):
            sum += MAP[r][c]
    
    return sum

def BFS(r, c):
    rp, wp = 0, 0
    
    queue[wp].r = r
    queue[wp].c = c
    wp += 1
    
    visit[r][c] = True

    while rp < wp:
        out = queue[rp]
        rp += 1
        
        for i in range(4):
            nr = out.r + dr[i]
            nc = out.c + dc[i]
            
            if MAP[nr][nc] == 0 or visit[nr][nc] == True: continue
            
            queue[wp].r = nr
            queue[wp].c = nc
            wp += 1
            
            visit[nr][nc] = True

    return wp

def get_group_count():
    global visit
    
    visit = [[False] * MAX for _ in range(MAX)]
    
    max = 0
    for r in range(1, MAP_SIZE + 1):
        for c in range(1, MAP_SIZE + 1):
            if MAP[r][c] == 0 or visit[r][c] == True: continue
            
            tmp = BFS(r, c)
            if max < tmp: max = tmp

    return max

# T = int(input())
T = 1
for tc in range(T):
    input_data()
    
    simulate()
    
    ice_count = get_ice_count()
    group_count = get_group_count()
    
    print(ice_count)
    print(group_count)