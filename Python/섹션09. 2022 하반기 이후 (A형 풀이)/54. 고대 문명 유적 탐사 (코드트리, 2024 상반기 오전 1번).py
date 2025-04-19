import copy

MAX = 5 + 3

MAP = [[0] * MAX for _ in range(MAX)]
visit = [[False] * MAX for _ in range(MAX)]

class RC:
    def __init__(self, r: int, c: int):
        self.r = r
        self.c = c

queue = [RC(0, 0) for _ in range(MAX * MAX)]

# ↑, →, ↓, ←
dr = [-1, 0, 1, 0]
dc = [0, 1, 0, -1]


def input_data():   
    global K, M, MAP, piece, pcnt
    
    K, M = map(int, input().split())
        
    for r in range(1, 6):
        MAP[r][1:6]= map(int, input().split())
    
    pcnt = 0
    
    piece = list(map(int, input().split()))
            
def print_map(map): # for debug
    for r in range(1, 6):
        print(*map[r][1:6])
    print("")

def rotate(map, sr, sc):
    tmp_map = [[0] * MAX for _ in range(MAX)]
    
    size = 3
    for r in range(size):
        for c in range(size):
            tmp_map[r][c] = map[sr + r][sc + c]
    
    for r in range(size):
        for c in range(size):
            map[sr + r][sc + c] = tmp_map[size - 1 - c][r]
    
def BFS(map, r, c):
    rp, wp = 0, 0
    
    number = map[r][c]
    
    queue[wp].r = r
    queue[wp].c = c
    wp += 1
    
    visit[r][c] = True
    
    while rp < wp:
        out = queue[rp]
        rp += 1
        
        for i in range(4):
            nr = out.r + dr[i]
            nc = out.c + dc[i]
            
            if map[nr][nc] != number or visit[nr][nc] == True: continue
                        
            queue[wp].r = nr
            queue[wp].c = nc
            wp += 1
            
            visit[nr][nc] = True
            
    if wp < 3: return 0
    
    for i in range(wp):
        r, c = queue[i].r, queue[i].c
        map[r][c] = 0
            
    return wp
    
def get_item(map):
    global visit

    visit = [[False] * MAX for _ in range(MAX)]

    sum = 0
    for r in range(1, 6):
        for c in range(1, 6):
            if visit[r][c] == True: continue

            count = BFS(map, r, c)
            sum += count

    return sum

def set_item(map):    
    global pcnt
    
    for c in range(1, 6):
        for r in range(5, 0, -1):
            if map[r][c] == 0: 
                map[r][c] = piece[pcnt]
                pcnt += 1

def simulate():
    global MAP
    
    max_item_count = 0
    max_map = [[0] * MAX for _ in range(MAX)]

    # 회전 각도가 작고
    for rot in range(1, 4):
        # 열이 작고
        for c in range(1, 4):
            # 행이 작은 순서대로
            for r in range(1, 4):
                tmp_map = copy.deepcopy(MAP)

                for rot_count in range(1, rot + 1):
                    rotate(tmp_map, r, c)

                item_count = get_item(tmp_map)
                if max_item_count < item_count:
                    max_item_count = item_count
                    max_map = copy.deepcopy(tmp_map)

    if max_item_count == 0: return 0

    sum = max_item_count
    while True:
        set_item(max_map)

        item_count = get_item(max_map)

        if item_count == 0: break

        sum += item_count

    MAP = copy.deepcopy(max_map)

    return sum
    

# T = int(input())
T = 1
for tc in range(T):    
    input_data()
    
    for k in range(K):
        result = simulate()
        
        if result == 0: break
        
        print(result, end=" ")