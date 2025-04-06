MAX = 50 + 5

CLOCKWISE = 0
COUNTER_CLOCKWISE = 1

circle = [[0] * MAX for _ in range(MAX)]
visit = [[False] * MAX for _ in range(MAX)]

X = [0] * MAX
D = [0] * MAX
K = [0] * MAX

class RC:
    def __init__(self, r: int, c: int):
        self.r = r
        self.c = c

queue = [RC(0, 0) for _ in range(MAX * MAX)]

# ↑, →, ↓, ←
dr = [-1, 0, 1, 0]
dc = [0, 1, 0, -1]

def input_data():
    global N, M, Q, circle, X, D, K
    
    N, M, Q = map(int, input().split())
    
    circle = [[0] * MAX for _ in range(MAX)]
    
    for r in range(1, N + 1):
        circle[r][1:M + 1] = map(int, input().split())
    
    for i in range(1, Q + 1):
        X[i], D[i], K[i] = map(int, input().split())
    
def print_map(): # for debug
    for r in range(1, N + 1):
        print(*circle[r][1:M + 1])
    print("") 

def rotate(x, d, k):
    if d == COUNTER_CLOCKWISE: k = -k

    for r in range(x, N + 1, x):
        arr = circle[r][1:M + 1]
        
        for i in range(M):
            new_index = (i - k) % M
            if new_index < 0: new_index += M
            circle[r][i + 1] = arr[new_index]
                        
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
            
            if circle[nr][nc] == 0: continue
            
            if (circle[nr][nc] != circle[r][c]) or visit[nr][nc] == True: continue
            
            queue[wp].r = nr
            queue[wp].c = nc
            wp += 1
            
            visit[nr][nc] = True

        if out.c == 1:
            if circle[r][c] == circle[out.r][M] and visit[out.r][M] == False:
                queue[wp].r = out.r
                queue[wp].c = M
                wp += 1
                
                visit[out.r][M] = True
        elif out.c == M:
            if circle[r][c] == circle[out.r][1] and visit[out.r][1] == False:
                queue[wp].r = out.r
                queue[wp].c = 1
                wp += 1
                
                visit[out.r][1] = True
            
    if wp > 1:
        for i in range(wp):
            r, c = queue[i].r, queue[i].c
            circle[r][c] = 0
        
        return True
    
    return False

def make_average():    
    sum, count = 0, 0
    for r in range(1, N + 1):
        for c in range(1, M + 1):
            if circle[r][c] != 0:
                sum += circle[r][c]
                count += 1
                
    if count == 0: return
    
    avg = sum // count
    for r in range(1, N + 1):
        for c in range(1, M + 1):
            if circle[r][c] == 0: continue
            
            if circle[r][c] < avg: circle[r][c] += 1
            elif circle[r][c] > avg: circle[r][c] -= 1

def start_game():
    global visit
    
    visit = [[False] * MAX for _ in range(MAX)]
    
    delete_check = False
    for r in range(1, N + 1):
        for c in range(1, M + 1):
            if circle[r][c] == 0 or visit[r][c] == True: continue
            
            check = BFS(r, c)
            if check == True: delete_check = True
    
    if delete_check == False: make_average()

def simulate():
    for q in range(1, Q + 1):
        rotate(X[q], D[q], K[q])
        start_game()

def get_answer():
    sum = 0
    for r in range(1, N + 1):
        for c in range(1, M + 1):
            sum += circle[r][c]
            
    return sum

# T = int(input())
T = 1
for tc in range(T):
    input_data()
    
    simulate()
    
    print(get_answer())
