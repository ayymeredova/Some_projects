#145 - EXEERCISE:Comprehensions

some_list = ['a', 'b', 'c', 'b', 'd', 'm', 'n', 'n']

duplicates = []

for value in some_list:
    if some_list.count(value) > 1:
        if value not in duplicates:
            duplicates.append(value)

print(duplicates)

#using comprehensions

duplicates = list({value for value in some_list if some_list.count(value) > 1})
print(duplicates)

