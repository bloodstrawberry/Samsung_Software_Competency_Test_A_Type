MAX = 1000 + 100

M, N = map(int, input().split())

# 주변을 빈 상자 (-1)로 처리
MAP = [[-1] * MAX for _ in range(MAX)]

class RC:
    def __init__(self, r: int, c: int):
        self.r = r
        self.c = c
    
queue = [RC(0, 0) for _ in range(MAX * MAX)]   

# ↑, →, ↓, ←
dr = [-1, 0, 1, 0]
dc = [0, 1, 0, -1]

def input_data():                
    for r in range(1, N + 1):
        MAP[r][1:M + 1] = map(int, input().split())

def print_map(): # for debug
    for r in range(1, N + 1):
        print(' '.join('%2d' % num for num in MAP[r][1:M + 1]))
    print("")
          
def BFS():
    rp, wp = 0, 0
        
    for r in range(1, N + 1):
        for c in range(1, M + 1):
            if MAP[r][c] == 1:
                queue[wp].r = r
                queue[wp].c = c
                wp += 1
                    
    while rp < wp:
        out = queue[rp]
        rp += 1
                
        for i in range(4):
            nr = out.r + dr[i]
            nc = out.c + dc[i]
            
            # (0, 0) 부터 (N + 1, M + 1)까지 -1로 초기화 한 경우 생략 가능
			# if nr < 1 or nc < 1 or nr > N or nc > M: continue
            if MAP[nr][nc] != 0: continue
            
            queue[wp].r = nr
            queue[wp].c = nc
            wp += 1
            
            MAP[nr][nc] = MAP[out.r][out.c] + 1
            
def getAnswer():
    max_answer = 0
    for r in range(1, N + 1):
        for c in range(1, M + 1):
            if MAP[r][c] == 0: return -1
            if max_answer < MAP[r][c]: max_answer = MAP[r][c]
            
    return max_answer - 1
                          
input_data()

BFS()

print(getAnswer())