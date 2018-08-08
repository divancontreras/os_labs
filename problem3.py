import random

def random_not_in_list():
    n_val = int(input("Enter N: "))
    items_num = int(input("Enter K: "))
    l = random.sample(range(0,n_val), items_num)
    while True:
        ran = random.randint(1,n_val-1)
        if ran not in l:
            return ran

print(random_not_in_list())
