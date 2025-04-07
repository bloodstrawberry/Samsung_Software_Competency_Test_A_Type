MAX = 10 + 3
MAX_K = 10000 + 500

START = 4
END = 9

WALL = -1

MAP = [[0] * MAX for _ in range(MAX)]

TYPE = [0] * MAX_K
R = [0] * MAX_K
C = [0] * MAX_K

def input_data():
    global MAP, K
    
    MAP = [[0] * MAX for _ in range(MAX)]

    MAP[0][10] = MAP[1][10] = MAP[2][10] = MAP[3][10] = WALL
    MAP[10][0] = MAP[10][1] = MAP[10][2] = MAP[10][3] = WALL

    K = int(input())

    for k in range(K):
        TYPE[k], R[k], C[k] = map(int, input().split())

def print_map(): # for debug    
    for r in range(11):
        print(*MAP[r][:11])
    print("")

def move_red(type, sr, sc):
    c = sc
    if type == 1:
        while True:
            if MAP[sr][c + 1] != 0: break
            c += 1
        
        MAP[sr][c] = 1
    elif type == 2:
        while True:
            if MAP[sr][c + 2] != 0: break
            c += 1
        
        MAP[sr][c] = MAP[sr][c + 1] = 1
    elif type == 3:
        while True:
            if MAP[sr][c + 1] != 0: break
            if MAP[sr + 1][c + 1] != 0: break      
            c += 1
        
        MAP[sr][c] = MAP[sr + 1][c] = 1

def move_yellow(type, sr, sc):
    r = sr
    if type == 1:
        while True:
            if MAP[r + 1][sc] != 0: break
            r += 1
            
        MAP[r][sc] = 1
    elif type == 2:
        while True:
            if MAP[r + 1][sc] != 0: break
            if MAP[r + 1][sc + 1] != 0: break            
            r += 1
            
        MAP[r][sc] = MAP[r][sc + 1] = 1
    elif type == 3:
        while True:
            if MAP[r + 2][sc] != 0: break
            r += 1
            
        MAP[r][sc] = MAP[r + 1][sc] = 1

def delete_red(col):
    for c in range(col, START, -1):
        for r in range(4):
            MAP[r][c] = MAP[r][c - 1]
            
    for r in range(4): MAP[r][START] = 0

def delete_yellow(row):
    for r in range(row, START, -1):
        for c in range(4):
            MAP[r][c] = MAP[r - 1][c]
            
    for c in range(4): MAP[START][c] = 0

def get_score_red():
    for c in range(START + 2, END + 1):
        cnt = sum(MAP[r][c] for r in range(4))
        if cnt == 4:
            delete_red(c)
            return 1
        
    return 0

def get_score_yellow():
    for r in range(START + 2, END + 1):
        cnt = sum(MAP[r][c] for c in range(4))
        if cnt == 4:
            delete_yellow(r)
            return 1
        
    return 0

def check_red():
    for r in range(4):
        if MAP[r][START + 1] == 1: return True
        
    return False

def check_yellow():
    for c in range(4):
        if MAP[START + 1][c] == 1: return True    
        
    return False

def simulate():
    score = 0
    for k in range(K):
        move_red(TYPE[k], R[k], C[k])
        move_yellow(TYPE[k], R[k], C[k])

        score += get_score_red()
        score += get_score_red()
        
        score += get_score_yellow()
        score += get_score_yellow()

        if check_red(): delete_red(END)
        if check_red(): delete_red(END)
        
        if check_yellow(): delete_yellow(END)
        if check_yellow(): delete_yellow(END)

    block_count = 0
    
    # red
    for c in range(START + 2, END + 1):
        for r in range(4):
            block_count += MAP[r][c]
            
    # yellow
    for r in range(START + 2, END + 1):
        for c in range(4):
            block_count += MAP[r][c]

    print(score)
    print(block_count)

# T = int(input())
T = 1
for tc in range(T):
    input_data()
    
    simulate()