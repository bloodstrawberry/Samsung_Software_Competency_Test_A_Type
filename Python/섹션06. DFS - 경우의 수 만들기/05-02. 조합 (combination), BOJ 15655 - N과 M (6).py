MAX = 8 + 3

N, M = map(int, input().split())

num_of_cases = [0] * MAX
visit = [False] * MAX
number = [0] * MAX

def print_cases():
    print(*num_of_cases[:M])

def DFS(depth, start):
    if depth == M:
        print_cases()
        return
    
    for i in range(start, N + 1):
        if visit[i] == True : continue
        
        num_of_cases[depth] = number[i]
        
        visit[i] = True
        DFS(depth + 1, i + 1)
        visit[i] = False

number[1:N + 1] = sorted(list(map(int, input().split())))
                 
DFS(0, 1)