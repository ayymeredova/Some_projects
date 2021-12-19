#_77_find_dublicates_exercise

some_list = ['a', 'b', 'c', 'b', 'd', 'm', 'n', 'n']
count = 1
##for i in range(len(some_list)):
##    j= i+1
##    for j in range(len(some_list)-1):
##        if some_list[j] == some_list[i]:
##            print(some_list[j])
##    
    
dublicates = []
for value in some_list:
    if some_list.count(value) > 1:
        if value not in dublicates:
            dublicates.append(value)

##print(list(set(dublicates)))
print(dublicates)

