from numpy import median
from time import time

class foo(object):
    def __init__(self, val=0):
        self.val = val
        self.median_list = []

    def __add__(self, other):
        return self.val + other.val

    def add_to_list(self, val):
        self.median_list.append(val)

    def calc_median(self):
        return median(self.median_list)

print("Test add operation")
n1= int(input("first number: "))
n2 = int(input("second number: "))
print(foo(n1) + foo(n2))

a = foo()
while True:
    inst = input("C to calc, A to add, E to exit: ")
    if "C" == inst:
        after = time()
        print(a.calc_median(), "it took:", after-time())
    elif "A" == inst:
        p = input("Write a number: ")
        a.add_to_list(int(p))
    elif "E" == inst:
        exit()
