import copy

MAX = 100 + 20

class MOLD:
    def __init__(self, distance: int, direction: int, size: int):
        self.distance = distance
        self.direction = direction
        self.size = size

mold = [[MOLD(0, 0, 0) for _ in range(MAX)] for _ in range(MAX)]
tmpMold = [[MOLD(0, 0, 0) for _ in range(MAX)] for _ in range(MAX)]

# -, 위, 아래, 오른쪽, 왼쪽
dr = [0, -1, 1, 0, 0]
dc = [0, 0, 0, 1, -1]

def input_data():
    global N, M, K, mold
    
    N, M, K = map(int, input().split())

    mold = [[MOLD(0, 0, 0) for _ in range(MAX)] for _ in range(MAX)]

    for _ in range(K):
        r, c, s, d, b = map(int, input().split())
        mold[r][c] = MOLD(s, d, b)

def print_map(): # for debug
    for r in range(1, N + 1):
        for c in range(1, M + 1):
            print(mold[r][c].size, end=' ')
        print()
    print()        

# 2. 곰팡이 채취
def catch_mold(sc):
    # 2-1. 해당 열의 위치에서 아래로 내려가며
    for r in range(1, N + 1):
        # 2-2. 가장 먼저 발견한 곰팡이를 채취
        if mold[r][sc].size != 0:
            ret = mold[r][sc].size
            
            # 2-3. 곰팡이를 채취하고 나면 해당 칸은 빈칸
            mold[r][sc].size = 0
            
            return ret
        
    return 0

def move_mold():
    global mold
    
    tmpMold = [[MOLD(0, 0, 0) for _ in range(MAX)] for _ in range(MAX)]
    
    change_dir = [0, 2, 1, 4, 3]

    for r in range(1, N + 1):
        for c in range(1, M + 1):
            if mold[r][c].size == 0: continue
            
            md = mold[r][c]
            
            sr, sc, dir = r, c, md.direction
            
            move = md.distance
            
            # dir = 1, 2 (위, 아래)
            if dir <= 2: move = md.distance % ((N - 1) * 2)
            else: move = md.distance % ((M - 1) * 2)
            
            # 4-1. 곰팡이 이동
            for m in range(move):
                nr = sr + dr[dir]
                nc = sc + dc[dir]
                
                # 4-2. 방향 변경
                if nr < 1 or nc < 1 or nr > N or nc > M:
                    dir = change_dir[dir]
                    
                    nr = sr + dr[dir]
                    nc = sc + dc[dir]
                
                sr, sc = nr, nc

            # 5. 이동 후, 한 칸에 곰팡이가 두마리 이상일 경우, 큰 곰팡이만 남기기
            # 이동할 위치 (sr, sc), 이동 전 위치의 곰팡이는 (r, c)
            if tmpMold[sr][sc].size < mold[r][c].size:
                tmpMold[sr][sc].distance = mold[r][c].distance
                tmpMold[sr][sc].direction = dir
                tmpMold[sr][sc].size = mold[r][c].size

    for r in range(1, N + 1):
        for c in range(1, M + 1):
            mold[r][c] = MOLD(tmpMold[r][c].distance, 
                             tmpMold[r][c].direction, 
                             tmpMold[r][c].size)

def simulate():
    sum = 0
    # 1. 승용이는 첫번째 열부터 탐색을 시작
    for c in range(1, M + 1):
        # 2. 곰팡이 채취
        sum += catch_mold(c)
        
        # 3. 곰팡이 이동 시작
        move_mold()
    
    return sum

# T = int(input())
T = 1
for tc in range(T):   
    input_data()
    
    print(simulate())