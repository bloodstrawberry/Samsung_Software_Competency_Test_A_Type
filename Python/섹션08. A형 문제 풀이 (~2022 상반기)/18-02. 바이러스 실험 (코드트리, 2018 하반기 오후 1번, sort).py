MAX = 10 + 5
MAX_VIRUS = 100000

food = [[0] * MAX for _ in range(MAX)] # 양분
MAP = [[0] * MAX for _ in range(MAX)] # 증가되는 양분

virus = [[[0] * MAX_VIRUS for _ in range(MAX)] for _ in range(MAX)] 
index = [[0] * MAX for _ in range(MAX)]

# 8방향 ↑, ↗, →, ↘, ↓, ↙, ←, ↖
dr = [-1, -1, 0, 1, 1, 1, 0, -1]
dc = [0, 1, 1, 1, 0, -1, -1, -1]

def input_data():
    global N, M, K
    
    N, M, K = map(int, input().split())

    for r in range(1, N + 1):
        MAP[r][1:N + 1] = map(int, input().split())

    for r in range(1, N + 1):
        for c in range(1, N + 1):
            food[r][c] = 5

    for _ in range(M):
        r, c, age = map(int, input().split())
        virus[r][c][index[r][c]] = age
        index[r][c] += 1

def print_virus(): # for debug
    for r in range(1, N + 1):
        for c in range(1, N + 1):
            virus_count = index[r][c]
            if virus_count == 0: continue

            print(f"{r}, {c}) : ", end='')
            for t in range(virus_count):
                print(virus[r][c][t], end=' ')
            print("")
    print("")

def step1_2():
    # 죽은 바이러스 정리    
    for r in range(1, N + 1):
        for c in range(1, N + 1):
            virus_count = index[r][c]
            
            new_index = 0
            for t in range(virus_count):
                if virus[r][c][t] == 0: continue
                
                virus[r][c][new_index] = virus[r][c][t]
                new_index += 1
            
            index[r][c] = new_index
            
            # 나이가 어린 바이러스부터 양분을 섭취하기 위한 정렬
            virus[r][c][:new_index] = sorted(virus[r][c][:new_index])

    # 바이러스의 양분 섭취
    for r in range(1, N + 1):
        for c in range(1, N + 1):
            virus_count = index[r][c]

            break_t = 0
            for t in range(virus_count):
                if virus[r][c][t] == 0: continue
                
                # 나이만큼 양분이 필요
                if virus[r][c][t] <= food[r][c]:
                    food[r][c] -= virus[r][c][t]
                    virus[r][c][t] += 1
                    
                    break_t = t + 1
                else:
                    break_t = t
                    break
            
            # 죽은 바이러스는 양분으로 추가
            for tt in range(break_t, virus_count):
                food[r][c] += (virus[r][c][tt] // 2)
                virus[r][c][tt] = 0
            
def step3():
    for r in range(1, N + 1):
        for c in range(1, N + 1):
            virus_count = index[r][c]        
            for t in range(virus_count):
                if virus[r][c][t] == 0: continue
                if virus[r][c][t] % 5 != 0: continue
                
                for i in range(8):
                    nr = r + dr[i]
                    nc = c + dc[i]
                    
                    if nr < 1 or nc < 1 or nr > N or nc > N: continue
                    
                    virus[nr][nc][index[nr][nc]] = 1
                    index[nr][nc] += 1

def step4():
    for r in range(1, N + 1):
        for c in range(1, N + 1):
            food[r][c] += MAP[r][c]

def get_answer():
    sum = 0
    for r in range(1, N + 1):
        for c in range(1, N + 1):
            end = index[r][c]
            for t in range(end):
                if virus[r][c][t] != 0:
                    sum += 1
            
    return sum

# T = int(input())
T = 1
for tc in range(T):
    input_data()
    
    for time in range(K):
        step1_2()
        step3()
        step4()
        
    print(get_answer())