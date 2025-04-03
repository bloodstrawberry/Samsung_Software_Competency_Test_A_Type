# printMap 수정

MAX = 500 + 50

N, M, A, B, K = map(int, input().split())

MAP = [[0] * MAX for _ in range(MAX)]
visit = [[0] * MAX for _ in range(MAX)]

class RC:
    def __init__(self, r: int, c: int):
        self.r = r
        self.c = c
    
queue = [RC(0, 0) for _ in range(MAX * MAX)]   

# ↑, →, ↓, ←
dr = [-1, 0, 1, 0]
dc = [0, 1, 0, -1]

def input_data():             
    global sr, sc, er, ec
    
    for _ in range(K):
        r, c = map(int, input().split())
        MAP[r][c] = 1
    
    sr, sc = map(int, input().split())
    er, ec = map(int, input().split())
    
def print_map(): # for debug
    for r in range(1, N + 1):
        print(*MAP[r][1:M + 1])
    print("")

def isEmpty(sr, sc):
    for r in range(sr, sr + A):
        for c in range(sc, sc + B):
            if MAP[r][c] == 1: return False
    
    return True

def BFS(r, c):
    rp, wp = 0, 0
    
    visit[r][c] = 1
        
    queue[wp].r = r
    queue[wp].c = c
    wp += 1    
                    
    while rp < wp:
        out = queue[rp]
        rp += 1
        
        if out.r == er and out.c == ec:
            return visit[out.r][out.c] - 1
                
        for i in range(4):
            nr = out.r + dr[i]
            nc = out.c + dc[i]
            
            if nr < 1 or nc < 1 or (nr + A - 1) > N or (nc + B - 1) > M: continue
            if isEmpty(nr, nc) == False or visit[nr][nc] != 0: continue             
            
            queue[wp].r = nr
            queue[wp].c = nc
            wp += 1
            
            visit[nr][nc] = visit[out.r][out.c] + 1

    return -1 # error
                 
input_data()                 
                                      
print(BFS(sr, sc))