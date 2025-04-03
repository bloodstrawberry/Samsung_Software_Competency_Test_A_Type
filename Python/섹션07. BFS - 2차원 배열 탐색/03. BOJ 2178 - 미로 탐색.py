MAX = 100 + 10

N, M = map(int, input().split())

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

def print_map():
    print("MAP")
    for r in range(1, N + 1):
        print(*MAP[r][1:M + 1])
    print("")
        
    print("visit")
    for r in range(1, N + 1):
        print(*list(map(int, visit[r][1:M + 1])))
    print("")

def input_data():    
    for r in range(1, N + 1):
        MAP[r][1:M + 1] = list(map(int, input()))
        
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
            
            MAP[nr][nc] = MAP[out.r][out.c] + 1
            
input_data()

BFS(1, 1)

print(MAP[N][M])