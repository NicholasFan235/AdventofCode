import os
import sys


infile = sys.argv[1]

with open(infile, 'r') as f:
    input = f.readlines()
    input = [[[int(n) for n in r.strip().split()] for r in l.split(":")[1].split('|')] for l in input]

ans = 0
for i, p in enumerate(input):
    val = 0
    for n in p[1]:
        if n in p[0]:
            val = max(1, val*2)
    ans += val
    #print(f"Card {i}: {val}")
print(ans)

