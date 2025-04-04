MAX = 50 + 5

ROAD = 0 # 도로
STREET = 1 # 인도
MARK = 2

MAP = [[0] * MAX for _ in range(MAX)]

# 북, 동, 남, 서
dr = [-1, 0, 1, 0]
dc = [0, 1, 0, -1]

def input_data():             
    global N, M, R, C, D
    
    N, M = map(int, input().split())
    R, C, D = map(int, input().split())
        
    for r in range(N):
        MAP[r][:M] = map(int, input().split())
                                
def print_map(): # for debug
    for r in range(N):
        print(*MAP[r][:M])
    print("")
   
def simulate():
    global R, C, D
    
    changeDir = [3, 0, 1, 2]
    
    # count = 0
    while True:
        # 종료 조건 구현 전, while 문 디버깅
        # count += 1
        # if count == 10 : break
        
        # for debug
        # print(R, C, D)
        # print_map()
        
        MAP[R][C] = MARK
        
        # 1. 현재 방향을 기준으로 왼쪽 방향으로 한 번도 간 적이 없다면 
        
        nDir = changeDir[D] # or (D - 1 + 4) % 4
        nr = R + dr[nDir]
        nc = C + dc[nDir]
        
        # 좌회전해서 해당 방향으로 1 칸 전진합니다.
        if MAP[nr][nc] == ROAD:
            D = nDir
            R = nr
            C = nc
        else: # 2. 만약 왼쪽 방향이 인도거나 이미 방문한 도로인 경우
            flag = False
            for i in range(0, 4):
                D = nDir
                nr = R + dr[D]
                nc = C + dc[D]
                
                # 좌회전하고 다시 1번 과정을 시도합니다.
                if MAP[nr][nc] == ROAD:
                    R = nr
                    C = nc
                    flag = True
                    break
                
                nDir = changeDir[D] # or (D - 1 + 4) % 4
            
            # 3. 2번에 대해 4방향 모두 확인하였으나 전진하지 못한 경우에는
            # 바라보는 방향을 유지한 채로 한 칸 후진을 하고 다시 1번 과정을 시도합니다.
            if flag == False:
                nr = R - dr[D]
                nc = C - dc[D]
                
                R = nr
                C = nc
                
                # 4. 3번 과정을 시도하려 했지만
                # 뒷 공간이 인도여서 후진조차 하지 못한다면 작동을 멈춥니다. 
                if MAP[R][C] == STREET: break
            
def get_answer():
    sum = 0
    for r in range(N):
        for c in range(M):
            if MAP[r][c] == MARK: sum += 1
            
    return sum
          
# T = int(input())
T = 1
for _ in range(T): 
    input_data()     
    
    simulate()
    
    print(get_answer())