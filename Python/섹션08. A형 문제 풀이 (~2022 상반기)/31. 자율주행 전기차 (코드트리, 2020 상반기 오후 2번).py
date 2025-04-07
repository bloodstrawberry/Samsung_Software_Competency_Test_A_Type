import copy

MAX = 20 + 5
INF = 0x7fff0000
ROAD = 0
WALL = 1

MAP = [[0] * MAX for _ in range(MAX)]
tmpMAP = [[0] * MAX for _ in range(MAX)]
visit = [[0] * MAX for _ in range(MAX)]

class RC:
    def __init__(self, r: int, c: int):
        self.r = r
        self.c = c

car = RC(0, 0)
queue = [RC(0, 0) for _ in range(MAX * MAX)]

class PEOPLE:
    def __init__(self, sr: int, sc: int, er: int, ec: int, check: bool):
        self.sr = 0
        self.sc = 0
        self.er = 0
        self.ec = 0
        self.check = False # 승객 도착 유무

people = [PEOPLE(0, 0, 0, 0, False) for _ in range(MAX * MAX)]

class INFO:
    def __init__(self, peopleNumber: int, distance: int):
        self.peopleNumber = peopleNumber
        self.distance = distance

# ↑, →, ↓, ←
dr = [-1, 0, 1, 0]
dc = [0, 1, 0, -1]

def input_data():
    global N, M, C, MAP
    
    N, M, C = map(int, input().split())

    MAP = [[-1] * MAX for _ in range(MAX)]

    for r in range(1, N + 1):
        MAP[r][1:N + 1] = map(int, input().split())
    
    for r in range(1, N + 1):
        for c in range(1, N + 1):
            if MAP[r][c] == WALL: MAP[r][c] = -1

    car.r, car.c = map(int, input().split())

    for m in range(1, M + 1):
        sr, sc, er, ec = map(int, input().split())
        
        people[m].sr = sr
        people[m].sc = sc
        people[m].er = er
        people[m].ec = ec
        people[m].check = False

def print_map(map): # for debug
    for r in range(1, N + 1):
        print(' '.join('%2d' % num for num in map[r][1:N + 1])) 
    print("")

def find_people():
    global visit
    
    visit = [[0] * MAX for _ in range(MAX)]

    tmpMAP = copy.deepcopy(MAP)

    for i in range(1, M + 1):
        if people[i].check: continue
        
        pr, pc = people[i].sr, people[i].sc
        
        tmpMAP[pr][pc] = i
        
        # A 승객의 도착지(= 현재 전기차의 좌표)와 B 승객의 출발지가 같은 경우
        if pr == car.r and pc == car.c: return INFO(i, 0)

    rp, wp = 0, 0
    
    queue[wp].r = car.r
    queue[wp].c = car.c
    wp += 1
    
    visit[car.r][car.c] = 1
    
    minDistance = minR = minC = INF
    peopleNumber = -1
    while rp < wp:
        out = queue[rp]
        rp += 1

        for k in range(4):
            nr = out.r + dr[k] 
            nc = out.c + dc[k]
            
            if tmpMAP[nr][nc] == -1 or visit[nr][nc] != 0: continue
            
            queue[wp].r = nr
            queue[wp].c = nc            
            wp += 1
            
            visit[nr][nc] = visit[out.r][out.c] + 1

            # 승객의 번호
            if tmpMAP[nr][nc] != 0:
                if (visit[nr][nc] < minDistance or
                    (visit[nr][nc] == minDistance and nr < minR) or
                    (visit[nr][nc] == minDistance and nr == minR and nc < minC)):
                    peopleNumber = tmpMAP[nr][nc]
                    minDistance = visit[nr][nc]
                    minR = nr
                    minC = nc

    return INFO(peopleNumber, minDistance - 1)

def goToDestination(er, ec):
    global visit
    
    visit = [[0] * MAX for _ in range(MAX)]

    tmpMAP = copy.deepcopy(MAP)

    rp, wp = 0, 0
    
    queue[wp].r = car.r
    queue[wp].c = car.c
    wp += 1
    
    visit[car.r][car.c] = 1

    while rp < wp:
        out = queue[rp]
        rp += 1

        if out.r == er and out.c == ec:
            return visit[out.r][out.c] - 1

        for k in range(4):
            nr = out.r + dr[k] 
            nc = out.c + dc[k]
            
            if tmpMAP[nr][nc] == -1 or visit[nr][nc] != 0: continue
            
            queue[wp].r = nr
            queue[wp].c = nc            
            wp += 1
            
            visit[nr][nc] = visit[out.r][out.c] + 1

    return -1

def simulate():
    global C
    
    for _ in range(M):
        # 남은 승객 중 가장 가까이 있는 승객의 번호와 거리 획득
        info = find_people()
        
        if C < info.distance: return -1
        
        C -= info.distance
        
        number = info.peopleNumber

        if number == -1: return -1
        
        # 자동차를 출발지로 이동
        car.r = people[number].sr
        car.c = people[number].sc

        # 전기차와 승객의 목적지까지의 거리
        capacity = goToDestination(people[number].er, people[number].ec)
        
        if capacity == -1 or C < capacity: return -1

        C += capacity
        
        # 자동차를 목적지로 이동
        car.r = people[number].er
        car.c = people[number].ec
        
        people[number].check = True

    return C

# T = int(input())
T = 1
for tc in range(T):    
    input_data()
    
    print(simulate())