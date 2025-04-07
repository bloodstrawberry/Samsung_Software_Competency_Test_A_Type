MAX = 100 + 20

MAP = [[0] * MAX for _ in range(MAX)]
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
    global N, L, R
    
    N, L, R = map(int, input().split())
    
    for r in range(1, N + 1):
        MAP[r][1:N + 1] = map(int, input().split())

def print_map(): # for debug    
    for r in range(1, N + 1):
        print(*MAP[r][1:N + 1])
    print("")

def BFS(r, c):
    rp, wp = 0, 0
    
    queue[wp].r = r
    queue[wp].c = c
    wp += 1
    
    visit[r][c] = True
    
    sum = MAP[r][c]
    
    while rp < wp:
        out = queue[rp]
        rp += 1
        
        for i in range(4):
            nr = out.r + dr[i]
            nc = out.c + dc[i]
            
            if nr < 1 or nc < 1 or nr > N or nc > N: continue
            
            diff = abs(MAP[out.r][out.c] - MAP[nr][nc])
            
            if visit[nr][nc] == True or (L <= diff and diff <= R) == False: continue
            
            queue[wp].r = nr
            queue[wp].c = nc
            wp += 1
            
            visit[nr][nc] = True
            sum += MAP[nr][nc]
    
    for i in range(wp):
        tmp = queue[i]
        MAP[tmp.r][tmp.c] = sum // wp

    return wp

def simulate():
    global visit
    
    visit = [[False] * MAX for _ in range(MAX)]
    
    result = False
    for r in range(1, N + 1):
        for c in range(1, N + 1):
            if visit[r][c] == True: continue
            
            move_egg_count = BFS(r, c)
            if move_egg_count != 1: result = True
     
    return result

# T = int(input())
T = 1
for tc in range(T):
    input_data()
    
    answer = 0
    
    while True:
        result = simulate()
        
        if result == False: break
        
        answer += 1
    
    print(answer)