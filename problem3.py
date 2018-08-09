import random
from time import time

def random_not_in_list(n, k):
    l = random.sample(range(0, n), k)
    while True:
        ran = random.randint(1, n-1)
        if ran not in l:
            return ran

n_val = int(input("Enter N: "))
items_num = int(input("Enter K: "))
a = time()
print(random_not_in_list(n_val, items_num))
print(f"it took {time() - a} to run")
