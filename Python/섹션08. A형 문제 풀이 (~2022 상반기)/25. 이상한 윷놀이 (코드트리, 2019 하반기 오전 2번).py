MAX = 12 + 5
WHITE = 0
RED = 1
BLUE = 2

MAP = [[0] * MAX for _ in range(MAX)]

class HORSE:
    def __init__(self, r: int, c: int, dir: int, pos: int):
        self.r = r
        self.c = c
        self.dir = dir
        self.pos = pos # position

horse = [HORSE(0, 0, 0, 0) for _ in range(10 + 3)]
hcnt = 0

board = [[[0] * (10 + 3) for _ in range(MAX)] for _ in range(MAX)]
index = [[0] * MAX for _ in range(MAX)]

# -, 오른쪽, 왼쪽, 위쪽, 아래쪽
dr = [0, 0, 0, -1, 1]
dc = [0, 1, -1, 0, 0]

def input_data():
    global N, K, MAP, hcnt, index

    N, K = map(int, input().split())
    
    MAP = [[BLUE] * MAX for _ in range(MAX)]

    for r in range(1, N + 1):
        MAP[r][1:N + 1] = map(int, input().split())

    index = [[0] * MAX for _ in range(MAX)]

    hcnt = 1 # 1번 말부터 K번 말까지
    for _ in range(K):
        r, c, dir = map(int, input().split())
        
        horse[hcnt] = HORSE(r, c, dir, index[r][c])                
        board[r][c][index[r][c]] = hcnt
        
        index[r][c] += 1
        hcnt += 1

def print_board(): # for debug
    for r in range(1, N + 1):
        for c in range(1, N + 1):
            idx = index[r][c]
            if idx == 0: continue
            
            print(f"{r}, {c} :", end=' ')
            for i in range(idx):
                print(board[r][c][i], end=' ')
            print("")
    print("")

def move_white(number):
    h = horse[number]
    sr, sc, dir = h.r, h.c, h.dir

    nr = sr + dr[dir]
    nc = sc + dc[dir]
    
    front = h.pos
    for k in range(front, index[sr][sc]):
        selected_number = board[sr][sc][k]
        
        horse[selected_number].r = nr
        horse[selected_number].c = nc
        horse[selected_number].pos = index[nr][nc]
        
        board[nr][nc][index[nr][nc]] = selected_number
        index[nr][nc] += 1

    index[sr][sc] = front

def move_red(number):
    h = horse[number]
    sr, sc, dir = h.r, h.c, h.dir

    nr = sr + dr[dir]
    nc = sc + dc[dir]
    
    front = h.pos
    for k in range(index[sr][sc] - 1, front - 1, -1):
        selected_number = board[sr][sc][k]
        
        horse[selected_number].r = nr
        horse[selected_number].c = nc
        horse[selected_number].pos = index[nr][nc]
        
        board[nr][nc][index[nr][nc]] = selected_number
        index[nr][nc] += 1

    index[sr][sc] = front

def simulation():
    change_dir = [0, 2, 1, 4, 3]
    
    for i in range(1, 1001):
        # 1번 말 부터 이동
        for h in range(1, hcnt):
            sr, sc, dir = horse[h].r, horse[h].c, horse[h].dir
            nr = sr + dr[dir]
            nc = sc + dc[dir]

            if MAP[nr][nc] == WHITE: move_white(h)
            elif MAP[nr][nc] == RED: move_red(h)
            elif MAP[nr][nc] == BLUE:
                dir = change_dir[dir]
                horse[h].dir = dir
                
                nr = sr + dr[dir]
                nc = sc + dc[dir]

                if MAP[nr][nc] == WHITE: move_white(h)
                elif MAP[nr][nc] == RED: move_red(h)
                # BLUE이면 이동하지 않음

            if index[nr][nc] >= 4: return i

    return -1

# T = int(input())
T = 1
for _ in range(T): 
    input_data()
    
    print(simulation())