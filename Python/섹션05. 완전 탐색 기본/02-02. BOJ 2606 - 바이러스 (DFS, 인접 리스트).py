MAX = 100 + 10

MAP = [[0] * MAX for _ in range(MAX)]
index = [0] * MAX
visit = [False] * MAX

count = 0

def input_data():
    global V, E

    V = int(input()) # Vertex
    E = int(input()) # Edge

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

def DFS(node):      
    global count
      
    visit[node] = True

    for i in range(index[node]):        
        number = MAP[node][i]
        
        if visit[number] == True: continue

        count = count + 1

        DFS(number)
       
input_data()
        
DFS(1)

print(count)
