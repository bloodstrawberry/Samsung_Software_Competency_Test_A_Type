MAX = 25
WALL = -1

MAP = [[0] * MAX for _ in range(MAX)]
herbicide = [[0] * MAX for _ in range(MAX)]

class INFO:
    def __init__(self, r: int, c: int, count: int):
        self.r = r
        self.c = c
        self.count = count

# ↑, →, ↓, ←
dr = [-1, 0, 1, 0]
dc = [0, 1, 0, -1]

# ↖, ↗, ↘, ↙
dr2 = [-1, -1, 1, 1]
dc2 = [-1, 1, 1, -1]

def input_data():
    global N, M, K, C
    
    N, M, K, C = map(int, input().split())
    
    for r in range(1, N + 1):
        MAP[r][1: N + 1] = map(int, input().split())

def print_map(map):  # for debug
    for r in range(1, N + 1):
        print(' '.join('%2d' % num for num in map[r][1:N + 1]))        
    print("")

def spread_tree():
    # 1. 인접한 칸 만큼 나무가 성장
    for r in range(1, N + 1):
        for c in range(1, N + 1):
            if MAP[r][c] == 0 or MAP[r][c] == WALL: continue
            
            count = 0 # 주변 나무의 개수
            for i in range(4):
                nr = r + dr[i]
                nc = c + dc[i]
                
                if nr < 1 or nc < 1 or nr > N or nc > N: continue
                
                if MAP[nr][nc] > 0: count += 1
                
            MAP[r][c] += count

    # 2. 인접한 칸에 동시에 번식
    tmp_map = [[0] * MAX for _ in range(MAX)]
    for r in range(1, N + 1):
        for c in range(1, N + 1):
            if MAP[r][c] == 0 or MAP[r][c] == WALL: continue
            
            count = 0 # 번식 가능한 칸
            for i in range(4):
                nr = r + dr[i]
                nc = c + dc[i]
                
                if nr < 1 or nc < 1 or nr > N or nc > N: continue
                
                if MAP[nr][nc] == WALL: continue
                
                if MAP[nr][nc] == 0 and herbicide[nr][nc] == 0: count += 1
                            
            for i in range(4):
                nr = r + dr[i]
                nc = c + dc[i]
                if nr < 1 or nc < 1 or nr > N or nc > N: continue
                
                if MAP[nr][nc] == 0 and herbicide[nr][nc] == 0:
                    tmp_map[nr][nc] += (MAP[r][c] // count)

    for r in range(1, N + 1):
        for c in range(1, N + 1):
            MAP[r][c] += tmp_map[r][c]

# (r, c)에 제초제를 나뒀을 때, 사라지는 나무의 수
def get_delete_tree_count(r, c):    
    sum = MAP[r][c]
    for i in range(4):
        for k in range(1, K + 1):
            nr = r + dr2[i] * k
            nc = c + dc2[i] * k
            
            if nr < 1 or nc < 1 or nr > N or nc > N: break
            if MAP[nr][nc] == 0 or MAP[nr][nc] == WALL: break
                        
            sum += MAP[nr][nc]
            
    return sum

def find_max_delete_tree():
    max_r, max_c, max_tree = 0, 0, 0
    for r in range(1, N + 1): # 행이 작은 순서대로
        for c in range(1, N + 1): # 열이 작은 순서대로
            if MAP[r][c] == 0 or MAP[r][c] == WALL: continue
            
            delete_tree_count = get_delete_tree_count(r, c)
            if max_tree < delete_tree_count:
                max_r, max_c, max_tree = r, c, delete_tree_count
                
    return INFO(max_r, max_c, max_tree)

def weeding(r, c):
    MAP[r][c] = 0
    herbicide[r][c] = C
    for i in range(4):
        for k in range(1, K + 1):
            nr = r + dr2[i] * k
            nc = c + dc2[i] * k
            
            if nr < 1 or nc < 1 or nr > N or nc > N: break
            if MAP[nr][nc] == WALL: break
            
            if MAP[nr][nc] == 0:            
                herbicide[nr][nc] = C
                break
            
            MAP[nr][nc] = 0
            herbicide[nr][nc] = C

def simulate():
    sum = 0
    for m in range(M):
        spread_tree() # 나무의 성장, 번식
        
        for r in range(1, N + 1):
            for c in range(1, N + 1):
                if herbicide[r][c] != 0: herbicide[r][c] -= 1
                
        target = find_max_delete_tree() # 제초제를 뿌릴 위치 선정
        
        weeding(target.r, target.c) # 제초제를 뿌리는 작업 진행
        
        sum += target.count # 총 박멸한 나무의 그루 수
        
    return sum

# T = int(input())
T = 1
for tc in range(T):    
    input_data()
    
    print(simulate())