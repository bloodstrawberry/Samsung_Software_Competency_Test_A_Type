# N, M 고치기

MAX = 50 + 10
MAX_HOSPITAL = 13 + 5
INF = 0x7fff0000

PERSON = 1
HOSPITAL = 2

MAP = [[0] * MAX for _ in range(MAX)]

num_of_cases = [0] * MAX_HOSPITAL

class RC:
    def __init__(self, r: int, c: int):
        self.r = r
        self.c = c

person = [RC(0, 0) for _ in range(MAX * MAX)]
hospital = [RC(0, 0) for _ in range(MAX * MAX)]
pcnt, hcnt = 0, 0

def input_data():
    global N, M, pcnt, hcnt
    
    N, M = map(int, input().split())
    
    pcnt, hcnt = 0, 0
    
    for r in range(1, N + 1):
        MAP[r][1:N + 1] = map(int, input().split())
    
    for r in range(1, N + 1):
        for c in range(1, N + 1):
            if MAP[r][c] == PERSON:
                person[pcnt].r = r
                person[pcnt].c = c
                pcnt += 1
            elif MAP[r][c] == HOSPITAL:
                hospital[hcnt].r = r
                hospital[hcnt].c = c
                hcnt += 1
                
def print_map(): # for debug    
    for r in range(1, N + 1):
        print(*MAP[r][1:N + 1])
    print("")

def print_cases():
    print(*num_of_cases[:M])

def get_distance(r1, c1, r2, c2):
    return abs(r1 - r2) + abs(c1 - c2)

def calculate():
    selected_hospital = [0] * MAX_HOSPITAL
    
    for i in range(M):
        selected_hospital[num_of_cases[i]] = True
    
    sum = 0
    for i in range(pcnt):
        min_distance = INF
        for k in range(hcnt):
            if selected_hospital[k] == False: continue
            
            distance = get_distance(person[i].r, person[i].c, hospital[k].r, hospital[k].c)
            
            min_distance = min(distance, min_distance)
        
        sum += min_distance

    return sum
    
def DFS(depth, start):
    global min_answer
    
    if depth == M: # M개를 고른 경우
        # print_cases()
        
        tmp = calculate()
        if tmp < min_answer: min_answer = tmp

        return
    
    for i in range(start, hcnt): # 병원의 개수에서
        num_of_cases[depth] = i
        
        DFS(depth + 1, i + 1)
    
# T = int(input())
T = 1
for tc in range(T):
    global min_answer
    
    input_data()
    
    min_answer = INF
    
    DFS(0, 0)
    
    print(min_answer)