# Python3 Timeout
# PyPy3 Pass (큐2 Timeout)

MAX = 10000 + 500

queue = [0] * MAX
rp, wp = 0, 0

N = int(input())

for _ in range(N):
    line = input().split()
    
    command = line[0]
    
    if command == "push":
        value = int(line[1])
        queue[wp] = value
        wp += 1
    elif command == "pop":
        if wp == rp : print(-1)
        else:
            print(queue[rp])
            rp += 1
    elif command == "size":
        print(wp - rp)
    elif command == "empty":
        print(int(wp == rp))
    elif command == "front":
        print(-1 if wp == rp else queue[rp])
    elif command == "back":
        print(-1 if wp == rp else queue[wp - 1])
    
        
    
        