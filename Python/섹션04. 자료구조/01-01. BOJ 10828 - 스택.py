# Python3 Time Out
# PyPy3 Pass

MAX = 10000 + 100

stack = [0] * MAX
sp = 0

N = int(input())

for _ in range(N):
    line = input().split()
    
    command = line[0]
    
    if command == "push": 
        value = int(line[1])
        stack[sp] = value
        sp += 1
    elif command == "pop": 
        if sp != 0: 
            print(stack[sp - 1])
            sp -=1
        else:
            print(-1)
    elif command == "size":
        print(sp)
    elif command == "empty":
        print(0 if sp > 0 else 1)
    elif command == "top":
        print(stack[sp - 1] if sp > 0 else -1)
    
        