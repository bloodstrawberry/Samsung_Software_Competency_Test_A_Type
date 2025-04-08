MAX = 100 + 20

MAP = [[0] * MAX for _ in range(MAX)]

class GRID:
    def __init__(self, value: int, count: int):
        self.value = value
        self.count = count

grid = [GRID(0, 0) for _ in range(MAX)]

def input_data():
    global R, C, K
    
    R, C, K = map(int, input().split())
    
    for r in range(1, 4):
        MAP[r][1:4] = map(int, input().split())

def print_map(row, col): # for debug
    for r in range(1, row + 1):
        print(MAP[r][1:col + 1])
    print("")

def make_array_row(row, col):
    count = [0] * MAX
    number = [0] * MAX
    ncnt = 0
    
    for c in range(1, col + 1):
        if MAP[row][c] == 0: continue
        
        value = MAP[row][c]
        if count[value] == 0: 
            number[ncnt] = value
            ncnt += 1
        
        count[value] += 1
    
    for i in range(ncnt):
        value = number[i]
        
        grid[i].value = value
        grid[i].count = count[value]    
    
    for i in range(ncnt - 1):
        for k in range(i + 1, ncnt):
            if ((grid[i].count > grid[k].count) \
				or ((grid[i].count == grid[k].count) and (grid[i].value > grid[k].value))):
            
                grid[i], grid[k] = grid[k], grid[i]
                
    index = 1
    for i in range(ncnt):
        MAP[row][index] = grid[i].value
        index += 1
        MAP[row][index] = grid[i].count
        index += 1
        
        # 배열이 100을 넘어가는 경우
        # if index == 101: break
    
    for i in range(index, col + 1): MAP[row][i] = 0

    return index - 1


def transpose(row, col):
    for r in range(1, max(row, col)):
        for c in range(r + 1, max(row, col) + 1):
            MAP[r][c], MAP[c][r] = MAP[c][r], MAP[r][c]

def simulate():
    if MAP[R][C] == K: return 0

    len_r, len_c = 3, 3
    for i in range(1, 101):
        if len_r >= len_c:
            for r in range(1, len_r + 1):
                length = make_array_row(r, len_c)
                if len_c < length: len_c = length                
        else:
            transpose(len_r, len_c)
            len_r, len_c = len_c, len_r

            for r in range(1, len_r + 1):
                length = make_array_row(r, len_c)
                if len_c < length: len_c = length

            len_r, len_c = len_c, len_r
            transpose(len_r, len_c)

        if MAP[R][C] == K: return i

    return -1

# T = int(input())
T = 1
for tc in range(T):
    input_data()
    
    print(simulate())