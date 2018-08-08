from time import time

def first_non_repeating(word):
    letter_dict = {}
    letter_list = []
    for letter in word:
        if letter in letter_dict:
            letter_dict[letter] = False
        else:
            letter_dict[letter] = True
            letter_list.append(letter)
    for letter in letter_list:
        if letter_dict[letter]:
            return letter
    return None

word = input()
after = time()
word = first_non_repeating(word)
print (f"It was {word} and it took {time()-after}")
