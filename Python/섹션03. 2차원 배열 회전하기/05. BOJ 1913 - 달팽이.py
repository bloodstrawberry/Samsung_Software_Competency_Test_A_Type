MAX = 1000 + 100

dr = [-1, 0, 1, 0]
dc = [0, 1, 0, -1]

MAP = [[0] * MAX for _ in range(MAX)]

N = int(input())
K = int(input())

def print_map():
    for r in range(1, N + 1):
        print(*MAP[r][1:N + 1])
    print("")

def make_snail():
    r = c = ansR = ansC = (N + 1) // 2
    direction = 0
    index = 1
    size = 0
    
    MAP[r][c] = index
    index += 1
    
    for i in range(2 * N - 1):
        if i % 2 == 0: size += 1
        
        for s in range(size):
            nr = r + dr[direction]
            nc = c + dc[direction]
            
            if index == K : ansR, ansC = nr, nc
            
            MAP[nr][nc] = index
            index += 1
            
            r, c = nr, nc
            
        direction += 1
        
        if direction == 4: direction = 0
    
    print_map()
    
    print(ansR, ansC)
    
make_snail()
