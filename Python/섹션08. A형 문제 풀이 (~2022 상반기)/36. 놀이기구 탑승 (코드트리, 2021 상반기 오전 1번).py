MAX = 20 + 5
INF = 0x7fff0000

WALL = -1

MAP = [[0] * MAX for _ in range(MAX)]

student = [0] * (MAX * MAX)
love = [[False] * (MAX * MAX) for _ in range(MAX * MAX)]

# ↑, →, ↓, ←
dr = [-1, 0, 1, 0]
dc = [0, 1, 0, -1]

class SEAT:
    def __init__(self, like: int, empty: int, r: int, c: int):
        self.like = like # 주변의 좋아하는 친구 수
        self.empty = empty # 주변의 빈 자리 수
        self.r = r
        self.c = c

def input_data():
    global N, MAP, love
    
    N = int(input())
    
    MAP = [[WALL] * MAX for _ in range(MAX)]

    for r in range(1, N + 1):
        for c in range(1, N + 1):
            MAP[r][c] = 0

    love = [[False] * (MAX * MAX) for _ in range(MAX * MAX)]
    
    for i in range(N * N):
        num, one, two, three, four = map(int, input().split())
        
        student[i] = num
        love[num][one] = True
        love[num][two] = True
        love[num][three] = True
        love[num][four] = True
        
def print_map(): # for debug
    for r in range(1, N + 1):
        print(*MAP[r][1:N + 1])
    print("")        

def get_seat_info(index, r, c):
    like, empty = 0, 0
    for i in range(4):
        nr = r + dr[i]
        nc = c + dc[i]
        
        if MAP[nr][nc] == WALL: continue
        
        if MAP[nr][nc] == 0: empty += 1
        elif love[index][MAP[nr][nc]] == True: like += 1
        
    return SEAT(like, empty, r, c)

# a가 우선순위가 더 높으면 true
def is_priority(a, b):
    if a.like != b.like: return a.like > b.like
    if a.empty != b.empty: return a.empty > b.empty
    if a.r != b.r: return a.r < b.r
    
    return a.c < b.c

def simulate():
    for i in range(N * N):
        index = student[i]
        
        wanted = SEAT(0, 0, INF, INF)
        for r in range(1, N + 1):
            for c in range(1, N + 1):
                if MAP[r][c] != 0: continue
                
                tmp = get_seat_info(index, r, c)
                
                if is_priority(tmp, wanted): 
                    wanted = tmp
                
        MAP[wanted.r][wanted.c] = index

def get_answer():
    board = [0, 1, 10, 100, 1000]
    
    score = 0
    for r in range(1, N + 1):
        for c in range(1, N + 1):
            index = MAP[r][c]
            count = 0
            for i in range(4):
                nr = r + dr[i]
                nc = c + dc[i]
                
                if MAP[nr][nc] == WALL: continue
                
                if love[index][MAP[nr][nc]]: count += 1
                
            score += board[count]
            
    return score

# T = int(input())
T = 1
for tc in range(T):    
    input_data()
    
    simulate()
    
    print(get_answer())