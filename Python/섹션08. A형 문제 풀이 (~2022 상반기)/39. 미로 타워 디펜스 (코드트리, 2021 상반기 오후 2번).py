MAX_N = 50 + 5
MAX_M = 100 + 10

MAP = [[0] * MAX_N for _ in range(MAX_N)]
D = [0] * MAX_M
P = [0] * MAX_M

snail = [[0] * MAX_N for _ in range(MAX_N)]
monster = [0] * (MAX_N * MAX_N)

# ←, ↓, →, ↑ for snail
drs = [0, 1, 0, -1]
dcs = [-1, 0, 1, 0]

# →, ↓, ←, ↑ 
dr = [0, 1, 0, -1]
dc = [1, 0, -1, 0]

def input_data():
    global N, M
    
    N, M = map(int, input().split())
    
    for r in range(1, N + 1):
        MAP[r][1:N + 1] = map(int, input().split())
        
    for m in range(M):
        D[m], P[m] = map(int, input().split())

def print_map(map):  # debug
    for r in range(1, N + 1):
        print(' '.join('%2d' % num for num in map[r][1:N + 1]))
    print()

def make_snail(map, arr):
    sr = sc = (N + 1) // 2
    direction = 0
    index = 0
    size = 0
    
    map[sr][sc] = arr[index]
    index += 1
    for i in range(2 * N - 1):
        if i % 2 == 0: size += 1
        
        for _ in range(size):
            nr = sr + drs[direction]
            nc = sc + dcs[direction]
            
            map[nr][nc] = arr[index]            
            index += 1
            
            sr, sc = nr, nc
            
        direction += 1
        
        if direction == 4: direction = 0

def delete_monster():
    score = 0
    
    start, count = 1, 1
    
    mcnt = 1
    for i in range(1, N * N):
        if monster[i] == monster[i + 1]: count += 1
        else:
            if count < 4:
                for k in range(start, start + count):
                    monster[mcnt] = monster[k]
                    mcnt += 1
            else:
                score += (monster[i] * count)
                
            count = 1
            start = i + 1
            
    # 남은 칸을 0으로 만들기    
    for i in range(mcnt, N * N): monster[i] = 0
    
    return score

def make_new_tower():
    new_monster = [0] * (MAX_N * MAX_N)
    
    ncnt, count = 1, 1
    for i in range(1, N * N):
        if monster[i] == 0: break
        
        if monster[i] == monster[i + 1]: count += 1
        else:
            new_monster[ncnt] = count
            ncnt += 1
            new_monster[ncnt] = monster[i]
            ncnt += 1
            
            count = 1
            
        if ncnt == N * N: break
        
    monster[1:ncnt] = new_monster[1:ncnt]
    
    make_snail(MAP, monster)

def simulate():
    global monster
    
    sr = sc = (N + 1) // 2
    
    score = 0
    for m in range(M):
        d, p = D[m], P[m]
        
        for k in range(1, p + 1):
            nr = sr + dr[d] * k
            nc = sc + dc[d] * k
            
            score += MAP[nr][nc]
            MAP[nr][nc] = 0
            
            index = snail[nr][nc]
            monster[index] = 0
            
        mcnt = 1
        for i in range(1, N * N):
            if monster[i] != 0:
                monster[mcnt] = monster[i]
                mcnt += 1
    
		# 남은 칸을 0으로 만들기
        for i in range(mcnt, N * N): monster[i] = 0
        
        while True:
            result = delete_monster()
            if result == 0: break
            score += result
            
        make_new_tower()
        
    return score

# T = int(input())
T = 1
for tc in range(T):
    input_data()
    
    # init
    snail_index = [0] * (MAX_N * MAX_N)
    for i in range(N * N): snail_index[i] = i
    
    make_snail(snail, snail_index)
    
    for r in range(1, N + 1):
        for c in range(1, N + 1):
            monster[snail[r][c]] = MAP[r][c]
            
    print(simulate())
