import sys

requiredKeys = {'byr', 'iyr', 'eyr', 'hgt', 'hcl', 'ecl', 'pid'}

def checkPassport(passport):
    passport = {p.split(':')[0].strip() for p in passport.strip().split(' ')}
    return len(requiredKeys.intersection(passport)) == len(requiredKeys)
    


ctr = 0
buffer = ''
for line in sys.stdin:
    line = line.strip()
    if len(line) == 0:
        print(buffer)
        if checkPassport(buffer):
            ctr += 1
        buffer = ''


    if len(buffer) > 0:
        buffer += ' '
    buffer += line

print(ctr)
