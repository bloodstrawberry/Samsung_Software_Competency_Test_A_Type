# Python3 Timeout
# PyPy3 Pass

MAX = 10000 + 500
OFFSET = MAX // 2

deque = [0] * MAX * 2
front, back = OFFSET, OFFSET

N = int(input())

for _ in range(N):
    line = input().split()
    
    command = line[0]
        
    if command == "push_front":
        value = int(line[1])
        deque[front - 1] = value
        front -= 1
    elif command == "push_back":
        value = int(line[1])
        deque[back] = value
        back += 1
    elif command == "pop_front":
        if back == front: print(-1)
        else: 
            print(deque[front])
            front += 1
    elif command == "pop_back":
        if back == front: print(-1)
        else: 
            print(deque[back - 1])       
            back -= 1
    elif command == "size":
        print(back - front)
    elif command == "empty":
        print(int(back == front))
    elif command == "front":
        print(-1 if back == front else deque[front])
    elif command == "back":
        print(-1 if back == front else deque[back - 1])
    
        
    
        