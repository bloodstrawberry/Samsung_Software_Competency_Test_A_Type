MAX = 50 + 5
MAX_DEQUE = MAX * MAX * 2
OFFSET = MAX_DEQUE // 2

deque = [0] * MAX_DEQUE * 2
front, back = OFFSET, OFFSET

N, M = map(int, input().split())
position = list(map(int, input().split()))

for i in range(1, N + 1):
    deque[back] = i
    back += 1
        
def get_left_count(value):
    ret = 0
    for i in range(front, back):
        if deque[i] == value: return ret
        
        ret += 1
    
    return -1 # error

def get_right_count(value):
    ret = 0
    for i in range(back - 1, front - 1, -1):
        ret += 1
        
        if deque[i] == value: return ret
    
    return -1 # error

answer = 0

for i in range(M):
    if deque[front] == position[i]: front += 1
    else:
        left_count = get_left_count(position[i])
        right_count = get_right_count(position[i])
        
        if left_count < right_count:
            for _ in range(left_count):
                deque[back] = deque[front]
                back += 1
                front += 1
            
            front += 1
            
            answer += left_count
        else:
            for _ in range(right_count):
                deque[front - 1] = deque[back - 1]
                front -= 1
                back -= 1
            
            front += 1
            
            answer += right_count
        
print(answer)
