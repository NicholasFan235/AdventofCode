
import sys

data = []

ctr = 0
for line in sys.stdin:
    if len(line) == 0:
        break
    line = [c=='1' for c in line.strip()]
    data.append(line)

d = [[i for i in r] for r in data]
ox = 0
i = 0

while (i < len(data[0]) and len(d) > 1):
    ones = list(filter(lambda t: t[i]==True, d))
    zeros = list(filter(lambda t: t[i]==False, d))

    i+=1
    if (len(ones) >= len(zeros)):
        ox += 1
        d = ones
    elif (len(ones) < len(zeros)):
        d = zeros
    ox *= 2
while (i < len(data[0])):
    if (d[0][i]):
        ox += 1
    ox *= 2
    i += 1
ox //= 2

d = [[i for i in r] for r in data]
co2 = 0
i = 0
while (i < len(data[0]) and len(d) > 1):
    ones = list(filter(lambda t: t[i]==True, d))
    zeros = list(filter(lambda t: t[i]==False, d))
    i += 1
    if (len(ones) >= len(zeros)):
        d = zeros
    elif (len(ones) < len(zeros)):
        d = ones
        co2 += 1
    co2 *= 2
while (i < len(data[0])):
    if (d[0][i]):
        co2 += 1
    co2 *= 2
    i += 1
co2 //= 2

print(f'ox: {ox}, co2: {co2}')
print(ox*co2)

