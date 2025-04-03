MAX = 25 + 5

N = int(input())

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

def print_visit():
    for r in range(1, N + 1):
        print(*list(map(int, visit[r][1:N + 1])))

def input_data():
    for r in range(1, N + 1):
        MAP[r][1:N + 1] = list(map(int, input()))
        
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

input_data()

answer = []
for r in range(1, N + 1):
    for c in range(1, N + 1):
        if MAP[r][c] == 1 and visit[r][c] == False:
            answer.append(BFS(r, c))

print(len(answer))

answer = sorted(answer)

for ans in answer:
    print(ans)