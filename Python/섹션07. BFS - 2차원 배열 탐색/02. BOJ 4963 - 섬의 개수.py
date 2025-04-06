MAX = 50 + 5

MAP = [[0] * MAX for _ in range(MAX)]
visit = [[False] * MAX for _ in range(MAX)]

class RC:
    def __init__(self, r: int, c: int):
        self.r = r
        self.c = c

queue = [RC(0, 0) for _ in range(MAX * MAX)]   

# 8방향 ↑, ↗, →, ↘, ↓, ↙, ←, ↖
dr = [ -1, -1, 0, 1, 1, 1, 0, -1 ]
dc = [ 0, 1, 1, 1, 0, -1, -1, -1 ]

def print_visit():
    for r in range(1, H + 1):
        print(*list(map(int, visit[r][1:W + 1])))

def input_data():
    global W, H, MAP, visit
    
    W, H = map(int, input().split())
    
    # init
    MAP = [[0] * MAX for _ in range(MAX)]
    visit = [[False] * MAX for _ in range(MAX)]
    
    for r in range(1, H + 1):
        MAP[r][1:W + 1] = map(int, input().split())
        
def BFS(r, c):
    rp, wp = 0, 0
    
    queue[wp].r = r
    queue[wp].c = c
    wp += 1
    
    visit[r][c] = True
        
    while rp < wp:
        out = queue[rp]
        rp += 1
        
        for i in range(8):
            nr = out.r + dr[i]
            nc = out.c + dc[i]
            
            if MAP[nr][nc] == 0 or visit[nr][nc] == True: continue
            
            queue[wp].r = nr
            queue[wp].c = nc
            wp += 1
            
            visit[nr][nc] = True
                
    return wp

while True:
    input_data()
        
    if W == 0 and H == 0: break

    ans_count = 0
    for r in range(1, H + 1):
        for c in range(1, W + 1):
            if MAP[r][c] == 1 and visit[r][c] == False:
                BFS(r, c)
                ans_count += 1
    
    print(ans_count)