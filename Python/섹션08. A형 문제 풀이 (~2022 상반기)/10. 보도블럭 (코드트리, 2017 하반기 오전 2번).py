MAX = 100 + 20

MAP = [[0] * MAX for _ in range(MAX)]
TMAP = [[0] * MAX for _ in range(MAX)]

def input_data():             
    global N, L
    
    N, L = map(int, input().split())
        
    for r in range(1, N + 1):
        MAP[r][1:N + 1] = map(int, input().split())

    for r in range(1, N + 1):
        for c in range(1, N + 1):
            TMAP[c][r] = MAP[r][c]        
                                        
def is_flat(arr, start, end):
    value = arr[start]
    for i in range(start + 1, end + 1):
        if value != arr[i]: return False
    
    return True
   
def check_row(arr):
    visit = [False] * MAX
    
    inverse = [0] * MAX
    visit_inverse = [False] * MAX
    
    for c in range(1, N):
        if arr[c] == arr[c + 1]: continue
        
        # 1) 높이 차이가 1 보다 큰 경우
        if abs(arr[c] - arr[c + 1]) > 1: return 0
        
        if arr[c] > arr[c + 1]:
            # 2) 경사로의 길이만큼 낮은 칸의 보도블럭이 연속하지 않는 경우
            if c + L > N: return 0
            if is_flat(arr, c + 1, c + L) == False: return 0
            
            for k in range(c + 1, c + L + 1):
                visit[k] = True
                
    for c in range(1, N + 1):
        inverse[c] = arr[N + 1 - c]
        visit_inverse[c] = visit[N + 1 - c]
        
    for c in range(1, N):
        if inverse[c] == inverse[c + 1]: continue
        
        # 1) 높이 차이가 1 보다 큰 경우
        if abs(inverse[c] - inverse[c + 1]) > 1: return 0
        
        if inverse[c] > inverse[c + 1]:
            # 2) 경사로의 길이만큼 낮은 칸의 보도블럭이 연속하지 않는 경우
            if c + L > N: return 0
            if is_flat(inverse, c + 1, c + L) == False: return 0
            
            # 3) 경사로를 놓은 곳에 또 경사로를 놓은 경우
            for k in range(c + 1, c + L + 1):
                if visit_inverse[k] == True: return 0
    
    return 1

def check_all_row():
    sum = 0
    for r in range(1, N + 1):
        sum += check_row(MAP[r])
        sum += check_row(TMAP[r])
        
    return sum

# T = int(input())
T = 1
for _ in range(T):     
    input_data()     
        
    print(check_all_row())