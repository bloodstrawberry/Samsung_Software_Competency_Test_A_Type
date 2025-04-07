MAX = 20 + 5
WALL = -1

T = 1
MAP = [[0] * MAX for _ in range(MAX)] # 독점하고 있는 player 번호
time = [[0] * MAX for _ in range(MAX)] # 독점 시간

class Player:
    def __init__(self):
        self.r = 0
        self.c = 0
        self.dir = 0
        self.priority = [[0] * 5 for _ in range(5)]
        self.dead = False

player = [Player() for _ in range(MAX * MAX)]

# -, 위, 아래, 왼쪽, 오른쪽
dr = [0, -1, 1, 0, 0]
dc = [0, 0, 0, -1, 1]

def input_data():
    global N, M, K, MAP
    
    N, M, K = map(int, input().split())
    
    MAP = [[WALL] * MAX for _ in range(MAX)]

    for r in range(1, N + 1):
        line = list(map(int, input().split()))
        for c in range(1, N + 1):
            MAP[r][c] = line[c - 1]
            
            playerNumber = MAP[r][c]
            if playerNumber != 0:
                player[playerNumber].r = r
                player[playerNumber].c = c

    dirs = list(map(int, input().split()))
    for i in range(1, M + 1):
        player[i].dir = dirs[i - 1]

    for i in range(1, M + 1):
        for d in range(1, 5):
            player[i].priority[d][1:5] = list(map(int, input().split()))

def print_map(map): # for debug
    for r in range(1, N + 1):
        for c in range(1, N + 1):
            print(f"{map[r][c]}", end=" ")
        print("")
    print("")
    
def print_player(number): # for debug
    p = player[number]
    print(f"number {number} / ({p.r}, {p.c}) / dir {p.dir} / dead {p.dead}")

def print_player_all(): # for debug
    for m in range(1, M + 1):
        print_player(m)

def getDirection(number):
    p = player[number]
    dir = p.dir

    # 빈 공간 찾기
    for i in range(1, 5):
        next_dir = p.priority[dir][i]
        nr = p.r + dr[next_dir]
        nc = p.c + dc[next_dir]
        
        if MAP[nr][nc] == WALL: continue
        
        if time[nr][nc] == 0:
            return next_dir

    # 자신의 구역 찾기
    for i in range(1, 5):
        next_dir = p.priority[dir][i]
        nr = p.r + dr[next_dir]
        nc = p.c + dc[next_dir]
        
        if MAP[nr][nc] == number:
            return next_dir

    return -1 # for debug

def simulate():
    playerCount = M
    for i in range(1, 1001):
        for p in range(1, M + 1):
            if player[p].dead == True: continue
            r, c = player[p].r, player[p].c
            
            MAP[r][c] = p
            time[r][c] = K

        tmpMAP = [[0] * MAX for _ in range(MAX)]
        for p in range(1, M + 1):
            if player[p].dead == True: continue

            sr, sc = player[p].r, player[p].c
            dir = getDirection(p)
            nr, nc = sr + dr[dir], sc + dc[dir]
            
            # 이동 후, 해당 칸에 player가 두 명 이상 있는 경우 
            if tmpMAP[nr][nc] == 0: # 아무도 없는 경우
                player[p].r = nr
                player[p].c = nc
                player[p].dir = dir
                
                tmpMAP[nr][nc] = p
            else:
                anotherPlayer = tmpMAP[nr][nc]
                
                playerCount -= 1
                
                if anotherPlayer < p: player[p].dead = True
                else:
                    player[anotherPlayer].dead = True
                    
                    player[p].r = nr
                    player[p].c = nc
                    player[p].dir = dir
                    
                    tmpMAP[nr][nc] = p

        for r in range(1, N + 1):
            for c in range(1, N + 1):
                if tmpMAP[r][c] == 0: continue
                
                MAP[r][c] = tmpMAP[r][c]

        if playerCount == 1: return i

        for r in range(1, N + 1):
            for c in range(1, N + 1):
                if time[r][c] != 0: time[r][c] -= 1

    return -1

# T = int(input())
T = 1
for tc in range(T):   
    input_data()
    
    print(simulate())