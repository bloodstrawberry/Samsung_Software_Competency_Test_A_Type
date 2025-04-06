MAX = 100 + 20

MAP = [[0] * MAX for _ in range(MAX)]
dragonPosition = [0] * 2000  # 2^10보다 큰 값 

# 오른쪽, 위쪽, 왼쪽, 아래쪽
dr = [0, -1, 0, 1]
dc = [1, 0, -1, 0]

def make_dragon_curve():    
    N = int(input())

    for _ in range(N):
        r, c, d, g = map(int, input().split())

        dragonPosition[0] = d
        
        length = 1
        for step in range(1, g + 1):
            for i in range(length + 1, length * 2 + 1):
                dragonPosition[i - 1] = (dragonPosition[length * 2 - i] + 1) % 4
                
            length *= 2

        MAP[r][c] = 1

        move_count = 1 << g # move = 2^g
        for k in range(move_count):
            r = r + dr[dragonPosition[k]]
            c = c + dc[dragonPosition[k]]
            
            MAP[r][c] = 1

def count_square():
    sum = 0
    for r in range(100):
        for c in range(100):
            if MAP[r][c] + MAP[r + 1][c] + MAP[r][c + 1] + MAP[r + 1][c + 1] == 4:
                sum += 1
    return sum

# T = int(input())
T = 1
for _ in range(T):
    make_dragon_curve()
    
    print(count_square())
