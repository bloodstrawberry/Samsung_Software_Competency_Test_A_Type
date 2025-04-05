MAX_N = 50 + 5
MAX_P = 30 + 5
INF = 0x7fff0000

RUDOLPH = 99

MAP = [[0] * MAX_N for _ in range(MAX_N)] 

class RC:
    def __init__(self, r: int, c: int):
        self.r = r
        self.c = c

rudolph = RC(0, 0)

class SANTA:
    def __init__(self, r: int, c: int, stun: int, dead: bool, score: int):
        self.r = r
        self.c = c
        self.stun = stun
        self.dead = dead
        self.score = score
           
santa = [SANTA(0, 0, 0, False, 0) for _ in range(MAX_P)]  
                
# 3-7. 상우하좌 우선순위
# ↑, →, ↓, ←
dr4 = [-1, 0, 1, 0]
dc4 = [0, 1, 0, -1]

# ←, ↖, ↑, ↗, →, ↘, ↓, ↙
dr8 = [0, -1, -1, -1, 0, 1, 1, 1]
dc8 = [-1, -1, 0, 1, 1, 1, 0, -1]

SCORE = [0] * (30 + 5)

def input_data():
    global N, M, P, C, D, rodulph, MAP
    
    N, M, P, C, D = map(int, input().split())
    
    rudolph.r, rudolph.c = map(int, input().split())
    
    for p in range(1, P + 1):
        index, r, c = map(int, input().split())
        
        santa[index].r = r
        santa[index].c = c
        santa[index].stun = 0
        santa[index].dead = False
          
def print_status(): # for debug
    print(f"rudolph {rudolph.r}, {rudolph.c}")

    for p in range(1, P + 1):
        s = santa[p]
        print(f"{p}] ({s.r}, {s.c}) {s.stun} / {s.dead} / {s.score}")
    print("")

    for r in range(1, N + 1):
        print(' '.join('%2d' % num for num in MAP[r][1:N + 1]))
    print("")          
          
def get_distance(r1, c1, r2, c2):
    return (r1 - r2) ** 2 + (c1 - c2) ** 2

def check():
    for p in range(1, P + 1):
        if santa[p].dead == False: return False
    
    return True

def score_up():
    for p in range(1, P + 1):
        if santa[p].dead == True: continue
        
        santa[p].score += 1

def set_map():
    global MAP
    
    MAP = [[0] * MAX_N for _ in range(MAX_N)]
    
    for p in range(1, P + 1):
        s = santa[p]
        
        if s.dead == True: continue
        
        MAP[s.r][s.c] = p
    
    MAP[rudolph.r][rudolph.c] = RUDOLPH

def get_near_santa_index():
    santa_index = 0
    min_distance = INF
    
    for r in range(N, 0, -1):
        for c in range(N, 0, -1):
            if MAP[r][c] == 0 or MAP[r][c] == RUDOLPH: continue
            
            distance = get_distance(rudolph.r, rudolph.c, r, c)
            
            if distance < min_distance:
                min_distance = distance
                santa_index = MAP[r][c]
    
    return santa_index
          
def get_rudolph_direction(santa_index):
    direction = -1
    min_distance = INF
    
    s = santa[santa_index]
    
    for i in range(8):
        nr = rudolph.r + dr8[i]
        nc = rudolph.c + dc8[i]
        
        distance = get_distance(nr, nc, s.r, s.c)
        
        if distance < min_distance:
            min_distance = distance
            direction = i
    
    return direction
        
def interaction(santa_index, direction, is_rudolph):
    start_santa = santa[santa_index]
    
    # 연쇄적으로 밀려날 산타들
    candidate = [0] * MAX_P
    count = 0
    
    candidate[count] = santa_index
    count += 1
    
    sr, sc = start_santa.r, start_santa.c
    
    while True:
        nr, nc = 0, 0
        
        if is_rudolph == True:
            nr = sr + dr8[direction]
            nc = sc + dc8[direction]
        else:
            nr = sr + dr4[direction]
            nc = sc + dc4[direction]
        
        if nr < 1 or nc < 1 or nr > N or nc > N: break
        if MAP[nr][nc] == 0: break
        
        candidate[count] = MAP[nr][nc]
        count += 1
        
        sr, sc = nr, nc
    
    for i in range(count):
        index = candidate[i]
        s = santa[index]
        
        snr, snc = s.r, s.c
        
        if is_rudolph == True:
            snr = snr + dr8[direction]
            snc = snc + dc8[direction]
        else:
            snr = snr + dr4[direction]
            snc = snc + dc4[direction]
            
        if snr < 1 or snc < 1 or snr > N or snc > N:
            santa[index].dead = True
            continue
    
        santa[index].r = snr
        santa[index].c = snc
    
def move_rudolph():
    set_map()

    # 2-1, 2-2 우선순위가 가장 높은 가까운 산타의 번호
    near_santa_index = get_near_santa_index()

    # 2-3 우선순위가 높은 산타를 향해 돌진하는 방향
    rudolph_direction = get_rudolph_direction(near_santa_index)

    nr = rudolph.r + dr8[rudolph_direction]
    nc = rudolph.c + dc8[rudolph_direction]

    rudolph.r = nr
    rudolph.c = nc

    # 4-2 루돌프가 움직여서 충돌이 일어난 경우
    if MAP[nr][nc] != 0:
        # 4-2 산타의 이동
        crash_santa_index = MAP[nr][nc]
        crash_santa = santa[crash_santa_index]

        snr = crash_santa.r + (dr8[rudolph_direction]) * C
        snc = crash_santa.c + (dc8[rudolph_direction]) * C

        # 4-5 게임판 밖인 경우 탈락
        if snr < 1 or snc < 1 or snr > N or snc > N:
            santa[crash_santa_index].dead = True
        elif MAP[snr][snc] != 0:
            inter_santa_index = MAP[snr][snc]
            
            # 5-2 tkdgh wkrdyd
            interaction(inter_santa_index, rudolph_direction, True)

        santa[crash_santa_index].r = snr
        santa[crash_santa_index].c = snc
        
        # 6-1 기절
        santa[crash_santa_index].stun = 2
        
        # 4-2 점수 획득
        santa[crash_santa_index].score += C


def move_santa(santa_index):
    set_map()

    s = santa[santa_index]
    distance = get_distance(rudolph.r, rudolph.c, s.r, s.c)
    direction = -1
    min_distance = INF

    # 3-7 상우하좌 우선순위대로 확인
    for i in range(4):
        nr = s.r + dr4[i]
        nc = s.c + dc4[i]

        next_distance = get_distance(rudolph.r, rudolph.c, nr, nc)

        # 3-6 루돌프와 멀어지는 방향 
        if distance < next_distance: continue

        # 루돌프 확인
        if MAP[nr][nc] == RUDOLPH:
            min_distance = 1
            direction = i
            break

        if MAP[nr][nc] != 0: continue

        if next_distance < min_distance:
            min_distance = next_distance
            direction = i

    # 3-5 움직일 수 있는 칸이 없는 경우
    if direction == -1: return

    santa[santa_index].r = s.r + dr4[direction]
    santa[santa_index].c = s.c + dc4[direction]

    # 4-3 산타의 다음 좌표가 루돌프인 경우
    if MAP[santa[santa_index].r][santa[santa_index].c] == RUDOLPH:
        santa[santa_index].stun = 1
        santa[santa_index].score += D

		#    ↑, →, ↓, ← (0, 1, 2, 3)
		# => ↓, ←, ↑, → (2, 3, 0, 1)
        change_dir = [2, 3, 0, 1]
        
        direction = change_dir[direction]
        snr = santa[santa_index].r + (dr4[direction]) * D
        snc = santa[santa_index].c + (dc4[direction]) * D

        if snr < 1 or snc < 1 or snr > N or snc > N:
            santa[santa_index].dead = True
            return

        santa[santa_index].r = snr
        santa[santa_index].c = snc

        # 5-2 상호작용
        if MAP[snr][snc] != 0:
            inter_santa_index = MAP[snr][snc]
            if inter_santa_index != santa_index:
                interaction(inter_santa_index, direction, False)


def move_all_santa():
    # 3-1 산타는 1번부터 순서대로 이동
    for p in range(1, P + 1):
        s = santa[p]

        # 3-2 탈락한 산타
        if s.dead: continue

        # 3-3 기절한 산타
        # 6-1, 6-2 기절 처리
        if s.stun != 0:
            santa[p].stun -= 1
            continue

        move_santa(p)

def simulate():
    for m in range(M):
        # 루돌프의 움직임
        move_rudolph()
        
        # 산타의 움직임
        move_all_santa()
        
        # 7-2 모든 산타가 탈락한 경우, 게임 종료
        if check() == True: break
        
        # 7-3 탈락하지 않은 산타 점수 추가
        score_up()
    
    for p in range(1, P + 1):
        print(santa[p].score, end=" ")
                				
# T = int(input())
T = 1
for tc in range(T):    
    input_data()
    
    simulate()