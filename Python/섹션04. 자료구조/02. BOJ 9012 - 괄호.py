T = int(input())

for _ in range(T):
    str = input()
    flag = False
    sp = 0
    
    for ch in str:
        if ch == '(': sp += 1
        else: sp -= 1
        
        if sp < 0: 
            flag = True
            break
        
    if flag == True or sp != 0: print("NO")
    else : print("YES")