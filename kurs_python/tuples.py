#==================================TUPLES======================================
my_tuple = (1,2,3,4,5)
print(my_tuple[1])
print(5 in my_tuple)
##my_tuple[0] = 6 - ERROR!
##print(my_tuple)

#КАК МЫ ЗНАЕМ, КЛЮЧИ В СЛОВАРЯХ НЕИЗМЕНЯЕМЫ, СЛЕДОВАТЕЛЬНО МЫ МОЖЕМ ИСПОЛЬЗОВАТЬ КОРТЕЖИ

user = {
    (1,2):[1,2,3],
    "greet":"hello",
    "age":20
    }
print(user[(1,2)])#-it's works!



#================================2part======================
print("\n\n\n\n")
print("2part\n")

my_tuple = (1,2,3,4,5,5)
new_tuple = my_tuple[1:4]
print(new_tuple)


x,y,z, *other = (1,2,3,4,5)
print(x)
print(y)
print(z)
print(other)

#method .count()

print(my_tuple.count(5))



#method .index()
print(my_tuple.index(5))

#method len()

print(len(my_tuple))
