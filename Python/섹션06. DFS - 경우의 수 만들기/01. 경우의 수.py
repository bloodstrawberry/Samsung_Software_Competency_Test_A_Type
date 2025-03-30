def print_permutations_with_repetition():
    count = 1
    for a in range(1, 5):
        for b in range(1, 5):
            for c in range(1, 5):
                print(f"{count}] {a} {b} {c}")
                count += 1

def print_combinations_with_repetition():
    count = 1
    for a in range(1, 5):
        for b in range(a, 5):
            for c in range(b, 5):
                print(f"{count}] {a} {b} {c}")
                count += 1

def print_combinations():
    count = 1
    for a in range(1, 5):
        for b in range(a + 1, 5):
            for c in range(b + 1, 5):
                print(f"{count}] {a} {b} {c}")
                count += 1

def print_permutations():
    count = 1
    visit = [False] * 5
    for a in range(1, 5):
        visit[a] = True
        for b in range(1, 5):
            if visit[b]:
                continue
            visit[b] = True
            for c in range(1, 5):
                if visit[c]:
                    continue
                print(f"{count}] {a} {b} {c}")
                count += 1
            visit[b] = False
        visit[a] = False

print_permutations_with_repetition()  # 4 Pi 3
# print_combinations_with_repetition()  # 4 H 3
# print_combinations()  # 4 C 3
# print_permutations()  # 4 P 3
