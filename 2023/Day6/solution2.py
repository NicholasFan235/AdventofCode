import math



time = 48938595
record = 296192812361391

# time = 71530
# record = 940200


disc = math.sqrt(time*time - 4*record)
print(disc)

lower = math.floor((time-disc)/2.0)+1
upper = math.ceil((time+disc)/2.0)-1
print(lower, upper)

print(upper-lower)
