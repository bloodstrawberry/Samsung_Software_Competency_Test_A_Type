MAX = 20 + 5
INF = 0x7fff0000

MAP = [[0] * MAX for _ in range(MAX)]

def input_data():
    global N, MAP
    
    N = int(input())
    
    MAP = [[-1] * MAX for _ in range(MAX)]
    
    for r in range(1, N + 1):        
        MAP[r][1:N + 1] = map(int, input().split())

def print_map(map): # for debug
    for r in range(1, N + 1):
        print(map[r][1:N + 1])
    print("")

def calculate(sr, sc, d1, d2):
    global min_answer
    
    area = [[0] * MAX for _ in range(MAX)]
    
    sum = [0] * 6

    start = end = sc
    left = -1
    right = 1

    # 1번 구역
    for r in range(sr, sr + d1 + d2 + 1):
        for c in range(start, end + 1):
            area[r][c] = 1

        start += left
        end += right

        if start == sc - d1: left = 1
        if end == sc + d2: right = -1

    # 2번 구역
    for r in range(1, N + 1):
        for c in range(1, N + 1):
            if area[r][c] == 1: break
            
            if 1 <= r <= sr + d1 - 1 and 1 <= c <= sc: area[r][c] = 2

    # 3번 구역
    for r in range(1, N + 1):
        for c in range(1, N + 1):
            if area[r][c] == 1: continue
            
            if 1 <= r <= sr + d2 and sc + 1 <= c <= N: area[r][c] = 3

    # 4번 구역
    for r in range(1, N + 1):
        for c in range(1, N + 1):
            if area[r][c] == 1: break
            
            if sr + d1 <= r <= N and 1 <= c <= sc - d1 + d2 - 1: area[r][c] = 4

    # 5번 구역
    for r in range(1, N + 1):
        for c in range(1, N + 1):
            if area[r][c] == 1: continue
            
            if sr + d2 + 1 <= r <= N and sc - d1 + d2 <= c <= N: area[r][c] = 5

    # for debug
    # print_map(area)

    for r in range(1, N + 1):
        for c in range(1, N + 1):
            sum[area[r][c]] += MAP[r][c]

    max_val = max(sum[1:6])
    min_val = min(sum[1:6])
    
    min_answer = min(min_answer, max_val - min_val)

def simulate():
    for r in range(1, N - 1):
        for c in range(2, N):
            d1 = 1
            while True:
                if MAP[r + d1][c - d1] == -1: break
                
                d2 = 1
                while True:
                    if (MAP[r + d2][c + d2] == -1 or
                        MAP[r + d1 + d2][c + d2 - d1] == -1):
                        break
                    
                    calculate(r, c, d1, d2)
                    
                    d2 += 1
                    
                d1 += 1

# T = int(input())
T = 1
for tc in range(T):
    global min_answer
    
    input_data()
    
    min_answer = INF
    
    simulate()
    
    print(min_answer)