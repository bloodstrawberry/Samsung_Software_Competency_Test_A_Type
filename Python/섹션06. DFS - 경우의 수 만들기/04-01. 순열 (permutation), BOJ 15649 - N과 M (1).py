MAX = 8 + 3

N, M = map(int, input().split())

num_of_cases = [0] * MAX
visit = [False] * MAX

def print_cases():
    print(*num_of_cases[:M])

def DFS(depth):
    if depth == M:
        print_cases()
        return
    
    for i in range(1, N + 1):
        if visit[i] == True : continue
        
        num_of_cases[depth] = i
        
        visit[i] = True
        DFS(depth + 1)
        visit[i] = False
                 
DFS(0)