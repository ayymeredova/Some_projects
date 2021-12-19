#68_iterables

user = {
    "name" : "Golem",
    "age": 50,
    "can_swim":False,
    }

##for item in user.items(): #(key:value)
##    key, value = item
##    print(key, value)

for key, value in user.items():
    print(key, value)

for item in user.values():
    print(item)

for item in user.keys():
    print(item)


#iterable variables = list, tuple, string, set

    
