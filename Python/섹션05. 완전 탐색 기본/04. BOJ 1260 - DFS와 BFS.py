MAX = 1000 + 50

MAP = [[0] * MAX for _ in range(MAX)]

queue = [0] * MAX
visit = [False] * MAX

def input_data():
    global N, M, V
 
    N, M, V = map(int, input().split())
         
    for _ in range(M):
        n1, n2 = map(int, input().split())        
        MAP[n1][n2] = MAP[n2][n1] = 1
        
def print_map(): # for debug
    for r in range(1, N + 1):
        print(*MAP[r][1:N + 1])

def DFS(node):
    visit[node] = True
    
    print(node, end=" ")
    
    for c in range(1, N + 1):
        if MAP[node][c] == 0 or visit[c] == True: continue
        
        DFS(c)
    
def BFS(node):
    rp, wp = 0, 0
    
    queue[wp] = node
    wp += 1
    
    visit[node] = True
    
    while rp < wp:
        out = queue[rp]
        rp += 1
        
        print(out, end=" ")
        
        for c in range(1, N + 1):
            if MAP[out][c] == 0 or visit[c] == True: continue
            
            queue[wp] = c
            wp += 1
            
            visit[c] = True
            
input_data()

DFS(V)
print("")

visit = [False] * MAX
      
BFS(V)
