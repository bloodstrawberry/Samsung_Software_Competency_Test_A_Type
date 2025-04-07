MAX = 20 + 5

EAST = 1
WEST = 2
NORTH = 3
SOUTH = 4

MAP = [[0] * MAX for _ in range(MAX)]
command = [0] * (1000 + 50)

class CUBE:
    def __init__(self, up: int, left: int, top: int, right: int, down: int, bottom: int):
        self.up = up
        self.left = left
        self.top = top
        self.right = right
        self.down = down
        self.bottom = bottom        

cube = CUBE(0, 0, 0, 0, 0, 0)

# -, 동, 서, 북, 남 
dr = [0, 0, 0, -1, 1]
dc = [0, 1, -1, 0, 0]

def input_data():             
    global N, M, R, C, K
    
    N, M, R, C, K = map(int, input().split())
    
    for r in range(N):
        MAP[r][:M] = map(int, input().split())
            
    command[:K] = map(int, input().split())

def print_map(): # for debug
    for r in range(N):
        print(*MAP[r][:M])
    print("")
    
    print(*command[:K])
    print("")
    
def print_cube(): # for debug
    print(cube.up)
    print(cube.left, cube.top, cube.right)
    print(cube.down)
    print(cube.bottom)
    print("")
    
def move_east():
    tmp = [cube.up, cube.left, cube.top, cube.right, cube.down, cube.bottom]
    
    cube.top = tmp[1]
    cube.right = tmp[2]
    cube.bottom = tmp[3]
    cube.left = tmp[5]

def move_west():
    tmp = [cube.up, cube.left, cube.top, cube.right, cube.down, cube.bottom]
    
    cube.top = tmp[3]
    cube.right = tmp[5]
    cube.bottom = tmp[1]
    cube.left = tmp[2]
    
def move_north():
    tmp = [cube.up, cube.left, cube.top, cube.right, cube.down, cube.bottom]
    
    cube.up = tmp[2]
    cube.top = tmp[4]
    cube.down = tmp[5]
    cube.bottom = tmp[0]
    
def move_south():
    tmp = [cube.up, cube.left, cube.top, cube.right, cube.down, cube.bottom]
    
    cube.up = tmp[5]
    cube.top = tmp[0]
    cube.down = tmp[2]
    cube.bottom = tmp[4]
        
def simulate():
    global R, C
    
    for k in range(K):
        cmd = command[k]
                
        # 바깥으로 나가게 되는 경우
        if R + dr[cmd] < 0 or R + dr[cmd] > N - 1 or C + dc[cmd] < 0 or C + dc[cmd] > M - 1: continue
        
        R = R + dr[cmd]
        C = C + dc[cmd]
        
        if cmd == EAST: move_east()
        elif cmd == WEST: move_west()
        elif cmd == NORTH: move_north()
        elif cmd == SOUTH: move_south()
        
        # 칸에 쓰여져 있는 수가 0이면, 주사위 바닥 면의 수가 복사
        if MAP[R][C] == 0: MAP[R][C] = cube.bottom
        else: # 0이 아니면, 주사위 바닥면으로 숫자를 복사하고, 해당 칸은 0
            cube.bottom = MAP[R][C]
            MAP[R][C] = 0
        
        print(cube.top)        
                
# T = int(input())
T = 1
for tc in range(T):
    input_data()     
    
    simulate()            
                      
                      
                  
