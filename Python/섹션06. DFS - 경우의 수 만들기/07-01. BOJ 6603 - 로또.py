MAX = 13 + 3

num_of_cases = [0] * MAX
number = [0] * MAX

def input_data():
    global N
    
    line = list(map(int, input().split()))
    N = line[0]
    number[1:N + 1] = line[1:]
    
def print_cases():
    print(*num_of_cases[:6])

def DFS(depth, start):
    if depth == 6:
        print_cases()
        return

    for i in range(start, N + 1):
        num_of_cases[depth] = number[i]
        
        DFS(depth + 1, i + 1)

while True:
    input_data()
    
    if N == 0: break
    
    DFS(0, 1)
    
    print("")
    