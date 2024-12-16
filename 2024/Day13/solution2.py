import re
import numpy as np
import math


regex = re.compile("Button A: X\\+(\\d+), Y\\+(\\d+)Button B: X\\+(\\d+), Y\\+(\\d+)Prize: X=(\\d+), Y=(\\d+)")
offset = 10000000000000

with open('input.txt', 'r') as f:
    input = [l.strip() for l in f.readlines() if len(l.strip()) > 0]

machines = [regex.match(l1.strip()+l2.strip()+l3.strip()) for l1,l2,l3 in zip(input[::3],input[1::3],input[2::3])]
machines = [(np.array([[int(m[1]), int(m[3])], [int(m[2]),int( m[4])]], dtype=int), np.array([int(m[5])+10000000000000, int(m[6])+10000000000000], dtype=int)) for m in machines]

def inv(m):
    return np.array([[m[1,1], -m[0,1]], [-m[1,0], m[0,0]]])
def calc_det(m):
    return m[0,0]*m[1,1]-m[0,1]*m[1,0]

ans = 0

for m in machines:
    det = calc_det(m[0])
    nDet = inv(m[0])@m[1]

    assert det != 0
    if (det < 0):
        det *= -1
        nDet *= -1
    
    gcd = np.gcd(nDet, det)

    if np.all(gcd>=det):
        nA = nDet[0]//det
        nB = nDet[1]//det

        score = 3*nA+nB
        ans += score

print(ans)

