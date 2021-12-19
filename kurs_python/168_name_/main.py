#main.py
##from utility import multiply,divide
##
##from shopping.more_shopping import shopping_cart
##
##
##if __name__ == '__main__':
##    print(shopping_cart.buy('apple'))
##    print(divide(5,2))
##    print(multiply(5,2))
##    print(max([1,2,3]))
##


#169_built in functions


import random
##from random import shuffle
##print(random)
##help(random)
##
##print(dir(random))



##print(random.randint(1,10))

print(random.choice([1,2,3,4,5]))

my_list = [1,2,3,4,5]

random.shuffle(my_list)
print(my_list)
