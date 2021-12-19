#=============================SET==============================
my_set = {1,2,3,4,5, 5}
my_set.add(100)
my_set.add(2)
print(my_set)

my_list = [1,2,3,4,5,5]
##new = list(set(my_list))
##print(new)
print(set(my_list))

print(1 in my_set)

print(len(my_set))


new_set = my_set.copy()
my_set.clear()
print(new_set)
print(my_set)
