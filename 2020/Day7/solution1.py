import sys
import re


M = {}
def processLine(line):
    global M
    for inner in line[1]:
        if inner in M:
            M[inner].add(line[0])
        else:
            M[inner] = {line[0]}

for line in sys.stdin:
    line = [l.strip() for l in line.split('contain')]
    line[0] = line[0].split('bag')[0].strip()
    if line[1] != 'no other bags.':
        line[1] = [' '.join(l.strip().split('bag')[0].strip().split(' ')[1:]) for l in line[1].split(',')]
    else:
        line[1] = []

    processLine(line)

from pprint import pprint
pprint(M)

goodBags = set()
def traverse(key):
    if key not in M:
        return
    for l in M[key]:
        traverse(l)
        goodBags.add(l)
traverse('shiny gold')
print(goodBags)
print(len(goodBags))