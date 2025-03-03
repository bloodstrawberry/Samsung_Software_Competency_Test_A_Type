import copy

MAX = 500 + 50
MAP = [[0] * MAX for _ in range(MAX)]

def input_data():
    global N, D
    N, D =  map(int, input().split())
    D = (D + 360) % 360  # 음수 각도를 양수로 변환
    
    for r in range(1, N + 1):
        MAP[r][1:N + 1] = map(int, input().split())

def print_map():
    for r in range(1, N + 1):
        print(" ".join(map(str, MAP[r][1:N + 1])))

def rotate_45():
    temp = copy.deepcopy(MAP)
        
    arr = [0] * MAX
    half = (N + 1) // 2
    
    for c in range(1, N + 1): arr[c] = temp[half][c]
    for i in range(1, N + 1): MAP[i][i] = arr[i]
    
    for i in range(1, N + 1): arr[i] = temp[i][i]
    for r in range(1, N + 1): MAP[r][half] = arr[r]
    
    for r in range(1, N + 1): arr[r] = temp[r][half]
    for i in range(1, N + 1): MAP[i][N - i + 1] = arr[i]
    
    for i in range(1, N + 1): arr[i] = temp[N - i + 1][i]
    for c in range(1, N + 1): MAP[half][c] = arr[c]

T = int(input())
for _ in range(T):
    input_data()
    
    # 회전
    count = D // 45
    
    for _ in range(count): rotate_45()
    
    print_map()

