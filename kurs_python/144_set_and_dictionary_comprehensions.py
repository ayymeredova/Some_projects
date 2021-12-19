#144 Set and Dictionary comprehensions

#set

my_list = {param for param in 'hello'}
my_list2 = {num for num in range(0,100)}
my_list3 = {num*2 for num in range(0,100)}
my_list4 = {num * num for num in range(0,100) if num %2 == 0}
print(my_list3)


#dictionary
simple_dict = {
    'a':1,
    'b':2
    }


my_dict = {k:v*v for k, v in simple_dict.items() if v % 2 == 0}


##li = [1,2,3]

my_dict = {num:num * 2 for num in [1,2,3]}

print(my_dict)
