MAX = 1000000 + 50000

restaurant = [0] * MAX

def input_data():
    global N, leader, member
    
    N = int(input())
    restaurant[0:N] = map(int, input().split())
    leader, member = map(int, input().split())

# T = int(input())
T = 1
for tc in range(T):
    input_data()
    
    sum = 0
    for i in range(N): restaurant[i] -= leader
    
    sum += N
    
    for i in range(N):
        if restaurant[i] > 0: 
            sum += ((restaurant[i] - 1) // member) + 1
    
    print(sum)