import copy

MAX = 8 + 5
INF = 0x7fff0000

EMPTY = 0
OTHER = 6 # 상대편 말
MARK = 7

MAP = [[0] * MAX for _ in range(MAX)]
tmpMAP = [[0] * MAX for _ in range(MAX)]

num_of_cases = [0] * MAX

class CHESS:
    def __init__(self, r: int, c: int, number: int):
        self.r = r
        self.c = c
        self.number = number

chess = [CHESS(0, 0, 0) for _ in range(8 + 2)]
cidx = 0

# ↑, →, ↓, ←
dr = [-1, 0, 1, 0]  
dc = [0, 1, 0, -1]

def input_data():
    global N, M, MAP, cidx

    N, M = map(int, input().split())

    MAP = [[OTHER] * MAX for _ in range(MAX)] # 벽

    for r in range(1, N + 1):
        MAP[r][1:M + 1] = map(int, input().split())

    cidx = 0
    for r in range(1, N + 1):
        for c in range(1, M + 1):
            if MAP[r][c] == EMPTY or MAP[r][c] == OTHER: continue
            
            chess[cidx] = CHESS(r, c, MAP[r][c])
            cidx += 1

def print_map(): # for debug
    for r in range(N + 2):
        print(*tmpMAP[r][:M + 2])
    print("")            

def print_cases():
    print(*num_of_cases[:cidx])
    print("")

def check_area(sr, sc, direction):
    r, c = sr, sc
    while True:
        r += dr[direction]
        c += dc[direction]

        if tmpMAP[r][c] == OTHER: return

        tmpMAP[r][c] = MARK

def simulate():
    global tmpMAP
    
    tmpMAP = copy.deepcopy(MAP)
    
    for i in range(cidx):
        sr = chess[i].r
        sc = chess[i].c
        chessNumber = chess[i].number
        direction = num_of_cases[i]

        if chessNumber == 1:
            check_area(sr, sc, direction)
        elif chessNumber == 2:
            inverse = direction + 2
            if inverse > 3: inverse -= 4
            
            check_area(sr, sc, direction)
            check_area(sr, sc, inverse)
        elif chessNumber == 3:
            next_dir = direction + 1
            if next_dir == 4: next_dir = 0
            
            check_area(sr, sc, direction)
            check_area(sr, sc, next_dir)
        elif chessNumber == 4:
            for i in range(4):
                if i == direction: continue
                
                check_area(sr, sc, i)
        elif chessNumber == 5:
            for i in range(4):
                check_area(sr, sc, i)

def getArea():
    sum = 0
    for r in range(1, N + 1):
        for c in range(1, M + 1):
            if tmpMAP[r][c] == EMPTY:
                sum += 1
                
    return sum

def DFS(depth):
    global min_answer

    if depth == cidx:
        # print_cases()    
        simulate()
        #print_map()
        
        tmp = getArea()
        if tmp < min_answer: min_answer = tmp
        
        return

    for i in range(4):
        num_of_cases[depth] = i
        DFS(depth + 1)

# T = int(input())
T = 1
for tc in range(T): 
    global min_answer
    
    input_data()
    
    min_answer = INF
    
    DFS(0)
    
    print(min_answer)