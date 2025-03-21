import copy

MAX = 100 + 10

FLIP_UPDOWN = 1
FLIP_LEFTRIGHT = 2
CLOCKWISE = 3
COUNTER_CLOCKWISE = 4
SPLIT_CLOCKWISE = 5
SPLIT_COUNTER_CLOCKWISE = 6

MAP = [[0] * MAX for _ in range(MAX)]

def input_data():
    global N, M, R
    N, M, R = map(int, input().split())

    for r in range(1, N + 1):
        MAP[r][1:M + 1] = map(int, input().split())

def print_map():
    for r in range(1, N + 1):
        print(*MAP[r][1:M + 1])
                
def flip_up_down():
    temp = copy.deepcopy(MAP)
    
    for r in range(1, N + 1):
        for c in range(1, M + 1):
            MAP[r][c] = temp[N + 1 - r][c]
    
def flip_left_right():
    temp = copy.deepcopy(MAP)
    
    for r in range(1, N + 1):
        for c in range(1, M + 1):
            MAP[r][c] = temp[r][M + 1 - c]
    
def clockwise():
    global N, M
    
    temp = copy.deepcopy(MAP)
    
    N, M = M, N
    
    for r in range(1, N + 1):
        for c in range(1, M + 1):
            MAP[r][c] = temp[M + 1 - c][r]
    
def counter_clockwise():
    global N, M
    
    temp = copy.deepcopy(MAP)
    
    N, M = M, N
    
    for r in range(1, N + 1):
        for c in range(1, M + 1):
            MAP[r][c] = temp[c][N + 1 - r]
            
def split_clockwise():       
    global N, M
         
    temp = copy.deepcopy(MAP)
    
    halfN = (N // 2)
    halfM = (M // 2)
    
    sr1, sc1 = 1, 1
    sr2, sc2 = 1, halfM + 1
    sr3, sc3 = halfN + 1, halfM + 1
    sr4, sc4 = halfN + 1, 1
    
    for r in range(halfN):
        for c in range(halfM):
            MAP[sr2 + r][sc2 + c] = temp[sr1 + r][sc1 + c]
            
    for r in range(halfN):
        for c in range(halfM):
            MAP[sr3 + r][sc3 + c] = temp[sr2 + r][sc2 + c]
    
    for r in range(halfN):
        for c in range(halfM):
            MAP[sr4 + r][sc4 + c] = temp[sr3 + r][sc3 + c]
    
    for r in range(halfN):
        for c in range(halfM):
            MAP[sr1 + r][sc1 + c] = temp[sr4 + r][sc4 + c]
    
def split_counter_clockwise():    
    global N, M
            
    temp = copy.deepcopy(MAP)
    
    halfN = (N // 2)
    halfM = (M // 2)
    
    sr1, sc1 = 1, 1
    sr2, sc2 = 1, halfM + 1
    sr3, sc3 = halfN + 1, halfM + 1
    sr4, sc4 = halfN + 1, 1
    
    for r in range(halfN):
        for c in range(halfM):
            MAP[sr1 + r][sc1 + c] = temp[sr2 + r][sc2 + c]
            
    for r in range(halfN):
        for c in range(halfM):
            MAP[sr2 + r][sc2 + c] = temp[sr3 + r][sc3 + c]
    
    for r in range(halfN):
        for c in range(halfM):
            MAP[sr3 + r][sc3 + c] = temp[sr4 + r][sc4 + c]
    
    for r in range(halfN):
        for c in range(halfM):
            MAP[sr4 + r][sc4 + c] = temp[sr1 + r][sc1 + c]
            
input_data()

COMMAND = map(int, input().split())

for command in COMMAND:
    if command == FLIP_UPDOWN: flip_up_down()
    elif command == FLIP_LEFTRIGHT: flip_left_right()
    elif command == CLOCKWISE: clockwise()
    elif command == COUNTER_CLOCKWISE: counter_clockwise()
    elif command == SPLIT_CLOCKWISE: split_clockwise()
    elif command == SPLIT_COUNTER_CLOCKWISE: split_counter_clockwise()
    
print_map()
    