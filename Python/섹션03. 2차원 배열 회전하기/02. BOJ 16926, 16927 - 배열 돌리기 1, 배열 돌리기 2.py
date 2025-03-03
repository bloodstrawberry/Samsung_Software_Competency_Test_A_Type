import copy

MAX = 300 + 30
MAP = [[0] * MAX for _ in range(MAX)]

N, M, R = map(int,input().split())

class RC:
    def __init__(self, r: int, c: int):
        self.r = r
        self.c = c

arr = [RC(0, 0) for _ in range(MAX * MAX)]

def input_data():
    for r in range(1, N + 1):
        MAP[r][1:N + 1] = map(int, input().split())

def print_map():
    for r in range(1, N + 1):
        print(" ".join(map(str, MAP[r][1:M + 1])))

def rotate_step(sr, sc, n, m, rotate_count):
    er = sr + n - 1
    ec = sc + m - 1

    temp = copy.deepcopy(MAP)
        
    index = 0
    for c in range(sc, ec + 1):
        arr[index] = RC(sr, c)
        index += 1
        
    for r in range(sr + 1, er + 1):
        arr[index] = RC(r, ec)
        index += 1
        
    for c in range(ec - 1, sc - 1, -1):
        arr[index] = RC(er, c)
        index += 1
        
    for r in range(er - 1, sr, -1):
        arr[index] = RC(r, sc)
        index += 1
                
    for i in range(index):
        newIndex = (i - rotate_count) % index
        newIndex = newIndex + index if newIndex < 0 else newIndex
        front = arr[newIndex]
        MAP[front.r][front.c] = temp[arr[i].r][arr[i].c]
        
def rotate(rotate_count):
    step = min(N, M) // 2
    sr, sc = 1, 1
    n, m = N, M
    
    for _ in range(step):
        rotate_step(sr, sc, n, m, rotate_count)
        sr += 1
        sc += 1
        n -= 2
        m -= 2

input_data()
rotate(R)
print_map()

