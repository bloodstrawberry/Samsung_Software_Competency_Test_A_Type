MAX = 8 + 3

N, M = map(int, input().split())

num_of_cases = [0] * MAX
visit = [False] * MAX
possible = [0] * (10000 + 500)
number = [0] * MAX

def print_cases():
    print(*num_of_cases[:M])

def DFS(depth):       
    if depth == M:
        print_cases()
        return
    
    for i in range(1, N + 1):
        if visit[i] == possible[number[i]] : continue
        
        num_of_cases[depth] = number[i]
        
        visit[i] += 1
        DFS(depth + 1)
        visit[i] -= 1

tmp_number = list(map(int, input().split()))

for value in tmp_number:
    possible[value] += 1
    
tmp_number = sorted(list(set(tmp_number)))

N = len(tmp_number)

number[1:N + 1] = tmp_number
                 
DFS(0)