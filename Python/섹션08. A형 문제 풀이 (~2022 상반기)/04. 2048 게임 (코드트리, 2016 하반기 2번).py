import copy

MAX = 20 + 5

UP = 0
RIGHT = 1
DOWN = 2
LEFT = 3

oMAP = [[0] * MAX for _ in range(MAX)]
ansMAP = [[0] * MAX for _ in range(MAX)]

num_of_cases = [0] * (5 + 5)

def input_data():             
    global N
    
    N = int(input())
        
    for r in range(1, N + 1):
        oMAP[r][1:] = map(int, input().split())
                
def print_map(map): # for debug
    for r in range(N):
        print(' '.join('%2d' % num for num in map[r][1:N + 1]))
    print("")    
    
def print_cases(): 
    print(*num_of_cases[:5])
    
def move_up():
    global ansMAP
    
    tmp_map = [[0] * MAX for _ in range(MAX)]
    
    for c in range(1, N + 1):
        index = 1
        for r in range(1, N + 1):
            if ansMAP[r][c] == 0: continue
            
            tmp_map[index][c] = ansMAP[r][c]
            index += 1
            
        for r in range(1, N):
            if tmp_map[r][c] != tmp_map[r + 1][c]: continue
            if tmp_map[r][c] == 0: break
            
            # 기준이 되는 점을 2배로
            tmp_map[r][c] *= 2
            
            # 남은 칸을 앞으로 1칸식 옮긴다.
            for tr in range(r + 1, N):
                tmp_map[tr][c] = tmp_map[tr + 1][c]
            
            tmp_map[N][c] = 0
            
    ansMAP = copy.deepcopy(tmp_map)

def move_right():
    global ansMAP
    
    tmp_map = [[0] * MAX for _ in range(MAX)]
    
    for r in range(1, N + 1):
        index = N
        for c in range(N, 0, -1):
            if ansMAP[r][c] == 0: continue
            
            tmp_map[r][index] = ansMAP[r][c]
            index -= 1
            
        for c in range(N, 1, -1):
            if tmp_map[r][c] != tmp_map[r][c - 1]: continue
            if tmp_map[r][c] == 0: break
            
            tmp_map[r][c] *= 2
            
            for tc in range(c - 1, 1, -1):
                tmp_map[r][tc] = tmp_map[r][tc - 1]
            
            tmp_map[r][1] = 0
            
    ansMAP = copy.deepcopy(tmp_map)

def move_down():
    global ansMAP
    
    tmp_map = [[0] * MAX for _ in range(MAX)]
    
    for c in range(1, N + 1):
        index = N
        for r in range(N, 0, -1):
            if ansMAP[r][c] == 0: continue
            
            tmp_map[index][c] = ansMAP[r][c]
            index -= 1
            
        for r in range(N, 1, -1):
            if tmp_map[r][c] != tmp_map[r - 1][c]: continue
            if tmp_map[r][c] == 0: break
            
            tmp_map[r][c] *= 2
            
            for tr in range(r - 1, 1, -1):
                tmp_map[tr][c] = tmp_map[tr - 1][c]
            
            tmp_map[1][c] = 0
            
    ansMAP = copy.deepcopy(tmp_map)

def move_left():
    global ansMAP
    
    tmp_map = [[0] * MAX for _ in range(MAX)]
    
    for r in range(1, N + 1):
        index = 1 # (1, 1)부터 시작
        for c in range(1, N + 1):
            if ansMAP[r][c] == 0: continue
            
            tmp_map[r][index] = ansMAP[r][c]
            index += 1
            
        for c in range(1, N):
            if tmp_map[r][c] != tmp_map[r][c + 1]: continue
            if tmp_map[r][c] == 0: break
            
            tmp_map[r][c] *= 2
            
            for tc in range(c + 1, N):
                tmp_map[r][tc] = tmp_map[r][tc + 1]
            
            tmp_map[r][N] = 0
            
    ansMAP = copy.deepcopy(tmp_map)
      
def simulate():
    global ansMAP
    
    ansMAP = copy.deepcopy(oMAP)
    
    for i in range(5):
        direction = num_of_cases[i]
        
        if direction == UP: move_up()
        elif direction == RIGHT: move_right()
        elif direction == DOWN: move_down()
        elif direction == LEFT: move_left()
        
def find_max():
    return max(max(r) for r in ansMAP)

def DFS(depth):
    global max_answer
    
    if depth == 5:
        # print_cases()
        
        simulate()
        
        tmp = find_max()
        if max_answer < tmp: max_answer = tmp
        
        return
    
    for i in range(4):
        num_of_cases[depth] = i
        DFS(depth + 1)
                            
# T = int(input())
T = 1
for tc in range(T):
    global max_answer
    
    input_data()     
    
    max_answer = 0
    
    DFS(0)
    
    print(max_answer)
                     