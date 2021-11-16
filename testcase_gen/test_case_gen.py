import random

def gen_random_items(n, m):
    weights = []
    profits = []
    sum = 0
    for i in range(0, n):
        w = random.randrange(0, m)
        p = random.randrange(0, 1000)
        sum += w
        weights.append(w)
        profits.append(p)

    print("N : " + str(n))
    print("M :" + str(m))
    print("Sum : " + str(sum))

    return zip(weights, profits)

for i in range(0, 10):
    n = random.randrange(10, 1000)
    m = random.randrange(10, 1000)
    items = gen_random_items(n, m)
    f = open("./testcases/test_" + str(i + 1) + ".txt", "w")
    for each in items:
        #f.write(str(each) + ",")
        f.write(str(each[0]))
        f.write(',')
        f.write(str(each[1]))
        f.write('\n')
    f.close()