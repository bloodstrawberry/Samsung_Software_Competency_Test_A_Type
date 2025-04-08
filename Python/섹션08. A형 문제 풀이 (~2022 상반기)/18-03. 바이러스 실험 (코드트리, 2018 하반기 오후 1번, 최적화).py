MAX = 10 + 5
MAX_VIRUS = 200000
OFFSET = 20000

food = [[0] * MAX for _ in range(MAX)] # 양분
MAP = [[0] * MAX for _ in range(MAX)] # 증가되는 양분
virus = [[[0] * MAX_VIRUS for _ in range(MAX)] for _ in range(MAX)] # deque
front = [[0] * MAX for _ in range(MAX)]
back = [[0] * MAX for _ in range(MAX)]

# 8방향 ↑, ↗, →, ↘, ↓, ↙, ←, ↖
dr = [-1, -1, 0, 1, 1, 1, 0, -1]
dc = [0, 1, 1, 1, 0, -1, -1, -1]

def input_data():
    global N, M, K, front, back
    
    N, M, K = map(int, input().split())

    for r in range(1, N + 1):
        MAP[r][1:N + 1] = map(int, input().split())

    for r in range(1, N + 1):
        for c in range(1, N + 1):
            food[r][c] = 5
            
    front = [[OFFSET] * MAX for _ in range(MAX)]
    back = [[OFFSET] * MAX for _ in range(MAX)]

    for _ in range(M):
        r, c, age = map(int, input().split())
        virus[r][c][back[r][c]] = age
        back[r][c] += 1

def print_virus(): # for debug
    for r in range(1, N + 1):
        for c in range(1, N + 1):
            if (back[r][c] - front[r][c]) == 0: continue
            
            print(f"{r}, {c}) :", end=" ")
            for t in range(front[r][c], back[r][c]):
                print(virus[r][c][t], end=" ")
            print("")
    print("")

def step1_2():
    # 바이러스의 양분 섭취
    for r in range(1, N + 1):
        for c in range(1, N + 1):
            start = front[r][c]
            end = back[r][c]

            break_t = start
            for t in range(start, end):
                if virus[r][c][t] <= food[r][c]:
                    food[r][c] -= virus[r][c][t]
                    virus[r][c][t] += 1
                    
                    front[r][c] += 1
                    virus[r][c][back[r][c]] = virus[r][c][t]
                    back[r][c] += 1
                    
                    break_t = t + 1
                else:
                    break_t = t
                    break
            
            for tt in range(break_t, end):
                food[r][c] += (virus[r][c][tt] // 2)
                front[r][c] += 1
            
def step3():
    for r in range(1, N + 1):
        for c in range(1, N + 1):
            start = front[r][c]
            end = back[r][c]            
            for t in range(start, end):
                if virus[r][c][t] % 5 != 0: continue
                
                for i in range(8):
                    nr = r + dr[i]
                    nc = c + dc[i]
                    
                    if nr < 1 or nc < 1 or nr > N or nc > N: continue
                    
                    front[nr][nc] -= 1
                    virus[nr][nc][front[nr][nc]] = 1

def step4():
    for r in range(1, N + 1):
        for c in range(1, N + 1):
            food[r][c] += MAP[r][c]

def get_answer():
    sum = 0
    for r in range(1, N + 1):
        for c in range(1, N + 1):
            sum += (back[r][c] - front[r][c])
            
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