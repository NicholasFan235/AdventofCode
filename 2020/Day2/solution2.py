import re
import sys


def isMatch(min, max, char, password):

    match1 = len(password) >= min and password[min-1] == char[0]
    match2 = len(password) >= max and password[max-1] == char[0]
    return match1 ^ match2

ctr = 0
bad = 0
for line in sys.stdin:
    if len(line) == 0:
        break
    line = [l.strip() for l in line.split(':')]
    password = line[1]
    line = line[0].split(' ')
    char = line[1].strip()
    ranges = [int(l.strip()) for l in line[0].strip().split('-')]
    
    if isMatch(ranges[0], ranges[1], char, password):
        ctr += 1
    else:
        bad += 1
print('{}/{}'.format(ctr, bad + ctr))