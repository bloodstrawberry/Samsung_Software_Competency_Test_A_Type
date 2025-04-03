MAX = 10 + 5
INF = 0x7fff0000

MAP = [[0] * MAX for _ in range(MAX)]
num_of_cases = [0] * MAX

class RC:
    def __init__(self, r: int, c: int):
        self.r = r
        self.c = c

# ↑, →, ↓, ←
dr = [-1, 0, 1, 0]
dc = [0, 1, 0, -1]

def input_data():
    global N, M, RED, BLUE
    
    N, M = map(int, input().split())
    for r in range(N):
        MAP[r] = list(input())
    
    for r in range(N):
        for c in range(M):
            if MAP[r][c] == 'R': 
                RED = RC(r, c)
                MAP[r][c] = '.'
            elif MAP[r][c] == 'B': 
                BLUE = RC(r, c)
                MAP[r][c] = '.'
         
def printMap(): # for debug
    MAP[RED.r][RED.c] = 'R'
    MAP[BLUE.r][BLUE.c] = 'B'
    
    for r in range(N): print("".join(MAP[r][:M]))
        
    MAP[RED.r][RED.c] = '.'
    MAP[BLUE.r][BLUE.c] = '.'    
    
def printCases():
    print(*num_of_cases[:10])
    
def simulate():
    red = RC(RED.r, RED.c)
    blue = RC(BLUE.r, BLUE.c)
    
    for i in range(10):
        direction = num_of_cases[i]
        
        while 1:
            red_nr = red.r + dr[direction]
            red_nc = red.c + dc[direction]
            blue_nr = blue.r + dr[direction]
            blue_nc = blue.c + dc[direction]
            
            checkWallRed = MAP[red_nr][red_nc] == '#'
            checkWallBlue = MAP[blue_nr][blue_nc] == '#'
            checkCandyRed = (red_nr == blue.r) and (red_nc == blue.c)
            checkCandyBlue = (blue_nr == red.r) and (blue_nc == red.c)
            
            # 둘 다 다음 좌표가 벽이면 break
            if checkWallRed == True and checkWallBlue == True: break
            
            # 둘 다 다음 좌표가 벽이 아니라면, 1칸 이동
            if checkWallRed == False and checkWallBlue == False:
                red.r = red_nr
                red.c = red_nc
                
                blue.r = blue_nr
                blue.c = blue_nc
            # 둘 중 하나의 사탕만 움직이는 경우
            elif checkWallRed == True and checkCandyBlue == False:
                blue.r = blue_nr
                blue.c = blue_nc
            elif checkWallBlue == True and checkCandyRed == False:
                red.r = red_nr
                red.c = red_nc
            # 그 외 모든 경우 break
            else:
                break
            
            if MAP[red.r][red.c] == 'O':
                while MAP[blue.r][blue.c] != '#':
                    if MAP[blue.r][blue.c] == 'O': return INF
                    
                    blue.r += dr[direction]
                    blue.c += dc[direction]
                    
                return i + 1
   
            if MAP[blue.r][blue.c] == 'O': return INF

    return INF
      
def DFS(depth, direction):
    global minAnswer
    
    if depth == 10:
        # printCases()
        
        tmp = simulate()
        if tmp < minAnswer: minAnswer = tmp
        
        return

    for i in range(4):
        # 연속된 방향 무시
        if i == direction: continue
        
        num_of_cases[depth] = i
        
        DFS(depth + 1, i)
                    
# T = int(input())
T = 1
for tc in range(T):
    global minAnswer
    
    input_data()
        
    minAnswer = INF
    
    DFS(0, -1)
    
    if minAnswer == INF: print(-1)
    else: print(minAnswer)