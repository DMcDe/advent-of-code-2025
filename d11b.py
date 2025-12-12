from functools import cache
import sys
from typing import Dict, Set

adj = {}

# Cache annotation does memoization for us
@cache
def partB(node: str, dac: bool, fft: bool) -> int:
    if node == "out":
        return 1 if dac and fft else 0
    
    res = 0
    for n in adj[node]:
        res += partB(n, dac or node == "dac", fft or node == "fft")
    return res

def main():
    lines = sys.stdin.read()

    for l in lines.splitlines():
        src, dsts = l.split(':')
        adj[src] = dsts.split()

    print("Part B solution (thanks Jonathan Paulson):", partB("svr", False, False))
    
if __name__ == "__main__":
    main()
    