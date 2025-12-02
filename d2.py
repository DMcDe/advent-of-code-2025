from typing import List
def partA(id_ranges: List[tuple]):
    res = 0
    for rng in id_ranges:
        # If all numbers in a range are odd number of digits, can't be two duplicate strings
        if len(rng[0]) == len(rng[1]) and len(rng[0]) % 2:
            continue
        
        for i in range(int(rng[0]), int(rng[1]) + 1):
            s = str(i)
            l = len(s)
            if s[:l//2] == s[l//2:]:
                res += i
    return res

def partB(id_ranges: List[tuple]):
    res = 0
    for rng in id_ranges:
        for i in range(int(rng[0]), int(rng[1]) + 1):
            s = str(i)
            l = len(s)

            for length in range(1, (l // 2) + 1):
                # This substring doesn't evenly divide the string we're looking at
                if l % length:
                    continue

                num_substrs = l // length
                substr = s[:length]
                invalid = True
                for i_substr in range(1, num_substrs):
                    if s[i_substr * length : (i_substr + 1) * length] != substr:
                        invalid = False
                        break
                
                if invalid:
                    res += i
                    # Break here so we don't double count a number like 9999
                    break
    
    return res
                
def main():
    id_ranges = []
    with open("d2.in", 'r') as f:
        text = f.read()
        ranges = text.split(',')
        for rng in ranges:
            nums = rng.split('-')
            id_ranges.append((nums[0], nums[1]))

    print("Part A solution:", partA(id_ranges=id_ranges))

    print("Part B solution:", partB(id_ranges=id_ranges))


if __name__ == "__main__":
    main()

