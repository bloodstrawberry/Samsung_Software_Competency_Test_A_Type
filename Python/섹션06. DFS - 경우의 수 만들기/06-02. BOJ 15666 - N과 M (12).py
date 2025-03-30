MAX = 7 + 3

N, M = map(int, input().split())

num_of_cases = [0] * MAX
number = [0] * MAX

def print_cases():
    print(*num_of_cases[:M])

def DFS(depth, start):
    if depth == M:
        print_cases()
        return
    
    for i in range(start, N + 1):        
        num_of_cases[depth] = number[i]
        
        DFS(depth + 1, i)    
     
tmp_number = sorted(list(set(map(int, input().split()))))

N = len(tmp_number)

number[1:N + 1] = tmp_number
                 
DFS(0, 1)