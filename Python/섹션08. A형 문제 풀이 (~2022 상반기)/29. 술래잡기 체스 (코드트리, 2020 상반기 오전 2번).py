import copy

MAX = 4 + 2
MAX_H = 16 + 5 # 도둑말의 수

MAP = [[0] * MAX for _ in range(MAX)]

class CHESS:
    def __init__(self, r: int, c: int, dir: int, dead: bool):
        self.r = r
        self.c = c
        self.dir = dir
        self.dead = False

chess = [CHESS(0, 0, 0, False) for _ in range(MAX_H)]
tagger = CHESS(0, 0, 0, False)

# -, ↑, ↖, ←, ↙, ↓, ↘, →, ↗
dr = [0, -1, -1, 0, 1, 1, 1, 0, -1]
dc = [0, 0, -1, -1, -1, 0, 1, 1, 1]

def input_data():
    for r in range(4):
        line = list(map(int, input().split()))
        for c in range(4):
            index = line[c * 2]
            dir = line[c * 2 + 1]
                        
            MAP[r][c] = index
            
            chess[index].r = r
            chess[index].c = c
            chess[index].dir = dir
            chess[index].dead = False

def print_status(tagger, map_, chess, score): # for debug
    print(f"score : {score}")
    print(f"tagger : r {tagger.r}, c {tagger.c}, dir {tagger.dir}")

    print("live chess : ", end='')
    for i in range(1, 17):
        if not chess[i].dead:
            print(f"{i}, ", end='')
    print("")

    for r in range(4):
        for c in range(4):
            if r == tagger.r and c == tagger.c:
                print(f"({-1}, {tagger.dir})", end=' ')
            else:
                piece_num = map_[r][c]
                print(f"({piece_num}, {chess[piece_num].dir})", end=' ')
        print("")
    print("")

def DFS(prev_tagger, prev_map, prev_chess, score):
    global max_answer

    pt = copy.deepcopy(prev_tagger)
    tmp_map = copy.deepcopy(prev_map)
    tmp_chess = copy.deepcopy(prev_chess)

    dead_index = tmp_map[pt.r][pt.c]
    
    # 이미 잡힌 도둑말인 경우
    if tmp_chess[dead_index].dead == True: return

    # 술래 방향 변경
    pt.dir = tmp_chess[dead_index].dir
    
    # 도둑말 사망 처리
    tmp_chess[dead_index].dead = True
    
    # 점수 누적
    score += dead_index

    # 도둑말 이동
    for i in range(1, 17):
        horse = copy.deepcopy(tmp_chess[i])
        
        if horse.dead == True: continue

        while True:
            dir = horse.dir
            nr = horse.r + dr[dir]
            nc = horse.c + dc[dir]

            if (nr == pt.r and nc == pt.c) or \
                (nr < 0 or nc < 0 or nr > 3 or nc > 3):
                #    -, ↑, ↖, ←, ↙, ↓, ↘, →, ↗
				# => -, ↖, ←, ↙, ↓, ↘, →, ↗, ↑
                change_dir = [0, 2, 3, 4, 5, 6, 7, 8, 1]
                next_dir = change_dir[dir]
                
                horse.dir = next_dir
                tmp_chess[i].dir = next_dir                
                
                continue
            else:
                change_index = tmp_map[nr][nc]
                
                # 좌표만 변경
                tmp_chess[i].r, tmp_chess[change_index].r = tmp_chess[change_index].r, tmp_chess[i].r
                tmp_chess[i].c, tmp_chess[change_index].c = tmp_chess[change_index].c, tmp_chess[i].c
                              
                # MAP에서 index 변경
                tmp_map[nr][nc], tmp_map[horse.r][horse.c] = tmp_map[horse.r][horse.c], tmp_map[nr][nc]
                
                break

    # 술래 1 ~ 3칸 이동
    sr, sc = pt.r, pt.c    
    for i in range(1, 4):
        nr = sr + dr[pt.dir] * i
        nc = sc + dc[pt.dir] * i

        if nr < 0 or nc < 0 or nr > 3 or nc > 3:
            if max_answer < score: max_answer = score

            break

        pt.r, pt.c = nr, nc
        
        DFS(pt, tmp_map, tmp_chess, score)
        
# T = int(input())
T = 1
for tc in range(T): 
    global max_answer
    
    input_data()
    
    max_answer = 0
    
    tagger.r, tagger.c = 0, 0
    
    DFS(tagger, MAP, chess, 0)
    
    print(max_answer)