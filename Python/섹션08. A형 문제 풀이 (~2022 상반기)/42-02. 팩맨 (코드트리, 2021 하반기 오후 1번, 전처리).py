import copy

MAX = 4 + 3
MAX_DIR = 8 + 2

grid = [[False] * MAX for _ in range(MAX)]
dead_body = [[0] * MAX for _ in range(MAX)]

class packman:
    def __init__(self, r: int, c: int):
        self.r = r
        self.c = c
    
packman = packman(0, 0)

monster = [[[0] * MAX_DIR for _ in range(MAX)] for _ in range(MAX)] # (r, c)에 dir 방향의 몬스터 수

num_of_cases = [0] * 10
position = [
    [1, 1, 1], [1, 1, 2], [1, 1, 3], [1, 1, 4],
    [1, 2, 1], [1, 2, 2], [1, 2, 3], [1, 2, 4],
    [1, 3, 1], [1, 3, 2], [1, 3, 3], [1, 3, 4],
    [1, 4, 1], [1, 4, 2], [1, 4, 3], [1, 4, 4],
    [2, 1, 1], [2, 1, 2], [2, 1, 3], [2, 1, 4],
    [2, 2, 1], [2, 2, 2], [2, 2, 3], [2, 2, 4],
    [2, 3, 1], [2, 3, 2], [2, 3, 3], [2, 3, 4],
    [2, 4, 1], [2, 4, 2], [2, 4, 3], [2, 4, 4],
    [3, 1, 1], [3, 1, 2], [3, 1, 3], [3, 1, 4],
    [3, 2, 1], [3, 2, 2], [3, 2, 3], [3, 2, 4],
    [3, 3, 1], [3, 3, 2], [3, 3, 3], [3, 3, 4],
    [3, 4, 1], [3, 4, 2], [3, 4, 3], [3, 4, 4],
    [4, 1, 1], [4, 1, 2], [4, 1, 3], [4, 1, 4],
    [4, 2, 1], [4, 2, 2], [4, 2, 3], [4, 2, 4],
    [4, 3, 1], [4, 3, 2], [4, 3, 3], [4, 3, 4],
    [4, 4, 1], [4, 4, 2], [4, 4, 3], [4, 4, 4]
]

# -, ↑, ←, ↓, →
dr4 = [0, -1, 0, 1, 0]
dc4 = [0, 0, -1, 0, 1]

# -, ↑, ↖, ←, ↙, ↓, ↘, →, ↗ 
dr8 = [0, -1, -1, 0, 1, 1, 1, 0, -1]
dc8 = [0, 0, -1, -1, -1, 0, 1, 1, 1]

def input_data():
    global M, TURN, packman, grid, dead_body, monster
    
    M, TURN = map(int, input().split())
    packman.r, packman.c = map(int, input().split())

    monster = [[[0] * MAX_DIR for _ in range(MAX)] for _ in range(MAX)]

    for _ in range(M):
        r, c, d = map(int, input().split())
        monster[r][c][d] += 1

    dead_body = [[0] * MAX for _ in range(MAX)]

    for r in range(MAX):
        for c in range(MAX):
            grid[r][c] = True

    for r in range(1, 5):
        for c in range(1, 5):
            grid[r][c] = False

def print_dead_body(): # for debug
    print("Dead Body")
    for r in range(1, 5):
        print(*dead_body[1][1:5])
    print("")

def print_monster(): # for debug
    for r in range(1, 5):
        for c in range(1, 5):
            print(f"({r}, {c})")
            for d in range(1, 9):
                print(f"{d} : {monster[r][c][d]} / ", end='')
            print("")
    print("")

def move_monster():
    global monster
    
    tmp_monster = [[[0] * MAX_DIR for _ in range(MAX)] for _ in range(MAX)]
    for r in range(1, 5):
        for c in range(1, 5):
            for d in range(1, 9):
                if monster[r][c][d] == 0: continue

                flag = False
                for i in range(8): # 반시계 방향 회전
                    dir = (d + i - 1 + 8) % 8 + 1
                    nr = r + dr8[dir]
                    nc = c + dc8[dir]

                    if (nr == packman.r and nc == packman.c) \
                        or dead_body[nr][nc] != 0 \
                        or grid[nr][nc] == True: continue                        
                    else:
                        tmp_monster[nr][nc][dir] += monster[r][c][d]
                        flag = True
                        break
                
                # 이동 불가
                if flag == False: tmp_monster[r][c][d] += monster[r][c][d]

    monster = copy.deepcopy(tmp_monster)

def get_monster(step):
    tmp_packman = copy.deepcopy(packman)    
    tmp_monster = [[[0] * MAX_DIR for _ in range(MAX)] for _ in range(MAX)]
    
    tmp_monster = copy.deepcopy(monster)

    count = 0
    for i in range(3):
        nr = tmp_packman.r + dr4[position[step][i]]
        nc = tmp_packman.c + dc4[position[step][i]]

        if grid[nr][nc]: return -1

        for d in range(1, 9):
            count += tmp_monster[nr][nc][d]
            tmp_monster[nr][nc][d] = 0

        tmp_packman.r = nr
        tmp_packman.c = nc

    return count

def move_packman(step):
    global packman
    
    for i in range(3):
        nr = packman.r + dr4[position[step][i]]
        nc = packman.c + dc4[position[step][i]]

        for d in range(1, 9):
            if monster[nr][nc][d] == 0: continue
            
            monster[nr][nc][d] = 0
            dead_body[nr][nc] = 3

        packman.r = nr
        packman.c = nc

def disappear():
    for r in range(1, 5):
        for c in range(1, 5):
            if dead_body[r][c] != 0: dead_body[r][c] -= 1

def simulate():
    for t in range(TURN):
        egg = [[[0] * MAX_DIR for _ in range(MAX)] for _ in range(MAX)]
        # 1. 몬스터 복제 시도
        egg = copy.deepcopy(monster)

		# 2. 몬스터 이동
        move_monster()

        step, maxMonster = -1, -1
        for i in range(64):
            tmp = get_monster(i)
            if tmp > maxMonster:
                maxMonster = tmp
                step = i

		# 3. 팩맨 이동
        move_packman(step)
        
        # 4. 몬스터 시체 소멸
        disappear()

		# 5. 몬스터 복제 완성
        for r in range(1, 5):
            for c in range(1, 5):
                for d in range(1, 9):
                    monster[r][c][d] += egg[r][c][d]

def get_answer():
    sum = 0
    for r in range(1, 5):
        for c in range(1, 5):
            for d in range(1, 9):
                sum += monster[r][c][d]
    
    return sum

# T = int(input())
T = 1
for tc in range(T):    
    input_data()
    
    simulate()
    
    print(get_answer())
