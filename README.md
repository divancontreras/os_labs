# OS Lab #1

##Set of problems of laboratory #1 for OS class.

### Requirements
To build you requiere to have python 3.5+ installed, along with numpy.

### Run

Just call with the prefix "python" the file to be executed.

### Problem 1

In this problem I'm using a dictionary which is equivalent to a hashmap, both represent a space complexity of O(n), on my algorithm I iterate on my word, and IF the current letter happen to already be a key on my dict, I will SET that key to false, since it is repeated. ELSE, I will set that key to True, and append that letter to a list. When I'm done iterating my word, I will iterate my list, checking in order of ocurrance if that letter is repeated, when I find the first True in my map, I'll return that value.

Since I'm iterating my word and a list with the same length that would be O(2n), all the other instructions like setting or getting the map are O(1) in an average case, so we can assume a O(n) Complexity.

## Problem 2

In this problem, the overload of __add__ takes O(log(n)) to add up two numbers, that's our complexity for that one.

The median method is a builtin on numpy library and on my research it takes O(n) time, we have a simple list we add on to, so basicly thats o(1) to add to the list and o(n) of space complexity.

So overall compelxity is O(n)

## Problem 3 

In this problem we have a space complexity of just one list o(n) on which length will be given by N and the range would be given by 0 to k, randint takes O log(n) to generate a number, and we have a chance of (N - K)/N of the remaining numbers to appear, and a chance of N/K getting it at the first time, so I'm gonna assume at the best case scenario runs O(log(n)), and a very bad case scenario O(n).
