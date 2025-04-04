MAX = 20 + 5
INF = 0x7fff0000

MAP = [[0] * MAX for _ in range(MAX)]
num_of_cases = [0] * MAX

def input_data():             
    global N, halfN
    
    N = int(input())
        
    halfN = N // 2
    for r in range(1, N + 1):
        MAP[r][1:N + 1] = map(int, input().split())
                                
def print_cases():
    print(*num_of_cases[:halfN])
   
def calculate():
    isMorning = [False] * MAX
    morning = [0] * MAX
    dinner = [0] * MAX
    
    for i in range(halfN):
        isMorning[num_of_cases[i]] = True
        
    mcnt, dcnt = 0, 0
    for i in range(1, N + 1):
        if isMorning[i] == True: 
            morning[mcnt] = i
            mcnt += 1
        else:
            dinner[dcnt] = i
            dcnt += 1
            
    # for debug
    # print("morning :", *morning[:mcnt])
    # print("dinner :", *dinner[:dcnt])
            
    sum1, sum2 = 0, 0
    
    # 23 24 34 / 15 16 56
    for i in range(halfN):
        for k in range(i + 1, halfN):
            mr = morning[i]
            mc = morning[k]
            dr = dinner[i]
            dc = dinner[k]
            
            sum1 += (MAP[mr][mc] + MAP[mc][mr])
            sum2 += (MAP[dr][dc] + MAP[dc][dr])
    
    return abs(sum1 - sum2)

def DFS(depth, start):    
    global min_answer
    
    if depth == halfN:
        # print_cases()
            
        tmp = calculate()
        if tmp < min_answer: min_answer = tmp
        
        return
    
    for i in range(start, N + 1):
        num_of_cases[depth] = i
        DFS(depth + 1, i + 1)
        
# T = int(input())
T = 1
for _ in range(T): 
    global min_answer
    
    input_data()     
        
    min_answer = INF
    
    DFS(0, 1)
    
    print(min_answer)