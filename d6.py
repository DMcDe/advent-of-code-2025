from typing import List
def partA(arrs: List[List]) -> int:
    m = len(arrs)
    n = len(arrs[0])
    res = 0
    for j in range(n):
        op = arrs[m - 1][j]
        answer = 1 if op == '*' else 0
        for i in range(m - 1):
            if op == '*':
                answer *= arrs[i][j]
            else:
                answer += arrs[i][j]

        res += answer

    return res

def partB(arrs: List[str]) -> int:
    m = len(arrs)
    n = len(arrs[0])
    ops = arrs[m - 1]
    res = 0

    answer = 0
    op = ' '
    for j in range(n):
        if ops[j] != ' ':
            res += answer
            # print(f"Adding {answer} to res {res}")
            op = ops[j]
            answer = 1 if op == '*' else 0
        
        num = 0
        for i in range(m - 1):
            if arrs[i][j] != ' ':
                num *= 10
                try:
                    num += int(arrs[i][j])
                except:
                    res += answer
                    # print(f"Adding {answer} to res {res} IN EXCEPTION (final column)")
                    return res

        if num > 0:
            if op == '*':
                # print(f"Multiplying {num} with {answer}")
                answer *= num
            else:
                # print(f"Adding {num} to {answer}")
                answer += num

    res += answer
    # print(f"Adding {answer} to res {res}")

    return res

def main():
    filename = input("Enter the input file name: ")

    arrs = []
    strs = []
    with open(filename, 'r') as fd:
        for line in fd:
            strs.append(line)

            try:
                arrs.append([int(str) for str in line.split()])
            except ValueError:
                arrs.append(line.split())
    strs[len(strs) - 1] += ' '

    print("Part A solution:", partA(arrs))

    print("Part B solution:", partB(strs))


if __name__ == "__main__":
    main()