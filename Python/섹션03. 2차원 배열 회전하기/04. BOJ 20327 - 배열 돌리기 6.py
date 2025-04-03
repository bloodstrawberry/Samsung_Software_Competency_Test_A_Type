MAX = 128 + 10

FLIP_UPDOWN = 1
FLIP_LEFTRIGHT = 2
CLOCKWISE = 3
COUNTER_CLOCKWISE = 4
SPLIT_UPDOWN = 5
SPLIT_LEFTRIGHT = 6
SPLIT_CLOCKWISE = 7
SPLIT_COUNTER_CLOCKWISE = 8

MAP = [[0] * MAX for _ in range(MAX)]
temp = [[0] * MAX for _ in range(MAX)]

def input_data():
    global N, R, S
    N, R = map(int, input().split())

    S = (1 << N)

    for r in range(1, S + 1):
        MAP[r][1:S + 1] = map(int, input().split())

def print_map():
    for r in range(1, S + 1):
        print(*MAP[r][1:S + 1])
    print("")
                
def flip_up_down_divide(sr, sc, size):
    for r in range(size):
        for c in range(size):
            temp[r][c] = MAP[sr + r][sc + c]
            
    for r in range(size):
        for c in range(size):
            MAP[sr + r][sc + c] = temp[size - 1 - r][c]
                        
def flip_up_down(level):
    divide = (1 << level)
    
    for r in range(1, S + 1, divide):
        for c in range(1, S + 1, divide):
            flip_up_down_divide(r, c, divide)

def flip_left_right_divide(sr, sc, size):
    for r in range(size):
        for c in range(size):
            temp[r][c] = MAP[sr + r][sc + c]
            
    for r in range(size):
        for c in range(size):
            MAP[sr + r][sc + c] = temp[r][size - 1 - c]
                        
def flip_left_right(level):
    divide = (1 << level)
    
    for r in range(1, S + 1, divide):
        for c in range(1, S + 1, divide):
            flip_left_right_divide(r, c, divide)

def clockwise_divide(sr, sc, size):
    for r in range(size):
        for c in range(size):
            temp[r][c] = MAP[sr + r][sc + c]
            
    for r in range(size):
        for c in range(size):
            MAP[sr + r][sc + c] = temp[size - 1 - c][r]
                        
def clockwise(level):
    divide = (1 << level)
    
    for r in range(1, S + 1, divide):
        for c in range(1, S + 1, divide):
            clockwise_divide(r, c, divide)

def counter_clockwise_divide(sr, sc, size):
    for r in range(size):
        for c in range(size):
            temp[r][c] = MAP[sr + r][sc + c]
            
    for r in range(size):
        for c in range(size):
            MAP[sr + r][sc + c] = temp[c][size - 1 - r]
                        
def counter_clockwise(level):
    divide = (1 << level)
    
    for r in range(1, S + 1, divide):
        for c in range(1, S + 1, divide):
            counter_clockwise_divide(r, c, divide)

def split_up_down(level):
    flip_up_down(N)
    flip_up_down(level)
    
def split_left_right(level):
    flip_left_right(N)
    flip_left_right(level)
    
def split_clockwise(level):
    clockwise(N)
    counter_clockwise(level)

def split_counter_clockwise(level):
    counter_clockwise(N)
    clockwise(level)
    
input_data()

for _ in range(R) :
    COMMAND, level = map(int, input().split())
    
    if COMMAND == FLIP_UPDOWN: flip_up_down(level)
    elif COMMAND == FLIP_LEFTRIGHT: flip_left_right(level)
    elif COMMAND == CLOCKWISE: clockwise(level)
    elif COMMAND == COUNTER_CLOCKWISE: counter_clockwise(level)
    elif COMMAND == SPLIT_UPDOWN: split_up_down(level)
    elif COMMAND == SPLIT_LEFTRIGHT: split_left_right(level)
    elif COMMAND == SPLIT_CLOCKWISE: split_clockwise(level)
    elif COMMAND == SPLIT_COUNTER_CLOCKWISE: split_counter_clockwise(level)
        
print_map()
