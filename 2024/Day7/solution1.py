

class Problem:
    def __init__(self, s):
        s = s.strip().split(': ')
        self.ans = int(s[0])
        self.inputs = [int(i) for i in s[1].strip().split(' ')]

    def __repr__(self):
        return f"Problem({self.ans} = {self.inputs})"

with open('input.txt', 'r') as f:
    problems = [Problem(p) for p in f.readlines()]


def search(p:Problem, pos:int=0, current:int=0):
    if (pos <= 0): return search(p, pos+1, p.inputs[0])
    if (pos >= len(p.inputs)): return p.ans == current
    return search(p, pos+1, current+p.inputs[pos]) or search(p, pos+1, current*p.inputs[pos])

ans = 0
for p in problems:
    if search(p):
        ans += p.ans
print(ans)
