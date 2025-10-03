MAX = 50 + 5

MAP = [[0] * MAX for _ in range(MAX)] 

class BOX:
    def __init__(self, k: int, h: int, w: int, r: int, c: int, drop: bool):
        self.k = k
        self.h = h
        self.w = w
        self.r = r
        self.c = c
        self.drop = drop

box = [BOX(0, 0, 0, 0, 0, False) for _ in range(100 + 10)]

def input_data():
        global N, M, max_box_num, MAP, box
        max_box_num = 0

        N, M = map(int, input().split())
                
        for i in range(1, 101):
            box[i].k = 0

        for r in range(0, N + 2):
            for c in range(0, N + 2):
                MAP[r][c] = -1

        for r in range(1, N + 1):
            for c in range(1, N + 1):
                MAP[r][c] = 0
                
def print_map(): # for debug
    for r in range(1, N + 1):
        print(*MAP[r][1:N + 1])
    print()                
                
def check_down(index):
    b = box[index]
    for c in range(b.c, b.c + b.w):
        if MAP[b.r + b.h][c] != 0:
            return False
    return True

def set_box(index):
    b = box[index]
    for r in range(b.r, b.r + b.h):
        for c in range(b.c, b.c + b.w):
            MAP[r][c] = index

def delete_box(index):
    b = box[index]
    for r in range(b.r, b.r + b.h):
        for c in range(b.c, b.c + b.w):
            MAP[r][c] = 0

def move_down(index):
    b = box[index]
    delete_box(index)

    while True:
        if not check_down(index):
            break
        b.r += 1
        
    set_box(index)

def check_left(index):
    b = box[index]
    for r in range(b.r, b.r + b.h):
        for c in range(1, b.c):
            if MAP[r][c] != 0:
                return False
    return True

def move_left():
    global max_box_num
    for i in range(1, max_box_num + 1):
        if box[i].drop or box[i].k == 0:
            continue
        if check_left(i):
            box[i].drop = True
            delete_box(i)
            print(i)
            return

def check_right(index):
    b = box[index]
    for r in range(b.r, b.r + b.h):
        for c in range(b.c + b.w, N + 1):
            if MAP[r][c] != 0:
                return False
    return True

def move_right():
    global max_box_num
    for i in range(1, max_box_num + 1):
        if box[i].drop or box[i].k == 0:
            continue
        if check_right(i):
            box[i].drop = True
            delete_box(i)
            print(i)
            return

def move_down_all():
    while True:
        check = True
        for i in range(1, max_box_num + 1):
            if box[i].drop or box[i].k == 0:
                continue
            if not check_down(i):
                continue
            check = False
            move_down(i)
        if check:
            break

def simulate():
    global max_box_num

    # 1. 택배 투입
    for _ in range(M):
        k, h, w, c = map(int, input().split())

        box[k].k = k # M과 최대 k가 다를 수 있음.
        box[k].h = h
        box[k].w = w
        box[k].r = 1
        box[k].c = c
        box[k].drop = False

        if max_box_num < k: max_box_num = k

        move_down(k)

    for _ in range(0, M, 2):
        # 2. 택배 하차 (좌측)
        move_left()
        move_down_all()

        # 3. 택배 하차 (우측)
        move_right()
        move_down_all()
                                
# T = int(input())
T = 1
for tc in range(T):  
    input_data()
        
    simulate()