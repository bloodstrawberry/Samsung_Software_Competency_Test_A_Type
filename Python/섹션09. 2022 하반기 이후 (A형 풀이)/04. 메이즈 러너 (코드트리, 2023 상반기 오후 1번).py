import copy

MAX = 10 + 5

PLAYER_NUMBER = 10
DESTINATION = -1

UP = 0
RIGHT = 1
DOWN = 2
LEFT = 3

MAP = [[0] * MAX for _ in range(MAX)]

class RCE:
    def __init__(self, r: int, c: int, escape: bool):
        self.r = r
        self.c = c
        self.escape = escape # Player 탈출 확인

player = [RCE(0, 0, False) for _ in range(MAX)]
destination = RCE(0, 0, False)

class RCS:
    def __init__(self, r: int, c: int, size: int):
        self.r = r
        self.c = c
        self.size = size # 회전을 위한 크기

# ↑, →, ↓, ←
dr = [-1, 0, 1, 0]
dc = [0, 1, 0, -1]

def input_data():   
    global N, M, K, MAP
    
    N, M, K = map(int, input().split())
        
    for r in range(1, N + 1):
        MAP[r][1:N + 1] = map(int, input().split())
    
    for m in range(M):
        player[m].r, player[m].c = map(int, input().split())
        player[m].escape = False
    
    destination.r, destination.c = map(int, input().split())
           
def print_map(map): # for debug
    for r in range(1, N + 1):
        print(' '.join('%2d' % num for num in map[r][1:N + 1]))
    print("")

def print_status(): # for debug
    tmp_map = copy.deepcopy(MAP)
    
    for m in range(M):
        p = player[m]
        print(f"{m} : {p.r}, {p.c} (exit : {p.escape})")
        if p.escape == False:
            tmp_map[p.r][p.c] = m + PLAYER_NUMBER
            
        print("")
        
        tmp_map[destination.r][destination.c] = DESTINATION
        
        print_map(tmp_map)
    
def check():
    for m in range(M):
        if player[m].escape == False: return False
    
    return True

def check_row(player):
    dr = destination.r
    pr = player.r 
    
    # dr > pr -> 출구는 아래에
	# dr = pr -> 같은 행, 상하로 움직일 수 없음.
	# dr < pr -> 출구는 위에
    return dr - pr

def check_column(player):
    dc = destination.c
    pc = player.c 
    
	# dc > pc -> 출구는 오른쪽에
	# dc = pc -> 같은 열, 좌우로 움직일 수 없음.
	# dc < pc -> 출구는 왼쪽에
    return dc - pc

def move():
    step = 0
    for m in range(M):
        if player[m].escape == True: continue
        
        next_r = [0] * 4
        next_c = [0] * 4
        
        for i in range(4):
            next_r[i] = player[m].r + dr[i]
            next_c[i] = player[m].c + dc[i]
            
        up_down = check_row(player[m])
        left_right = check_column(player[m])
        
        direction = -1
        
    	# 항상 출구를 향해 움직이기 때문에 격자를 벗어나지 않음.
        if up_down < 0 and MAP[next_r[UP]][next_c[UP]] == 0: direction = UP
        elif up_down > 0 and MAP[next_r[DOWN]][next_c[DOWN]] == 0: direction = DOWN
        elif left_right < 0 and MAP[next_r[LEFT]][next_c[LEFT]] == 0: direction = LEFT
        elif left_right > 0 and MAP[next_r[RIGHT]][next_c[RIGHT]] == 0: direction = RIGHT
        
        if direction == -1: continue
        
        player[m].r = player[m].r + dr[direction]
        player[m].c = player[m].c + dc[direction]
        
        if player[m].r == destination.r and player[m].c == destination.c:
            player[m].escape = True
        
        step += 1
    
    return step
        
def rotate_check(map, sr, sc, size):
    destination_check = player_check = False
    for r in range(sr, sr + size):
        for c in range(sc, sc + size):
            if map[r][c] >= PLAYER_NUMBER: player_check = True
            elif map[r][c] == DESTINATION: destination_check = True
    
    return player_check and destination_check

def get_square_info():
    for size in range(2, N + 1):
        for r in range(1, N - size + 2):
            for c in range(1, N - size + 2):
                tmp_map = copy.deepcopy(MAP)
                
                for m in range(M):
                    if player[m].escape == True: continue
                    
                    tmp_map[player[m].r][player[m].c] = m + PLAYER_NUMBER
                
                tmp_map[destination.r][destination.c] = DESTINATION
                
                if rotate_check(tmp_map, r, c, size) == True:
                    return RCS(r, c, size)
	
	# for debug
    return RCS(-1, -1, -1)

def rotate(map, sr, sc, size):
    tmp_map = [[0] * MAX for _ in range(MAX)]
    
    for r in range(size):
        for c in range(size):
            tmp_map[r][c] = map[sr + r][sc + c]
    
    for r in range(size):
        for c in range(size):
            map[sr + r][sc + c] = tmp_map[size - 1 - c][r]
     
def rotate_rc(rce, square_info):
    tmp_map = [[0] * MAX for _ in range(MAX)]
    tmp_map[rce.r][rce.c] = 1
    
    rotate(tmp_map, square_info.r, square_info.c, square_info.size)
    
    for r in range(1, N + 1):
        for c in range(1, N + 1):
            if tmp_map[r][c] == 1:
                return RCE(r, c, 0)
    
    # for debug
    return RCE(-1, -1, 0)

def durability_down(square_info):
    sr = square_info.r
    er = square_info.r + square_info.size
    sc = square_info.c
    ec = square_info.c + square_info.size

    for r in range(1, N + 1):
        for c in range(1, N + 1):
            if MAP[r][c] == 0: continue

            if sr <= r < er and sc <= c < ec:
                MAP[r][c] -= 1
                
def rotate_maze():
    global destination
    
    square_info = get_square_info()
    
    rotate(MAP, square_info.r, square_info.c, square_info.size)
    
    destination = rotate_rc(destination, square_info)
    
    for m in range(M):
        if player[m].escape == True: continue
        
        player[m] = rotate_rc(player[m], square_info)
    
    durability_down(square_info)
    
def simulate():
    sum = 0
    for k in range(K):
        step = move()
        
        sum += step
        
        if check() == True: break
        
        rotate_maze()
    
    print(sum)
    print(destination.r, destination.c)
        
# T = int(input())
T = 1
for tc in range(T):    
    input_data()
    
    # print_status()
    
    simulate()