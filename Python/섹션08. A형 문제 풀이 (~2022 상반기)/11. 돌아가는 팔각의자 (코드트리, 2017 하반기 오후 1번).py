MAX = 100 + 20

CLOCKWISE = 1
COUNTER_CLOCKWISE = -1

chair = [[0] * 10 for _ in range(5)]
chair_number = [0] * MAX
directions = [0] * MAX

def input_data():             
    global chair, K, chair_number, directions
    
    for number in range(1, 5):
        value = map(int, list(input()))
        chair[number][1:9] = value

    K = int(input())
    for i in range(K):
        chair_number[i], directions[i] = map(int, input().split())
    
def rotate(number, direction):
    global chair
    
    if direction == COUNTER_CLOCKWISE:
        tmp = chair[number][1]
        for index in range(1, 8):
            chair[number][index] = chair[number][index + 1]
        chair[number][8] = tmp
    else:
        tmp = chair[number][8]
        for index in range(8, 1, -1):
            chair[number][index] = chair[number][index - 1]
        chair[number][1] = tmp
        
def simulate():
    for k in range(K):
        check = [0] * (5 + 1)
        
        target = chair_number[k]
        direction = directions[k]
        
        check[target] = direction
        
        for right in range(target, 4):
            if chair[right][3] != chair[right + 1][7]:
                check[right + 1] = check[right] * (-1)
            else:
                break
    
        for left in range(target, 1, -1):
            if chair[left][7] != chair[left - 1][3]:
                check[left - 1] = check[left] * (-1)
            else:
                break
            
        for i in range(1, 5):
            if check[i] != 0: rotate(i, check[i])
        
def get_score():
    return (chair[1][1] * 1) + (chair[2][1] * 2) \
            + (chair[3][1] * 4) + (chair[4][1] * 8)

# T = int(input())
T = 1
for _ in range(T):     
    input_data()     
    
    simulate()
    
    print(get_score())