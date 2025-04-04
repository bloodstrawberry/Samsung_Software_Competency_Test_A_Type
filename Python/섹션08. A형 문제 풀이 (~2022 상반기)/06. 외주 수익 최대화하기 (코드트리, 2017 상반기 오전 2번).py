MAX = 15 + 5

time = [0] * MAX
profit = [0] * MAX

num_of_cases = [0] * MAX

def input_data():             
    global N
    
    N = int(input())
        
    for i in range(1, N + 1):
        time[i], profit[i] = map(int, input().split())
                                
def print_cases(): 
    print(*num_of_cases[1:N + 1])
   
def check():
    visit = [False] * MAX
    for i in range(1, N + 1):
        if num_of_cases[i] == 0: continue
        
        for k in range(time[i]):
            if N < i + k: return False
            # i + k가 MAX를 넘지 않도록 주의!, 작업 기한의 최대값은 5
            if visit[i + k] == True: return False
            
            visit[i + k] = True
    
    return True

def getProfit():
    sum = 0
    for i in range(1, N + 1):
        sum += (num_of_cases[i] * profit[i])
    
    return sum

def DFS(depth):
    global max_answer
    
    if depth == N:
        # print_cases()
        
        if check() == True:
            tmp = getProfit()
            if max_answer < tmp: max_answer = tmp
        
        return
    
    for i in range(2):
        num_of_cases[depth + 1] = i # 1일차 ~ N일차
        
        DFS(depth + 1)
          
# T = int(input())
T = 1
for _ in range(T):
    global max_answer
    
    input_data()     
    
    max_answer = 0
    
    DFS(0)
    
    print(max_answer)