MAX = 50 + 10

LEFT = 0 # 서
UP = 1 # 북
RIGHT = 2 # 동
DOWN = 3 # 남

M, N = map(int, input().split())

# init 
MAP = [[15] * MAX for _ in range(MAX)] # 모두 벽으로 초기화
visit = [[0] * MAX for _ in range(MAX)]

class RC:
    def __init__(self, r: int, c: int):
        self.r = r
        self.c = c
    
queue = [RC(0, 0) for _ in range(MAX * MAX)]   

# 서쪽, 북쪽, 동쪽, 남쪽
dr = [0, -1, 0, 1]
dc = [-1, 0, 1, 0]

WALL = [
    [0, 0, 0, 0],
	[1, 0, 0, 0],
	[0, 1, 0, 0],
	[1, 1, 0, 0],
	[0, 0, 1, 0],
	[1, 0, 1, 0],
	[0, 1, 1, 0],
	[1, 1, 1, 0],
	[0, 0, 0, 1],
	[1, 0, 0, 1],
	[0, 1, 0, 1],
	[1, 1, 0, 1],
	[0, 0, 1, 1],
	[1, 0, 1, 1],
	[0, 1, 1, 1],
	[1, 1, 1, 1],     
]

# room1 = room1에 적힌 값
def isOpen(room1, room2, direction):
    if direction == LEFT:
        return not (WALL[room1][LEFT] or WALL[room2][RIGHT])
    
    if direction == UP:
        return not (WALL[room1][UP] or WALL[room2][DOWN])
    
    if direction == RIGHT:
        return not (WALL[room1][RIGHT] or WALL[room2][LEFT])
    
    if direction == DOWN:
        return not (WALL[room1][DOWN] or WALL[room2][UP])
    
    return -1 # error
    
def input_data():             
    for r in range(1, N + 1):
        MAP[r][1:M + 1] = map(int, input().split())

def print_map(): # for debug
    for r in range(1, N + 1):
        print(*MAP[r][1:M + 1])    
    print("")
    
    for r in range(1, N + 1):
        print(*visit[r][1:M + 1])        
    print("")
                      
def BFS(r, c, mark):
    rp, wp = 0, 0
    
    queue[wp].r = r
    queue[wp].c = c
    wp += 1
    
    visit[r][c] = mark
                    
    while rp < wp:
        out = queue[rp]
        rp += 1
                
        for i in range(4):
            nr = out.r + dr[i]
            nc = out.c + dc[i]
            
            if isOpen(MAP[out.r][out.c], MAP[nr][nc], i) == 0 or visit[nr][nc] != 0: continue                    
            
            queue[wp].r = nr
            queue[wp].c = nc
            wp += 1
            
            visit[nr][nc] = mark

    return wp
                 
input_data()                 
                                      
mark = 1
answer_count = 1 # 1번부터 입력
answers = [0] * (MAX * MAX)
for r in range(1, N + 1):
    for c in range(1, M + 1):
        if visit[r][c] == 0:
            answers[answer_count] = BFS(r, c, mark)
            answer_count += 1
            mark += 1
            
max_answer = max(answers[1 : answer_count + 1])

max_area_sum = 0
for r in range(1, N + 1):
    for c in range(1, M + 1):
        for i in range(4):
            nr = r + dr[i]
            nc = c + dc[i]
            
            # if nr < 1 or nc < 1 or nr > N or nc > M: continue
            if visit[r][c] == visit[nr][nc]: continue
            
            tmp_area = answers[visit[r][c]] + answers[visit[nr][nc]]
            if max_area_sum < tmp_area: max_area_sum = tmp_area

print(answer_count - 1)            
print(max_answer)
print(max_area_sum)