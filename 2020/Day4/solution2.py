import sys
import re

requiredKeys = {'byr', 'iyr', 'eyr', 'hgt', 'hcl', 'ecl', 'pid'}

def checkByr(byr):
    if not byr.isnumeric():
        return False
    byr = int(byr)
    return byr >= 1920 and byr <= 2002

def checkIyr(iyr):
    if not iyr.isnumeric():
        return False
    iyr = int(iyr)
    return iyr >= 2010 and iyr <= 2020

def checkEyr(iyr):
    if not iyr.isnumeric():
        return False
    iyr = int(iyr)
    return iyr >= 2020 and iyr <= 2030

def checkHgt(hgt):
    if hgt[-2:] == 'in':
        if not hgt[:-2].isnumeric():
            return False
        hgt = int(hgt[:-2])
        return hgt >= 59 and hgt <= 76
    elif hgt[-2:] == 'cm':
        if not hgt[:-2].isnumeric():
            return False
        hgt = int(hgt[:-2])
        return hgt >= 150 and hgt <= 193
    else:
        return False

def checkHcl(hcl):
    return re.fullmatch('^#[a-zA-Z0-9]{6}$', hcl) is not None

def checkEcl(ecl):
    return ecl in {'amb', 'blu', 'brn', 'gry', 'grn', 'hzl', 'oth'}

def checkPid(pid):
    return re.fullmatch('^[0-9]{9}$', pid) is not None

def checkPassport(passport):
    passport = dict(p.split(':') for p in passport.split(' '))
    if len(requiredKeys.intersection(passport.keys())) != len(requiredKeys):
        return False
    return checkByr(passport['byr']) and checkIyr(passport['iyr']) and checkEyr(passport['eyr']) and \
        checkHgt(passport['hgt']) and checkHcl(passport['hcl']) and \
        checkEcl(passport['ecl']) and checkPid(passport['pid'])


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
