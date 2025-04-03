MAX = 300 + 30

MAP = [[0] * MAX for _ in range(MAX)]

class RC:
    def __init__(self, r: int, c: int):
        self.r = r
        self.c = c
    
queue = [RC(0, 0) for _ in range(MAX * MAX)]   

dr = [-2, -1, 1, 2, 2, 1, -1, -2]
dc = [1, 2, 2, 1, -1, -2, -2, -1]

def input_data():             
    global L, sr, sc, er, ec, MAP
    
    L = int(input())
    sr, sc = map(int, input().split())
    er, ec = map(int, input().split())
    
    MAP = [[0] * MAX for _ in range(MAX)]
    
def print_map(): # for debug
    for r in range(L):
        print(*MAP[r][:L])
    print("")

def BFS(r, c):
    rp, wp = 0, 0
    
    queue[wp].r = r
    queue[wp].c = c
    wp += 1    
                    
    MAP[r][c] = 1                    
                    
    while rp < wp:
        out = queue[rp]
        rp += 1
        
        if out.r == er and out.c == ec:
            return MAP[out.r][out.c] - 1
                
        for i in range(8):
            nr = out.r + dr[i]
            nc = out.c + dc[i]
            
            if nr < 0 or nc < 0 or nr > L - 1 or nc > L - 1: continue
            if MAP[nr][nc] != 0: continue
           
            queue[wp].r = nr
            queue[wp].c = nc
            wp += 1            
            
            MAP[nr][nc] = MAP[out.r][out.c] + 1

    return -1 # error
               
T = int(input())
for _ in range(T):
    input_data()                 
                                      
    print(BFS(sr, sc))