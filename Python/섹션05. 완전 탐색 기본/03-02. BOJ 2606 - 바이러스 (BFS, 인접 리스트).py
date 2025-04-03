MAX = 100 + 10

MAP = [[0] * MAX for _ in range(MAX)]
index = [0] * MAX

queue = [0] * MAX
visit = [False] * MAX

def input_data():
    global V, E

    V = int(input())
    E = int(input())

    for _ in range(E):
        n1, n2 = map(int, input().split())
        
        MAP[n1][index[n1]] = n2
        index[n1] += 1
        MAP[n2][index[n2]] = n1
        index[n2] += 1
        
def print_map(): # for debug
    for r in range(1, V + 1):
        print(*MAP[r][:index[r]])
    print("")

def BFS(node):
    rp, wp = 0, 0

    queue[wp] = node
    wp += 1
    
    visit[node] = True
    
    count = 0
    while rp < wp:
        out = queue[rp]
        rp += 1
        
        for i in range(index[out]):
            number = MAP[out][i]
            
            if visit[number] == True : continue
            
            count += 1
            
            queue[wp] = number
            wp += 1
            
            visit[number] = True
    
    print(count)
    
input_data()
        
BFS(1)