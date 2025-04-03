MAX = 1000 + 10

N, M = map(int, input().split())

MAP = [[0] * MAX for _ in range(MAX)]
visit = [[[0] * MAX for _ in range(MAX)] for _ in range(2)]

class RC:
    def __init__(self, r: int, c: int, crash: int):
        self.r = r
        self.c = c
        self.crash = crash
    
queue = [RC(0, 0, 0) for _ in range(MAX * MAX * 2)]   

# ↑, →, ↓, ←
dr = [-1, 0, 1, 0]
dc = [0, 1, 0, -1]

def input_data():    
    for r in range(1, N + 1):
        MAP[r][1:M + 1] = list(map(int, input()))

def print_map(map): # for debug
    for r in range(1, N + 1):
        print(*map[r][1:M + 1])
    print("")
        
def print_map_all(): # for debug
    print("MAP")
    print_map(MAP)
    
    print("visit[0]")    
    print_map(visit[0])
    
    print("visti[1]")
    print_map(visit[1])
          
def BFS(r, c):
    rp, wp = 0, 0
    
    visit[0][r][c] = 1
    
    queue[wp].r = r
    queue[wp].c = c
    wp += 1
            
    while rp < wp:
        out = queue[rp]
        rp += 1
        
        if out.r == N and out.c == M:
            return visit[out.crash][out.r][out.c]
        
        for i in range(4):
            nr = out.r + dr[i]
            nc = out.c + dc[i]
            
            if nr < 1 or nc < 1 or nr > N or nc > M: continue
            
            if out.crash == 0:
                if MAP[nr][nc] == 0 and visit[0][nr][nc] == 0:
                    queue[wp].r = nr
                    queue[wp].c = nc
                    queue[wp].crash = 0     
                    wp += 1
                    
                    visit[0][nr][nc] = visit[0][out.r][out.c] + 1
                else:
                    if MAP[nr][nc] == 1 and visit[1][nr][nc] == 0:
                        queue[wp].r = nr
                        queue[wp].c = nc
                        queue[wp].crash = 1     
                        wp += 1
                        
                        visit[1][nr][nc] = visit[0][out.r][out.c] + 1
            else: # 벽을 한 번 부순 경우
                if MAP[nr][nc] == 0 and visit[1][nr][nc] == 0:
                    queue[wp].r = nr
                    queue[wp].c = nc
                    queue[wp].crash = 1
                    wp += 1
                    
                    visit[1][nr][nc] = visit[1][out.r][out.c] + 1

    return -1
                          
input_data()

print(BFS(1, 1))