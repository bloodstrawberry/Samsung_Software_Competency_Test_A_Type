MAX = 100 + 20

class MOVING:
    def __init__(self, index: int, people_number: int, stability: int):
        self.index = index # for debug
        self.people_number = people_number
        self.stability = stability

moving = [MOVING(0, 0, 0) for _ in range(MAX * 2)]

# position[i] = i번째 사람이 현재 있는 belt의 번호
position = [0] * (200000 + 5000) # 현재 무빙워크에 있는 사람들의 번호
live_people = [0] * MAX # 현재 무빙워크에 있는 사람들의 수
lcnt = 0

def input_data():
    global N, K, moving
    
    N, K = map(int, input().split())
    
    arr = list(map(int, input().split()))    
    for i in range(1, 2 * N + 1):
        moving[i] = MOVING(i, 0, arr[i - 1])

def print_moving():
    for i in range(1, N + 1):
        m = moving[i]
        print(f"({m.index}, {m.stability}, {m.peopleNumber})", end=' ')
    print()

    for i in range(2 * N, N, -1):
        m = moving[i]
        print(f"({m.index}, {m.stability}, {m.peopleNumber})", end=' ')
    print("")

def rotate():
    tmp = moving[2 * N]
    for i in range(2 * N, 1, -1): moving[i] = moving[i - 1]
    moving[1] = tmp

def simulate():
    global lcnt
    
    step, crush = 0, 0
    p_index = 1 # 1번 사람부터 시작
    while True:
        step += 1

        # 1-1. 무빙 워크 회전
        rotate()

        # 1-2. 무빙 워크 회전에 의한 사람 이동
        for i in range(lcnt):
            people_number = live_people[i]
            position[people_number] += 1

        # 2. 무빙 워크 내에서 사람을 이동
        next_lcnt = 0
        for i in range(lcnt):
            people_number = live_people[i]
            cur_pos = position[people_number]

            if cur_pos == N:
                position[people_number] = -1
                moving[cur_pos].people_number = 0
                continue

            next_pos = cur_pos + 1
            # 다음 칸에 사람이 있거나, 안전성이 0인 경우
            if moving[next_pos].people_number != 0 or moving[next_pos].stability == 0:
                live_people[next_lcnt] = people_number
                next_lcnt += 1
                continue

            moving[cur_pos].people_number = 0
            moving[next_pos].people_number = people_number

            moving[next_pos].stability -= 1
            if moving[next_pos].stability == 0: crush += 1

            position[people_number] = next_pos

            if next_pos == N:
                position[people_number] = -1
                moving[next_pos].people_number = 0
            else:
                live_people[next_lcnt] = people_number
                next_lcnt += 1

        # 3. 사람 추가
        if moving[1].people_number == 0 and moving[1].stability != 0:
            position[p_index] = 1
            live_people[next_lcnt] = p_index
            next_lcnt += 1
            
            moving[1].people_number = p_index
            p_index += 1

            moving[1].stability -= 1
            if moving[1].stability == 0: crush += 1

        lcnt = next_lcnt
        
        if crush >= K: return step

    return -1 # for debug

# T = int(input())
T = 1
for tc in range(T):    
    input_data()
    
    print(simulate())