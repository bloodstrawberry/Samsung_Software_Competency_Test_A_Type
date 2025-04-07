# PyPy3

MAX_H = 30 + 5
MAX_N = 10 + 5

MAP = [[0] * MAX_N for _ in range(MAX_H)]

num_of_cases = [0] * (MAX_H * MAX_H)

class RC:
    def __init__(self, r: int, c: int):
        self.r = r
        self.c = c

ladder = [RC(0, 0) for _ in range(MAX_H * MAX_N)]
lcnt = 0

def input_data():
    global C, M, R, MAP
    
    C, M, R = map(int, input().split())
    
    MAP = [[0] * MAX_N for _ in range(MAX_H)]
    
    for _ in range(M):
        r, c = map(int, input().split())
        MAP[r][c] = 1

def print_map(): # for debug    
    for r in range(1, R + 1):
        print(*MAP[r][1:C + 1])
    print("")
    
def print_cases():
    print(*num_of_cases[:lcnt])
    print("")

def check():
    start = [0] * MAX_N    
    for c in range(1, C + 1): start[c] = c
    
    for r in range(1, R + 1):
        for c in range(1, C + 1):
            if MAP[r][c] == 0: continue
            
            start[c], start[c + 1] = start[c + 1], start[c]
            
    for c in range(1, C + 1):
        if start[c] != c: return False

    return True

def DFS(depth, start, setup):
    global PASS

    if depth == setup:
        # print_cases()
                
        if check() == True: PASS = True
        
        return

    for i in range(start, lcnt):       
        # num_of_cases[depth] = i
        
        r, c = ladder[i].r, ladder[i].c
        
        if MAP[r][c - 1] == 1 or MAP[r][c + 1] == 1: continue
        
        MAP[r][c] = 1
        DFS(depth + 1, i + 1, setup)
        MAP[r][c] = 0
        
def simulate():
    global PASS

    if check() == True: return 0

    for setup in range(1, 4):
        DFS(0, 0, setup)
        
        if PASS == True: return setup

    return -1

def get_empty_ladder():
    global lcnt
    
    lcnt = 0
    for r in range(1, R + 1):
        for c in range(1, C):
            if (MAP[r][c] == 0 and MAP[r][c + 1] == 0) and \
                (MAP[r][c] == 0 and MAP[r][c - 1] == 0):
                    ladder[lcnt].r = r
                    ladder[lcnt].c = c
                    lcnt += 1

# T = int(input())
T = 1
for tc in range(T):
    global PASS
    
    input_data()
    
    get_empty_ladder()
    
    PASS = False
 
    print(simulate())