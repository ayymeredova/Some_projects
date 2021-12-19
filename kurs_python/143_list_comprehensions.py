#143_list comprehensions

#list, set, dictionary

my_list = [param for param in 'hello']
my_list2 = [num for num in range(0,100)]
my_list3 = [num*2 for num in range(0,100)]
my_list4 = [num * num for num in range(0,100) if num %2 == 0]
print(my_list4)
