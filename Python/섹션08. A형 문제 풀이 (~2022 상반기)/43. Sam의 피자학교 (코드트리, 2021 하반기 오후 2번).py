MAX = 100 + 10
INF = 0x7fff0000

pizza = [[0] * MAX for _ in range(MAX)]

class RC:
    def __init__(self, r: int, c: int):
        self.r = r
        self.c = c

# ↑, →, ↓, ←
dr = [-1, 0, 1, 0]
dc = [0, 1, 0, -1]

def input_data():
    global N, K, pizza
    
    N, K = map(int, input().split())

    # 초기화
    pizza = [[0] * MAX for _ in range(MAX)]

    values = list(map(int, input().split()))
    for c in range(1, N + 1):
        pizza[N][c] = values[c - 1]

def print_map(): # for debug
    for r in range(1, N + 1):
        print(' '.join('%2d' % num for num in pizza[r][1:N + 1]))
    print("")

def add_flour():
    min_val = min(pizza[N][1:N+1])
    
    for c in range(1, N + 1):
        if pizza[N][c] == min_val:
            pizza[N][c] += 1

def roll():
    # 1, 1 x 1
	# 2, 2 x 1
	# 3, 2 x 2
	# 5, 3 x 2
	# 7, 3 x 3
	# 10, 4 x 3
 
    start = height = width = 1
    
    count = 0
    while True:
        if start + height + width - 1 > N: break
        
        # 밀가루 이동
        for c in range(start, start + width):
            for r in range(N, N - height, -1):
                nr = N - width + (c - start)
                nc = start + width + (N - r)
                
                pizza[nr][nc] = pizza[r][c]
                pizza[r][c] = 0

        if count % 2 == 0: height += 1
        else: width += 1

        start += (count // 2 + 1)
        
        count += 1

def press():
    tmp_pizza = [[0] * MAX for _ in range(MAX)]    
    for r in range(1, N + 1):
        for c in range(1, N + 1):
            if pizza[r][c] == 0: continue
            
            flour = pizza[r][c]
            
            for i in range(4):
                nr = r + dr[i]
                nc = c + dc[i]
                
                if pizza[nr][nc] == 0: continue
                
                if pizza[r][c] > pizza[nr][nc]:
                    diff = (pizza[r][c] - pizza[nr][nc]) // 5
                    
                    flour -= diff
                    tmp_pizza[nr][nc] += diff
                    
            tmp_pizza[r][c] += flour

    index = 1
    for c in range(1, N + 1):
        if tmp_pizza[N][c] == 0: continue
        
        sr = N
        while True:
            if tmp_pizza[sr][c] == 0: break
            
            pizza[N][index] = tmp_pizza[sr][c]
            index += 1
            sr -= 1

    for r in range(1, N):
        for c in range(1, N + 1):
            pizza[r][c] = 0

def fold():
    # 한 번 접기
    sc = (N // 2) + 1
    for c in range((N // 2), 0, -1):
        pizza[N - 1][sc] = pizza[N][c]
        pizza[N][c] = 0
        sc += 1

    # 두 번 접기
    nr = N - 2
    for r in range(N - 1, N + 1):
        ec = (N // 4) * 3
        nc = N
        for c in range((N // 2) + 1, ec + 1):
            pizza[nr][nc] = pizza[r][c]
            pizza[r][c] = 0
            nc -= 1
            
        nr -= 1

def check():
    values = pizza[N][1:N+1]
    return max(values) - min(values) <= K

def simulate():
    count = 0
    while True:
        add_flour()
        roll()
        press()
        fold()
        press()
        
        count += 1
        
        if check(): break
        
    return count

# T = int(input())
T = 1
for tc in range(T):    
    input_data()
    
    print(simulate())

