#C++ 코드, 고치기
MAX = 8 + 3

num_of_cases = [0] * MAX
visit = [False] * MAX
number = [0] * MAX

max_answer = -1

N = int(input())
number[0:N] = list(map(int, input().split()))

def print_cases():
    print(*num_of_cases[:N])

def calculate():
    sum = 0
    
    for i in range(N - 1):
        sum += abs(num_of_cases[i] - num_of_cases[i + 1])
    
    return sum

def DFS(depth):
    global max_answer
    
    if depth == N:
        # print_cases()
        tmp = calculate()
        if max_answer < tmp: max_answer = tmp
        
        return
    
    for i in range(N):
        if visit[i] == True: continue
        
        num_of_cases[depth] = number[i]
        
        visit[i] = True
        DFS(depth + 1)
        visit[i] = False
    
DFS(0)

print(max_answer)