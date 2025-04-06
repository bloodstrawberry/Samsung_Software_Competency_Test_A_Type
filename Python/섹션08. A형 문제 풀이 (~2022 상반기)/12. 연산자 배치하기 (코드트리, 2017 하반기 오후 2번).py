MAX = 11 + 5
INF = 0x7fff0000

PLUS = 0
MINUS = 1
MULTIPLY = 2

num_of_cases = [0] * MAX
visit = [0] * MAX
possible = [0] * 3 # 사용할 수 있는 최대 PLUS, MINUS, MULTIPLY 
number = [0] * MAX

def input_data():
    global N, number, possible
    
    N = int(input())
    
    number = list(map(int, input().split()))
    possible = list(map(int, input().split()))

def print_cases():
    print(*print_cases[:N - 1])

def calculate():
    sum = number[0]
    for i in range(N - 1):
        if num_of_cases[i] == PLUS: sum += number[i + 1]
        elif num_of_cases[i] == MINUS: sum -= number[i + 1]
        elif num_of_cases[i] == MULTIPLY: sum *= number[i + 1]
        
    return sum

def DFS(depth):
    global min_answer, max_answer
    
    if depth == N - 1:
        # print_cases()
        
        tmp = calculate()
        if max_answer < tmp: max_answer = tmp
        if min_answer > tmp: min_answer = tmp
            
        return

    for i in range(3):
        if visit[i] == possible[i]: continue

        num_of_cases[depth] = i
        
        visit[i] += 1
        DFS(depth + 1)
        visit[i] -= 1

# T = int(input())
T = 1
for tc in range(T):
    global min_answer, max_answer
    
    input_data()
    
    min_answer = INF
    max_answer = -INF
    
    DFS(0)
    
    print(min_answer, max_answer)