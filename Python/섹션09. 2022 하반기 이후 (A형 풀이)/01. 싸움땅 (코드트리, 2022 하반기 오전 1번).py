MAX = 30 + 5

GUN = [[[0] * (MAX * MAX) for _ in range(MAX)] for _ in range(MAX)]
gIndex = [[0] * MAX for _ in range(MAX)]

class PLAYER:
    def __init__(self, r: int, c: int, dir: int, s: int, gun: int):
        self.r = r
        self.c = c
        self.dir = dir
        self.s = s # 초기 능력치
        self.gun = gun
           
player = [PLAYER(0, 0, 0, 0, 0) for _ in range(30 + 5)]  
                
# ↑, →, ↓, ←
dr = [-1, 0, 1, 0]
dc = [0, 1, 0, -1]

SCORE = [0] * (30 + 5)

def input_data():
    global N, M, K, gIndex
    
    N, M, K = map(int, input().split())
    
    gIndex = [[0] * MAX for _ in range(MAX)]
    
    for r in range(1, N + 1):
        values = list(map(int, input().split()))
        for c in range(1, N + 1):
            value = values[c - 1]
            GUN[r][c][0] = value
            if value != 0: gIndex[r][c] = 1            
    
    for m in range(1, M + 1): # player 번호는 1번 부터
        SCORE[m] = 0
        
        r, c, d, s = map(int, input().split())
        
        player[m].r = r
        player[m].c = c
        player[m].dir = d
        player[m].s = s
        player[m].gun = 0 # 초기화
            
def print_map(map): # for debug
    for r in range(1, N + 1):
        print(*map[r][1:N + 1])            
    print("")

def get_max_power_gun_index(r, c):
    max = -1
    count = gIndex[r][c]
    index = 0
    for i in range(count):
        if max < GUN[r][c][i]:
            max = GUN[r][c][i]
            index = i
    
    return index

# p1이 이기면 0, p2가 이기면 1
def battle(p1, p2):
    g1 = p1.gun
    s1 = p1.s
    g2 = p2.gun
    s2 = p2.s

    sum1 = g1 + s1
    sum2 = g2 + s2
    
    if sum1 > sum2: return 0
    if sum1 < sum2: return 1
    
    if s1 > s2: return 0
    if s1 < s2: return 1
    
    return -1 # for debug

def simulate():
    changeDir = [2, 3, 0, 1]
    
    for k in range(K):
        tmp_map = [[0] * MAX for _ in range(MAX)]
        
        # 현재 player의 번호를 마킹
        for m in range (1, M + 1):
            r = player[m].r
            c = player[m].c
            
            tmp_map[r][c] = m
            
        for m in range (1, M + 1):
			# 1-1. 플레이어 순차적으로 이동
            p = player[m]
            
            dir = p.dir
            nr = p.r + dr[dir]
            nc = p.c + dc[dir]
            
            # 1-1. 격자를 벗어나는 경우, 반대 방향으로 변경 후 이동
            if nr < 1 or nc < 1 or nr > N or nc > N:
                dir = changeDir[dir]
                player[m].dir = dir
                
                nr = p.r + dr[dir]
                nc = p.c + dc[dir]
            
            # 2-1. 이동할 방향에 플레이어가 있는지 체크
            if tmp_map[nr][nc] == 0: # 없는 경우
                # tmp_map에서 이동
                tmp_map[p.r][p.c] = 0
                tmp_map[nr][nc] = m
                
                # player 좌표 갱신
                player[m].r = nr
                player[m].c = nc
                
                if gIndex[nr][nc] != 0: # 총이 있는 경우
                    player_gun = player[m].gun
                    gun_index = get_max_power_gun_index(nr, nc)
                    
                    if player_gun < GUN[nr][nc][gun_index]:
                        player[m].gun, GUN[nr][nc][gun_index] = GUN[nr][nc][gun_index], player[m].gun
            else: # 2-2. player가 있는 경우
                winner, loser = 0, 0
                another = tmp_map[nr][nc]
                
                # 이동한 플레이어 0으로 갱신
                tmp_map[player[m].r][player[m].c] = 0
                
                if battle(player[m], player[another]) == 0: # m이 이긴 경우
                    winner = m
                    loser = another
                else:
                    winner = another
                    loser = m
                
                # 2-2-1. 점수 획득
                SCORE[winner] += ((player[winner].gun + player[winner].s)) - ((player[loser].gun + player[loser].s))
                
                # 2-2-2. 패배한 플레이어
                loser_gun = player[loser].gun
                player[loser].gun = 0
                
                GUN[nr][nc][gIndex[nr][nc]] = loser_gun
                gIndex[nr][nc] += 1

                for i in range(4):
                    lnr = nr + dr[player[loser].dir]
                    lnc = nc + dc[player[loser].dir]
                    if lnr < 1 or lnc < 1 or lnr > N or lnc > N or tmp_map[lnr][lnc] != 0:
                        player[loser].dir = (player[loser].dir + 1) % 4
                    else:
                        tmp_map[nr][nc] = 0
                        tmp_map[lnr][lnc] = loser
                        
                        player[loser].r = lnr
                        player[loser].c = lnc
                        
                        if gIndex[lnr][lnc] != 0: # 총이 있는 경우
                            player_gun = player[loser].gun
                            gun_index = get_max_power_gun_index(lnr, lnc)
                            
                            if player_gun < GUN[lnr][lnc][gun_index]:
                                player[loser].gun = GUN[lnr][lnc][gun_index]
                                GUN[lnr][lnc][gun_index] = 0
                        
                        break
                
                # 2-2-3. 이긴 플레이어는 더 좋은 총으로 변경
                player_gun = player[winner].gun
                gun_index = get_max_power_gun_index(nr, nc)
                if player_gun < GUN[nr][nc][gun_index]:
                        player[winner].gun, GUN[nr][nc][gun_index] = GUN[nr][nc][gun_index], player[winner].gun
                
                # 이긴 플레이어 표시
                tmp_map[nr][nc] = winner
                
                player[winner].r = nr
                player[winner].c = nc
                				
# T = int(input())
T = 1
for tc in range(T):    
    input_data()
    
    simulate()
    
    print(*SCORE[1:M + 1])