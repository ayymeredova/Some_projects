#136 - map()

#map, filter, zip and reduce


my_list = [1,2,3]
def multiply_by2(item):

    return item*2   

print(list(map(multiply_by2, my_list)))
print(my_list)

#map - don't change base list, so there are no side effects

##print(multiply_by2([1,2,3]))
