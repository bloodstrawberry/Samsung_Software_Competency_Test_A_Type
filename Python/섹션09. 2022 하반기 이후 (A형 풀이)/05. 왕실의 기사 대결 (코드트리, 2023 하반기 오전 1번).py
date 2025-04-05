MAX_L = 40 + 5
MAX_N = 30 + 5

EMPTY = 0
TRAP = -1
WALL = -2

MAP = [[0] * MAX_L for _ in range(MAX_L)] # 함정과 벽만 기록
tmpMAP = [[0] * MAX_L for _ in range(MAX_L)]

class COMMAND:
    def __init__(self, index: int, direction: int):
        self.index = index
        self.direction = direction

command = [COMMAND(0, 0) for _ in range(100 + 10)]

class RCI:
    def __init__(self, r: int, c: int, index: int):
        self.r = r
        self.c = c
        self.index = index
        
queue = [RCI(0, 0, 0) for _ in range(MAX_L * MAX_L)]       

class KNIGHT:
    def __init__(self, r: int, c: int, h: int, w: int, k: int, init_k: int):
        self.r = r
        self.c = c
        self.h = h
        self.w = w
        self.k = k # 기사의 체력
        self.init_k = k # 기사의 원래 체력

knight = [KNIGHT(0, 0, 0, 0, 0, 0) for _ in range(MAX_N)]  

# ↑, →, ↓, ←
dr = [-1, 0, 1, 0]
dc = [0, 1, 0, -1]

def input_data():   
    global L, N, Q, MAP
    
    L, N, Q = map(int, input().split())
    
    MAP = [[WALL] * MAX_L for _ in range(MAX_L)]
    
    for r in range(1, L + 1):
        MAP[r][1:L + 1] = map(int, input().split())
    
    for r in range(1, L + 1):
        for c in range(1 , L + 1):
            if MAP[r][c] == 1: MAP[r][c] = TRAP
            elif MAP[r][c] == 2: MAP[r][c] = WALL

    for n in range(1, N + 1):
        knight[n].r, knight[n].c, knight[n].h, knight[n].w, knight[n].k = map(int, input().split())
        
        # 최초 체력 저장
        knight[n].init_k = knight[n].k
    
    for q in range(Q):
        command[q].index, command[q].direction = map(int, input().split())
           
def print_map(map): # for debug
    for r in range(1, L + 1):
        print(' '.join('%2d' % num for num in map[r][1:L + 1]))
    print("")

def print_status(): # for debug
    for n in range(1, N + 1):
        tmp = knight[n]
        print(f"{n}] ({tmp.r}, {tmp.c}) {tmp.h}, {tmp.w}, : {tmp.k}")
    print("")

def set_knight():
    global tmpMAP
    
    tmpMAP = [[0] * MAX_L for _ in range(MAX_L)]

    for n in range(1, N + 1):
        if knight[n].k <= 0: continue
        
        kr, kc, kh, kw = knight[n].r, knight[n].c, knight[n].h, knight[n].w
        
        for r in range(kr, kr + kh):
            for c in range(kc, kc + kw):
                tmpMAP[r][c] = n
    
def BFS(index, direciton):
    if knight[index].k <= 0: return
    
    visit = [[False] * MAX_L for _ in range(MAX_L)]
    
    kr, kc, kh, kw = knight[index].r, knight[index].c, knight[index].h, knight[index].w
    
    rp, wp = 0, 0
    
    for r in range(kr, kr + kh):
        for c in range(kc, kc + kw):
            queue[wp].r = r
            queue[wp].c = c
            queue[wp].index = index
            wp += 1
            
            visit[r][c] = True            
    
    while rp < wp:
        out = queue[rp]
        rp += 1
        
        nr = out.r + dr[direciton]
        nc = out.c + dc[direciton]
        
        if MAP[nr][nc] == WALL: return
        
        if visit[nr][nc] == True or tmpMAP[nr][nc] == EMPTY: continue
        
        another = tmpMAP[nr][nc]
        
        kr, kc, kh, kw = knight[another].r, knight[another].c, knight[another].h, knight[another].w
        
        for r in range(kr, kr + kh):
            for c in range(kc, kc + kw):                
                queue[wp].r = r
                queue[wp].c = c
                queue[wp].index = another
                wp += 1
                
                visit[r][c] = True
                    
    check = [False] * MAX_N  
    for i in range(wp):
        knight_index = queue[i].index
        check[knight_index] = True
    
    for n in range(1, N + 1):
        if check[n] == False: continue
        
        knight[n].r = knight[n].r + dr[direciton]
        knight[n].c = knight[n].c + dc[direciton]
        
        if n == index: continue
        
        kr, kc, kh, kw = knight[n].r, knight[n].c, knight[n].h, knight[n].w
        
        for r in range(kr, kr + kh):
            for c in range(kc, kc + kw):
                if MAP[r][c] == TRAP: knight[n].k -= 1
        
        
    
def simulate():
    for q in range(Q):
        set_knight()
        BFS(command[q].index, command[q].direction)
        
def get_answer():
    sum = 0
    for n in range(1, N + 1):
        if knight[n].k > 0: sum += (knight[n].init_k - knight[n].k)
        
    return sum

# T = int(input())
T = 1
for tc in range(T):    
    input_data()
    
    simulate()
    
    print(get_answer())