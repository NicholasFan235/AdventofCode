import sys
import re


M = {}
def processLine(line):
    global M
    for inner in line[1]:
        if line[0] in M:
            if inner[1] in M[line[0]]:
                M[line[0]][inner[1]] += int(inner[0])
            else:
                M[line[0]][inner[1]] = int(inner[0])
        else:
            M[line[0]] = {inner[1]:int(inner[0])}

for line in sys.stdin:
    line = [l.strip() for l in line.split('contain')]
    line[0] = line[0].split('bag')[0].strip()
    if line[1] != 'no other bags.':
        line[1] = [l.strip().split('bag')[0].strip().split(' ', 1) for l in line[1].split(',')]
    else:
        line[1] = []

    print(line)
    processLine(line)

from pprint import pprint
pprint(M)

def traverse(key):
    print(key)
    if key not in M:
        return 1
    ctr = 1
    for inner in M[key]:
        ctr += M[key][inner] * traverse(inner)
    return ctr
ans = traverse('shiny gold') - 1
print(ans)
