import re
import sys


def isMatch(min, max, char, password):
    cnt = password.count(char[0])
    return cnt <= max and cnt >= min

ctr = 0
for line in sys.stdin:
    if len(line) == 0:
        break
    line = [l.strip() for l in line.split(':')]
    password = line[1]
    line = line[0].split(' ')
    char = line[1].strip()
    ranges = [int(l.strip()) for l in line[0].split('-')]
    
    if isMatch(ranges[0], ranges[1], char, password):
        ctr += 1
print(ctr)