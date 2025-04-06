MAX = 20 + 10

OFFICE = 1
LEFT = 2
UP = 3
RIGHT = 4
DOWN = 5

MAP = [[0] * MAX for _ in range(MAX)]
temperature = [[0] * MAX for _ in range(MAX)]

class RC:
    def __init__(self, r: int, c: int):
        self.r = r
        self.c = c
    
office = [RC(0, 0) for _ in range(MAX * MAX)]  
ocnt = 0

class RCD:
    def __init__(self, r: int, c: int, dir: int):
        self.r = r
        self.c = c
        self.dir = dir
        
air_conditioner = [RCD(0, 0, 0) for _ in range(MAX * MAX)] 
acnt = 0

class RCL:
    def __init__(self, r: int, c: int, length: int):
        self.r = r
        self.c = c
        self.length = length

queue = [RCL(0, 0, 0) for _ in range(MAX * MAX)] 

class WALL:
    def __init__(self):
        self.direction = [False] * 6

wall = [[WALL() for _ in range(MAX)] for _ in range(MAX)]

# -, -, ←, ↑, →, ↓
dr = [0, 0, 0, -1, 0, 1]
dc = [0, 0, -1, 0, 1, 0]

def input_data():
    global N, K, W, ocnt, acnt
    
    N, W, K = map(int, input().split())
    
    ocnt, acnt = 0, 0

    for r in range(1, N + 1):
        line = list(map(int, input().split()))        
        for c in range(1, N + 1):
            MAP[r][c] = line[c - 1]
            
            if MAP[r][c] == OFFICE:
                office[ocnt].r = r
                office[ocnt].c = c
                ocnt += 1                
            elif MAP[r][c] != 0:
                air_conditioner[acnt].r = r
                air_conditioner[acnt].c = c
                air_conditioner[acnt].dir = MAP[r][c]
                acnt += 1
                
    for _ in range(W):
        r, c, s = map(int, input().split())
        
        if s == 0:
            wall[r][c].direction[UP] = True
            wall[r - 1][c].direction[DOWN] = True                        
        else:
            wall[r][c].direction[LEFT] = True
            wall[r][c - 1].direction[RIGHT] = True
        
def print_map(map): # for debug
    for r in range(1, N + 1):
        print(' '.join('%2d' % num for num in map[r][1:N + 1]))
    print("")
        
def BFS(r, c, dir):
    visit = [[False] * MAX for _ in range(MAX)]
        
    sr = r + dr[dir]
    sc = c + dc[dir]
    
    rp, wp = 0, 0
    
    queue[wp].r = sr
    queue[wp].c = sc
    queue[wp].length = 5
    wp += 1
    
    visit[sr][sc] = True
    
    while rp < wp:
        out = queue[rp]
        rp += 1
        
        if out.length == 0: break
        
        if out.r < 1 or out.c < 1 or out.r > N or out.c > N: continue
        
        temperature[out.r][out.c] += out.length
        
        if dir == RIGHT or dir == LEFT:
            nc = out.c + dc[dir]

            # ↖ ↗ 위
            nr = out.r - 1
            if visit[nr][nc] == False \
                and wall[out.r][out.c].direction[UP] == False \
                and wall[nr][out.c].direction[dir] == False:                
                    
                queue[wp].r = nr
                queue[wp].c = nc
                queue[wp].length = out.length - 1
                wp += 1

                visit[nr][nc] = True

            # ← → 옆
            nr = out.r
            if visit[nr][nc] == False \
                and wall[out.r][out.c].direction[dir] == False:
                
                queue[wp].r = nr
                queue[wp].c = nc
                queue[wp].length = out.length - 1
                wp += 1

                visit[nr][nc] = True

            # ↙ ↘ 아래
            nr = out.r + 1
            if visit[nr][nc] == False \
                and wall[out.r][out.c].direction[DOWN] == False \
                and wall[nr][out.c].direction[dir] == False:
                
                queue[wp].r = nr
                queue[wp].c = nc
                queue[wp].length = out.length - 1
                wp += 1

                visit[nr][nc] = True

        else:  # UP or DOWN
            nr = out.r + dr[dir]

            # ↖ ↙ 왼쪽
            nc = out.c - 1
            if visit[nr][nc] == False \
                and wall[out.r][out.c].direction[LEFT] == False \
                and wall[out.r][nc].direction[dir] == False:
                
                queue[wp].r = nr
                queue[wp].c = nc
                queue[wp].length = out.length - 1
                wp += 1

                visit[nr][nc] = True

            # ↑ ↓ 위, 아래
            nc = out.c
            if visit[nr][nc] == False \
                and wall[out.r][out.c].direction[dir] == False:
                
                queue[wp].r = nr
                queue[wp].c = nc
                queue[wp].length = out.length - 1
                wp += 1

                visit[nr][nc] = True

            # ↗ ↘ 오른쪽
            nc = out.c + 1
            if visit[nr][nc] == False \
                and wall[out.r][out.c].direction[RIGHT] == False \
                and wall[out.r][nc].direction[dir] == False:
                
                queue[wp].r = nr
                queue[wp].c = nc
                queue[wp].length = out.length - 1
                wp += 1

                visit[nr][nc] = True

def control_temperature():
    tmp_temp = [[0] * MAX for _ in range(MAX)]
    for r in range(1, N + 1):
        for c in range(1, N + 1):
            if temperature[r][c] == 0: continue
            
            value = temperature[r][c]
            for i in range(2, 6):
                nr = r + dr[i]
                nc = c + dc[i]
                
                if nr < 1 or nc < 1 or nr > N or nc > N: continue
                if wall[r][c].direction[i] == True: continue
                
                if temperature[r][c] > temperature[nr][nc]:
                    diff = (temperature[r][c] - temperature[nr][nc]) // 4
                    
                    value -= diff
                    tmp_temp[nr][nc] += diff
            
            tmp_temp[r][c] += value
                
    for r in range(1, N + 1):
        for c in range(1, N + 1):
            temperature[r][c] = tmp_temp[r][c]

def decrease_temperature():
    if temperature[1][1] != 0: temperature[1][1] -= 1
    if temperature[N][1] != 0: temperature[N][1] -= 1
    if temperature[1][N] != 0: temperature[1][N] -= 1
    if temperature[N][N] != 0: temperature[N][N] -= 1

    for r in range(2, N):
        if temperature[r][1] != 0: temperature[r][1] -= 1
        
    for r in range(2, N):
        if temperature[r][N] != 0: temperature[r][N] -= 1
    
    for c in range(2, N):
        if temperature[1][c] != 0: temperature[1][c] -= 1
    
    for c in range(2, N):
        if temperature[N][c] != 0: temperature[N][c] -= 1
     
def check_office():
    for i in range(ocnt):
        if temperature[office[i].r][office[i].c] < K:
            return False
    
    return True
        
def simulate():
    time = 0
    while True:
        for i in range(acnt):
            r, c, dir = air_conditioner[i].r, air_conditioner[i].c, air_conditioner[i].dir
            BFS(r, c, dir)            
            
        control_temperature()
        decrease_temperature()
        
        time += 1        
        if time > 100: return -1
        
        if check_office(): break
        
    return time

# T = int(input())
T = 1
for tc in range(T):    
    input_data()
    
    print(simulate())