i = 2
s = 0

while i < 1000:
    j = 2
    while j < i:
        if i % j == 0:
            s = 1
        j = j + 1
    if s == 0:
        print i
    s = 0
    i = i + 1
