import copy

MAX_N = 20 + 5
MAX_M = 5 + 2

HEAD = 1
BODY = 2
TAIL = 3
ROOP = 4

# 공을 던지는 방향
RIGHT = 0
UP = 1
LEFT = 2
DOWN = 3

class MAP_INFO:
    def __init__(self, value: int, order: int, loop: int):
        self.value = value # 입력 값
        self.order = order # k번째 사람
        self.loop = loop # loop의 번호

MAP = [[MAP_INFO(0, 0, 0) for _ in range(MAX_N)] for _ in range(MAX_N)]
visit = [[False] * MAX_N for _ in range(MAX_N)]

class RCON:
    def __init__(self, r: int, c: int, value: int, order: int):
        self.r = r
        self.c = c
        self.value = value
        self.order = order # K번째 사람
        
queue = [RCON(0, 0, 0, 0) for _ in range(MAX_N * MAX_N)]

position = [[RCON(0, 0, 0, 0) for _ in range(MAX_N * MAX_N)] for _ in range(MAX_M)]
pos_index = [0] * MAX_M # 1 ~ 4의 수
people_index = [0] * MAX_M # 1 ~ 3의 수

check_direction = [False] * MAX_M # 방향이 바뀌었는지 여부
 
# ↑, →, ↓, ←
dr = [-1, 0, 1, 0]
dc = [0, 1, 0, -1]

def input_data():
    global N, M, K, MAP, pos_index, people_index, check_direction
    
    N, M, K = map(int, input().split())

    for r in range(1, N + 1):
        line = list(map(int, input().split()))        
        for c in range(1, N + 1):
            MAP[r][c].value = line[c - 1]
            MAP[r][c].loop = MAP[r][c].order = -1
            
    pos_index = [0] * MAX_M
    people_index = [0] * MAX_M
    check_direction = [False] * MAX_M

def print_map(map): # for debug
    for r in range(1, N + 1):
        print(*map[r][1:N + 1])     
    print("")

def print_map_value(map): # for debug
    for r in range(1, N + 1):
        for c in range(1, N + 1):
            print(map[r][c].value, end=" ")
        print("")
    print("")
     
def print_position(loop): # for debug
    index = pos_index[loop]

    for i in range(index):
        p = position[loop][i]
        print(f"{i}] ({p.r}, {p.c}) {p.order}, {p.value}")
    print("")
    
def BFS(r, c, loop):
    global MAP, visit, position, people_index, pos_index
    
    order = 1
    
    MAP[r][c].loop = loop
    MAP[r][c].order = order
    
    position[loop][pos_index[loop]].r = r
    position[loop][pos_index[loop]].c = c
    position[loop][pos_index[loop]].order = order
    position[loop][pos_index[loop]].value = HEAD
    
    order += 1  
    pos_index[loop] += 1
    
    rp, wp = 0, 0
    
    visit[r][c] = True

    # 1 -> 2 먼저 찾기
    for i in range(4):
        nr = r + dr[i]
        nc = c + dc[i]
        
        if nr < 1 or nc < 1 or nr > N or nc > N: continue
        
        if MAP[nr][nc].value == BODY:            
            queue[wp].r = nr
            queue[wp].c = nc
            wp += 1
            
            visit[nr][nc] = True
            
            MAP[nr][nc].loop = loop
            MAP[nr][nc].order = order
            
            position[loop][pos_index[loop]].r = nr
            position[loop][pos_index[loop]].c = nc
            position[loop][pos_index[loop]].order = order
            position[loop][pos_index[loop]].value = BODY
    
            order += 1
            pos_index[loop] += 1
            
            break

	# 1, 2 count
    people_index[loop] = 2

    while rp < wp:
        out = queue[rp]
        rp += 1
        
        for i in range(4):
            nr = out.r + dr[i]
            nc = out.c + dc[i]
            
            if nr < 1 or nc < 1 or nr > N or nc > N: continue
            if MAP[nr][nc].value == 0 or visit[nr][nc] == True: continue
            
            queue[wp].r = nr
            queue[wp].c = nc
            wp += 1
            
            visit[nr][nc] = True
            
            MAP[nr][nc].loop = loop
            MAP[nr][nc].order = order
            
            position[loop][pos_index[loop]].r = nr
            position[loop][pos_index[loop]].c = nc
            position[loop][pos_index[loop]].order = order
            position[loop][pos_index[loop]].value = MAP[nr][nc].value
            
            order += 1
            pos_index[loop] += 1
    
            if MAP[nr][nc].value <= TAIL: people_index[loop] += 1

def move(loop):    
    index = pos_index[loop]
    check = check_direction[loop]
    
    if check == False: # 1 -> 4 -> .. -> 2 -> 1로 이동
        tmp = copy.deepcopy(position[loop][index - 1])
        
        for i in range(index - 2, -1, -1):
            r, c = position[loop][i].r, position[loop][i].c
            position[loop][i + 1].r, position[loop][i + 1].c = r, c
            
        position[loop][0].r, position[loop][0].c = tmp.r, tmp.c
    else: # 1 -> 2 -> 2 -> ... -> 3 -> 4 -> 1로 이동
        tmp = copy.deepcopy(position[loop][0])
        
        for i in range(1, index):
            r, c = position[loop][i].r, position[loop][i].c
            position[loop][i - 1].r, position[loop][i - 1].c = r, c
            
        position[loop][index - 1].r, position[loop][index - 1].c = tmp.r, tmp.c

    for i in range(index):
        r, c = position[loop][i].r, position[loop][i].c
        order, value = position[loop][i].order, position[loop][i].value
        
        MAP[r][c].order = order
        MAP[r][c].value = value

def get_score(round):
    hit = [False, True, True, True, False]
    
    # → 1 ~ N ==> 0번 방향
	# ↑ N + 1 ~ 2 * N ==> 1번 방향
	# ← 2 * N + 1 ~ 3 * N ==> 2번 방향
	# ↓ 3 * N + 1 ~ 4 * N ==> 3번 방향

	# if N == 7 
	# → 1 ~ 7  ==> 0번 방향
	# ↑ 8 ~ 14 ==> 1번 방향
	# ← 15 ~ 21 ==> 2번 방향
	# ↓ 22 ~ 28 ==> 3번 방향
    
    ball_dir = ((round - 1) % (4 * N)) // N
    line = ((round - 1) % N) + 1

    if ball_dir == RIGHT: # →
        for c in range(1, N + 1):
            if hit[MAP[line][c].value] == True:
                order = MAP[line][c].order
                loop = MAP[line][c].loop
                
                if check_direction[loop] == True:
                    order = people_index[loop] - order + 1
                
                check_direction[loop] = not check_direction[loop]
                
                return order * order                                
    elif ball_dir == UP: # ↑
        for r in range(N, 0, -1):
            if hit[MAP[r][line].value] == True:
                order = MAP[r][line].order
                loop = MAP[r][line].loop
                
                if check_direction[loop] == True:
                    order = people_index[loop] - order + 1
                
                check_direction[loop] = not check_direction[loop]
                
                return order * order 
    elif ball_dir == LEFT: # ←
        for c in range(N, 0, -1):
            if hit[MAP[N + 1 - line][c].value] == True:
                order = MAP[N + 1 - line][c].order
                loop = MAP[N + 1 - line][c].loop
                
                if check_direction[loop] == True:
                    order = people_index[loop] - order + 1
                
                check_direction[loop] = not check_direction[loop]
                
                return order * order 
    elif ball_dir == DOWN: # ↓
        for r in range(1, N + 1):
            if hit[MAP[r][N + 1 - line].value] == True:
                order = MAP[r][N + 1 - line].order
                loop = MAP[r][N + 1 - line].loop
                
                if check_direction[loop] == True:
                    order = people_index[loop] - order + 1
                
                check_direction[loop] = not check_direction[loop]
                
                return order * order 
            
    return 0

def simulate():
    global visit
    
    visit = [[False] * MAX_N for _ in range(MAX_N)]

    loop = 0
    for r in range(1, N + 1):
        for c in range(1, N + 1):
            if MAP[r][c].value != HEAD or visit[r][c] == True: continue
            
            BFS(r, c, loop)
            
            # print_position(loop)
            
            loop += 1

    score = 0
    for k in range(1, K + 1):
        for m in range(M): move(m)
        
        score += get_score(k)

    return score

# T = int(input())
T = 1
for tc in range(T):    
    input_data()
    
    print(simulate())
