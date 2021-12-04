import sys

data = []
for line in sys.stdin:
    data.append(int(line))

print(sum(data))
print(min(data))
print(max(data))