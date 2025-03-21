MAX = 1000 + 100

queue = [0] * MAX * 2
rp, wp = 0, 0

N = int(input())

for i in range(1, N + 1):
    queue[wp] = i
    wp += 1
    
for _ in range(N - 1):
    print(queue[rp], end=' ')
    rp += 1
    
    queue[wp] = queue[rp]
    rp += 1
    wp += 1
    
print(queue[wp - 1])