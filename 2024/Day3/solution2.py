import re


with open("input.txt", 'r') as f:
    input = [''.join(f.readlines())]

def crop_end(s):
    return s.split("do()")[0].split("don't()")[0]

# phrases = [[s.split("don't()")[0] for s in l.split("do()")] for l in input]
# phrases = [[p for p in q if p is not None and p != ""] for q in phrases]

phrases = [s.split("don't()")[0] for l in input for s in l.split("do()")]
phrases = [p for p in phrases if p is not None and p != ""]

regex = re.compile(r"mul\((\d+),(\d+)\)")

ans = 0
for p in phrases:
    for r in regex.findall(p):
        ans += int(r[0])*int(r[1])
print(ans)
