import copy

MAX = 50 + 5

TMINT_CHOKO_MILK = 111
TMINT_CHOKO = 1 + 10
TMINT_MILK = 1 + 100
CHOKO_MILK = 100 + 10
MILK = 100
CHOKO = 10
TMINT = 1

UP = 0
DOWN = 1
LEFT = 2
RIGHT = 3

F = [[''] * MAX for _ in range(MAX)]
B = [[0] * MAX for _ in range(MAX)]

class STUDENT:
    def __init__(self, food: int, believe: int, isLeader: bool, defense: int, row: int, col: int):
        self.food = food # 신봉하는 음식
        self.believe = believe # 신앙심
        self.isLeader = isLeader # 대표
        self.defense = defense # 방어 여부
        self.row = row # 대표자 선정을 위한 값
        self.col = col

student = [[STUDENT(0, 0, False, 0, 0, 0) for _ in range(MAX)] for _ in range(MAX)]
candidates = [STUDENT(0, 0, False, 0, 0, 0) for _ in range(MAX * MAX)]
ccnt = 0

group = [[STUDENT(0, 0, False, 0, 0, 0) for _ in range(MAX * MAX)] for _ in range(3 + 1)]
index = [0] * (3 + 1)

class RC:
    def __init__(self, r: int, c: int):
        self.r = r
        self.c = c

queue = [RC(0, 0) for _ in range(MAX * MAX)]
visit = [[False] * MAX for _ in range(MAX)]

# 위, 아래, 왼쪽, 오른쪽
dr = [-1, 1, 0, 0]
dc = [0, 0, -1, 1]

def input_data():
    global N, T
    
    N, T = map(int, input().split())
    
    for r in range(1, N + 1):
        F[r][1: N + 1] = list(input())

    for r in range(1, N + 1):
        B[r][1:N + 1] = map(int, input().split())
    
    for r in range(1, N + 1):
        for c in range(1, N + 1):        
            student[r][c].believe = B[r][c]
            student[r][c].isLeader = False # 초기화
            student[r][c].defense = 0 # 초기화
            student[r][c].row = r
            student[r][c].col = c

            if F[r][c] == 'T': student[r][c].food = TMINT
            elif F[r][c] == 'C': student[r][c].food = CHOKO
            elif F[r][c] == 'M': student[r][c].food = MILK

def printBelieve():  # for debug
    for r in range(1, N + 1):
        print(' '.join(str(student[r][c].believe) for c in range(1, N + 1)))
    print()

def printFood():  # for debug
    for r in range(1, N + 1):
        print(' '.join(f"{student[r][c].food:3d}" for c in range(1, N + 1)))
    print()

def printGroup():  # for debug
    for g in range(1, 4):
        print(f"group {g} ", end='')
        for i in range(index[g]):
            s = group[g][i]
            print(f"({s.row}, {s.col})", end=' ')
        print()

def morning():
    for r in range(1, N + 1):
        for c in range(1, N + 1):
            student[r][c].believe += 1

# a가 우선순위가 더 높으면 true
def is_priority(a, b):
    if a.believe != b.believe: return a.believe > b.believe
    if a.row != b.row: return a.row < b.row
    
    return a.col < b.col

def BFS(r, c):
    global ccnt, candidates
    
    rp, wp = 0, 0
    
    queue[wp].r = r
    queue[wp].c = c
    wp += 1
    
    visit[r][c] = True
    
    ccnt = 0
    
    candidates[ccnt] = copy.deepcopy(student[r][c])
    ccnt += 1
    
    while rp < wp:
        out = queue[rp]
        rp += 1
        
        for i in range(4):
            nr = out.r + dr[i]
            nc = out.c + dc[i]
            
            if nr < 1 or nc < 1 or nr > N or nc > N: continue
            if visit[nr][nc] == True: continue
            
            # 인접한 학생들과 신봉 음식이 완전히 같은 경우에만 그룹을 형성
            if student[out.r][out.c].food != student[nr][nc].food: continue
            
            queue[wp].r = nr
            queue[wp].c = nc
            wp += 1
            
            visit[nr][nc] = True
            
            candidates[ccnt] = copy.deepcopy(student[nr][nc])
            ccnt += 1

    leader = STUDENT(0, 0, False, 0, 0, 0)
    for i in range(ccnt):
        if is_priority(candidates[i], leader):
            leader = candidates[i]

    student[leader.row][leader.col].isLeader = True
    student[leader.row][leader.col].believe += (ccnt - 1)

    for i in range(ccnt):
        c = candidates[i]
        if c.row == leader.row and c.col == leader.col: continue
                
        student[c.row][c.col].believe -= 1

def lunch():
    for r in range(1, N + 1):
        for c in range(1, N + 1):
            visit[r][c] = False
            student[r][c].isLeader = False

    for r in range(1, N + 1):
        for c in range(1, N + 1):
            if visit[r][c] == True: continue
            
            BFS(r, c)

def get_group_number(food):
    if food == TMINT_CHOKO_MILK: return 3
    elif food in (TMINT, CHOKO, MILK): return 1
    
    return 2

def mix_food(sFood, nFood):
    return sFood | nFood

def dinner():
    global index

    index = [0] * (3 + 1)
    
    # 그룹 별 분리
    for r in range(1, N + 1):
        for c in range(1, N + 1):
            s = student[r][c]
            
            if s.isLeader == False: continue
            
            group_number = get_group_number(s.food)
            group[group_number][index[group_number]] = copy.deepcopy(s)
            index[group_number] += 1

    for g in range(1, 4):
        g_index = index[g]
        for i in range(g_index - 1):
            for k in range(i + 1, g_index):
                a = group[g][i]
                b = group[g][k]
                
                if is_priority(a, b) == False:
                    group[g][i], group[g][k] = b, a
     
    # 전파 시작                   
    for g in range(1, 4):
        for i in range(index[g]):
            
            gr = group[g][i].row
            gc = group[g][i].col
            
            spreader = copy.deepcopy(student[gr][gc])
            
            # 방어 상태에서는 대표자가 되어도 전파를 하지 않음.
            if spreader.defense != 0: continue

            sr, sc = spreader.row, spreader.col
            
            # 원본의 신앙심을 1로 변경
            student[sr][sc].believe = 1

            x = spreader.believe - 1 # 간절함
            dir = spreader.believe % 4

            while True:
                nr = sr + dr[dir]
                nc = sc + dc[dir]

                # 격자 밖으로 나가거나 간절함이 0이 되면 전파 종료
                if nr < 1 or nc < 1 or nr > N or nc > N or x == 0: break

                # 전파 대상
                next_s = student[nr][nc]

                # 전파 대상이 전파자와 신봉 음식이 완전히 같은 경우
                if next_s.food == spreader.food:
                    # 전파를 하지 않고 바로 다음으로 진행
                    sr, sc = nr, nc                    
                    continue

                # 전파 대상이 전파자와 신봉 음식이 다른 경우, 전파 시도
                y = next_s.believe # 신앙심
                
                # 대표자에게 전파가 시도된 학생은 방어 상태
                student[next_s.row][next_s.col].defense = 1

                if x > y: # 강한 전파 성공
                    x -= (y + 1)
                    if x < 0: x = 0
                    
                    student[next_s.row][next_s.col].believe += 1
                    student[next_s.row][next_s.col].food = spreader.food
                else: # x <= y, 약한 전파 헝공
                    student[next_s.row][next_s.col].believe += x
                    student[next_s.row][next_s.col].food = mix_food(spreader.food, next_s.food)
                    
                    x = 0
                    
                    break

                sr, sc = nr, nc

    for r in range(1, N + 1):
        for c in range(1, N + 1):
            student[r][c].defense = 0

def print_answer():
    sum = [0] * (TMINT_CHOKO_MILK + 1)
    for r in range(1, N + 1):
        for c in range(1, N + 1):
            sum[student[r][c].food] += student[r][c].believe

    outputIndex = [TMINT_CHOKO_MILK, TMINT_CHOKO, TMINT_MILK, CHOKO_MILK, MILK, CHOKO, TMINT]
    
    for i in range(7):
        print(sum[outputIndex[i]], end=" ")
    print("")
            
def simulate():
    for _ in range(T):
        morning()
        lunch()
        dinner()

        print_answer()

# test_case = int(input())
test_case = 1
for tc in range(test_case):  
    input_data()
        
    simulate()