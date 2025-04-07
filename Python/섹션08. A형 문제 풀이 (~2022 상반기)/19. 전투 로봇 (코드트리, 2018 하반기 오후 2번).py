MAX = 20 + 5
INF = 0x7fff0000

ROBOT_POSITION = 9

MAP = [[0] * MAX for _ in range(MAX)]
visit = [[0] * MAX for _ in range(MAX)]

class ROBOT:
    def __init__(self, r: int, c: int, attack: int, level: int):
        self.r = r
        self.c = c
        self.attack = attack # 몬스터를 제거한 횟수
        self.level = level # 로봇의 레벨

battle_robot = ROBOT(0, 0, 0, 0)

class RC:
    def __init__(self, r: int, c: int):
        self.r = r
        self.c = c
    
queue = [RC(0, 0) for _ in range(MAX * MAX)]

# ↑, →, ↓, ←
dr = [-1, 0, 1, 0]
dc = [0, 1, 0, -1]

def input_data():
    global N, MAP, battle_robot
    
    N = int(input())
    
    for r in range(1, N + 1):
        MAP[r][1:N + 1] = map(int, input().split())
        
    for r in range(1, N + 1):
        for c in range(1, N + 1):
            if MAP[r][c] == ROBOT_POSITION:
                MAP[r][c] = 0 # 전투 로봇은 좌표에서 삭제
                battle_robot = ROBOT(r, c, 0, 2)
                
def print_map(): # for debug
    for r in range(1, N + 1):
        print(*visit[r][1:N + 1])
    print("")                

def monster_exists():
    for r in range(1, N + 1):
        for c in range(1, N + 1):
            if MAP[r][c] != 0 and MAP[r][c] < battle_robot.level: return True
            
    return False

def BFS():
    global visit
    
    visit = [[0] * MAX for _ in range(MAX)]
    
    rp, wp = 0, 0
    
    queue[wp].r = battle_robot.r
    queue[wp].c = battle_robot.c
    wp += 1
    
    visit[battle_robot.r][battle_robot.c] = 1

    while rp < wp:
        out = queue[rp]
        rp += 1
        
        for i in range(4):
            nr = out.r + dr[i]
            nc = out.c + dc[i]
            
            if nr < 1 or nc < 1 or nr > N or nc > N: continue
            
            # 같은 레벨은 해당 칸을 지나칠 수는 있음.
            if battle_robot.level < MAP[nr][nc]: continue
            if visit[nr][nc] != 0: continue
            
            queue[wp].r = nr
            queue[wp].c = nc
            wp += 1
            
            visit[nr][nc] = visit[out.r][out.c] + 1

def simulate():
    if monster_exists() == False: return 0

    BFS()

    tmp_r, tmp_c = 0, 0
    min_time = INF
    for r in range(1, N + 1): # 가장 위에 존재하는 몬스터를 확인
        for c in range(1, N + 1): # 가장 왼쪽에 존재하는 몬스터를 확인
            if MAP[r][c] == 0 or visit[r][c] == 0: continue
            
            if battle_robot.level <= MAP[r][c]: continue
            
            if visit[r][c] < min_time:
                min_time = visit[r][c]
                tmp_r, tmp_c = r, c
            
    if min_time == INF: return 0
    
    # 몬스터를 없애면 해당 칸은 빈칸
    MAP[tmp_r][tmp_c] = 0

    # 로봇 이동 및 제거한 몬스터 수 증가
    battle_robot.r = tmp_r
    battle_robot.c = tmp_c
    battle_robot.attack += 1

    # 본인의 레벨과 같은 수의 몬스터를 없앨 때마다 레벨 상승
    if battle_robot.attack == battle_robot.level:    
        battle_robot.level += 1
        battle_robot.attack = 0
            
    return min_time - 1

# T = int(input())
T = 1
for tc in range(T): 
    input_data()
    
    time = 0
    
    while True:
        result = simulate()
        
        if result == 0: break
        
        time += result
        
    print(time)