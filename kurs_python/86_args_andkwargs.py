#86_*args_and_**kwargs

def super_func(name, *args, i = 'hi', **kwargs): #any number positional arguments
##    print(kwargs)
    total = 0
    for items in kwargs.values():
        total += items
    return sum(args) + total #tuples

print(super_func('Andy', 1,2,3,4,5, num1 = 5, num2 = 10))


#Rule: params, *args, defuault parametres, **kwargs



#exercise functions


####################__MY__#######################
##def is_even(num):
##    return num % 2 == 0
##
##
##def highest_even(li):
##    number = li[0]
##    for i in range(len(li)):
##        if is_even(li[i]):
##            if li[i] > number:
##                number = li[i]
##    return number
##
##print(highest_even([10,2,3,4,8, 11]))



################__teacher's__####################
def highest_even(li):
    evens = []
    for item in li:
        if item % 2 == 0:
            evens.append(item)
    return max(evens)

print(highest_even([2,10,2,3,4,8, 11]))




            
