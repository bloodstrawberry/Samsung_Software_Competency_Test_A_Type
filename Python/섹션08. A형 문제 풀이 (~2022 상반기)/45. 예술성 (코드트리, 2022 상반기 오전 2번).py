import copy

MAX = 29 + 5

T = 1

N = 0
halfN = 0
MAP = [[0] * MAX for _ in range(MAX)]
tmpMAP = [[0] * MAX for _ in range(MAX)]
visit = [[0] * MAX for _ in range(MAX)]

class GROUP:
    def __init__(self, value: int, count: int, group_number: int):
        self.value = value
        self.count = count
        self.group_number = group_number

group = [GROUP(0, 0, 0) for _ in range(MAX * MAX)]
gcnt = 0

class RC:
    def __init__(self, r: int, c: int):
        self.r = r
        self.c = c

queue = [RC(0, 0) for _ in range(MAX * MAX)]

# ↑, →, ↓, ←
dr = [-1, 0, 1, 0]
dc = [0, 1, 0, -1]

harmony = [[0] * (MAX * MAX) for _ in range(MAX * MAX)]

def input_data():
    global N, halfN, MAP
    
    N = int(input())
    
    halfN = (N + 1) // 2
    
    MAP = [[0] * MAX for _ in range(MAX)]
    
    for r in range(1, N + 1):
        MAP[r][1:N + 1] = map(int, input().split())

def print_map(map): # for debug
    for r in range(1, N + 1):
        print(' '.join('%2d' % num for num in map[r][1:N + 1]))
    print("")

def BFS(r, c, mark):    
    rp, wp = 0, 0
    value = MAP[r][c]
    
    queue[wp].r = r
    queue[wp].c = c
    wp += 1
    
    visit[r][c] = mark

    while rp < wp:
        out = queue[rp]
        rp += 1
        
        for i in range(4):
            nr = out.r + dr[i]
            nc = out.c + dc[i]
            
            if nr < 1 or nc < 1 or nr > N or nc > N: continue
            if MAP[nr][nc] != value or visit[nr][nc] != 0: continue
            
            queue[wp].r = nr
            queue[wp].c = nc
            wp += 1
                        
            visit[nr][nc] = mark

    return GROUP(value, wp, mark)

def rotateCenter():
    global tmpMAP
    
    tmpMAP = copy.deepcopy(MAP)
    
    for r in range(1, N + 1):
        MAP[r][halfN] = tmpMAP[halfN][N + 1 - r]
        
    for c in range(1, N + 1):
        MAP[halfN][c] = tmpMAP[c][halfN]

def rotate(sr, sc):
    size = N // 2
    
    for r in range(size):
        for c in range(size):
            tmpMAP[r][c] = MAP[sr + r][sc + c]
            
    for r in range(size):
        for c in range(size):
            MAP[sr + r][sc + c] = tmpMAP[size - 1 - c][r]

def makeHarmony():
    for r in range(1, N + 1):
        for c in range(1, N + 1):
            for i in range(4):
                nr = r + dr[i]
                nc = c + dc[i]
                
                if nr < 1 or nc < 1 or nr > N or nc > N: continue
                
                if visit[r][c] == visit[nr][nc]: continue
                
                harmony[visit[r][c]][visit[nr][nc]] += 1 # harmony[A][B]++;
                harmony[visit[nr][nc]][visit[r][c]] += 1 # harmony[B][A]++;

    for r in range(1, N * N + 1):
        for c in range(1, N * N + 1):
            harmony[r][c] //= 2

def getScore():
    score = 0
    for i in range(gcnt - 1):
        for k in range(i + 1, gcnt):
            a = group[i]
            b = group[k]
            
            score \
                += ((a.count + b.count) * a.value * b.value * harmony[a.group_number][b.group_number])
            
    return score

def simulate():
    global visit, gcnt, harmony
    
    score = 0
    for round in range(4):
        visit = [[0] * MAX for _ in range(MAX)]

        gcnt = 0
        
        group_number = 1
        for r in range(1, N + 1):
            for c in range(1, N + 1):
                if visit[r][c] != 0: continue
                
                ret = BFS(r, c, group_number)
                group[gcnt] = ret
                gcnt += 1
                group_number += 1

        harmony = [[0] * (MAX * MAX) for _ in range(MAX * MAX)]

        makeHarmony()
        
        score += getScore()

        rotateCenter()
        
        rotate(1, 1)
        rotate(halfN + 1, 1)
        rotate(1, halfN + 1)
        rotate(halfN + 1, halfN + 1)

    return score

# T = int(input())
T = 1
for tc in range(T):    
    input_data()
    
    print(simulate())
