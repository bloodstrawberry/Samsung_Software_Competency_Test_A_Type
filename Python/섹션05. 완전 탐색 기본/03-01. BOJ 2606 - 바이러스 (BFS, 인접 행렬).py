MAX = 100 + 10

MAP = [[0] * MAX for _ in range(MAX)]

queue = [0] * MAX
visit = [False] * MAX

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

def BFS(node):
    rp, wp = 0, 0

    queue[wp] = node
    wp += 1
    
    visit[node] = True
    
    count = 0
    while rp < wp:
        out = queue[rp]
        rp += 1
        
        for c in range(1, V + 1):
            if MAP[out][c] == 0 or visit[c] == True: continue
                        
            count += 1
            
            queue[wp] = c
            wp += 1
            
            visit[c] = True
        
    print(count)
    
input_data()
        
BFS(1)

