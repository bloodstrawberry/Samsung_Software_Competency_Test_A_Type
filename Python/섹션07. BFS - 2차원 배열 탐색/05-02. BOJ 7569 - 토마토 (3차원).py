MAX = 100 + 10

M, N, H = map(int, input().split())

# 주변을 빈 상자 (-1)로 처리
MAP = [[[-1] * MAX for _ in range(MAX)] for _ in range(MAX)]

class HRC:
    def __init__(self, h: int, r: int, c: int):
        self.h = h
        self.r = r
        self.c = c
    
queue = [HRC(0, 0, 0) for _ in range(MAX * MAX * MAX)]   

# ↑, →, ↓, ←
dr = [-1, 0, 1, 0]
dc = [0, 1, 0, -1]

def input_data():            
    for h in range(1, H + 1):    
        for r in range(1, N + 1):
            MAP[h][r][1:M + 1] = map(int, input().split())

def print_map(): # for debug
    for h in range(H + 1):
        print("h :", h)
        for r in range(1, N + 1):
            print(*MAP[h][r][1:M + 1])
        print("")
          
def BFS():
    rp, wp = 0, 0
        
    for h in range(1, H + 1):
        for r in range(1, N + 1):
            for c in range(1, M + 1):
                if MAP[h][r][c] == 1:
                    queue[wp].h = h
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
            if MAP[out.h][nr][nc] != 0: continue
            
            queue[wp].h = out.h
            queue[wp].r = nr
            queue[wp].c = nc
            wp += 1
            
            MAP[out.h][nr][nc] = MAP[out.h][out.r][out.c] + 1
            
        # 아래로 가는 상자, (out.h - 1) != 0 조건 삭제
        if MAP[out.h - 1][out.r][out.c] == 0:
            queue[wp].h = out.h - 1
            queue[wp].r = out.r
            queue[wp].c = out.c
            wp += 1
            
            MAP[out.h - 1][out.r][out.c] = MAP[out.h][out.r][out.c] + 1
            
        # 위로 가는 상자, (out.h) != H 조건 삭제
        if MAP[out.h + 1][out.r][out.c] == 0:
            queue[wp].h = out.h + 1
            queue[wp].r = out.r
            queue[wp].c = out.c
            wp += 1
            
            MAP[out.h + 1][out.r][out.c] = MAP[out.h][out.r][out.c] + 1
                        
def getAnswer():
    max_answer = 0
    for h in range(1, H + 1):
        for r in range(1, N + 1):
            for c in range(1, M + 1):
                if MAP[h][r][c] == 0: return -1
                if max_answer < MAP[h][r][c]: max_answer = MAP[h][r][c]
            
    return max_answer - 1
                          
input_data()

BFS()

print(getAnswer())