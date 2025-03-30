MAX = 100 + 10

MAP = [[0] * MAX for _ in range(MAX)]
visit = [False] * MAX

count = 0

def input_data():
    global V, E

    V = int(input()) # Vertex
    E = int(input()) # Edge

    for _ in range(E):
        n1, n2 = map(int, input().split())
        MAP[n1][n2] = MAP[n2][n1] = 1    

def print_map(): # for debug
    for r in range(1, V + 1):
        print(*MAP[r][1:V + 1])

def DFS(node):      
    global count
      
    visit[node] = True

    for c in range(1, V + 1):        
        if MAP[node][c] == 0 or visit[c] == True: continue

        count = count + 1

        DFS(c)
       
input_data()
        
DFS(1)

print(count)
