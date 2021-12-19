#============================DICTIONARY METHODS==================================
user = {
    "basket":[1,2,3],
    "greet":"hello",
    "age":20
    }
print(user.get("age", 55)) # .get() dlya polucheniya znacheniya bez oshibok
#"age" 55 - default


user2 = dict(name = "JOJO")
print(user2)

print('\n\n\n\n')
print("2PART\n")
#===================================2part=====================================
user3 = {
    "basket": [1,2,3],
    "greet":"hello",
    "age":20
}

##print("size" in user)

#method .keys() - ishet sredi klyuchey

print("age" in user3.keys())

#method .values() = ishet sredi znacheniy

print("hello" in user3.values())


#method .items() - возвращает список кортежей с ключами и их значениями

print(user3.items())


#method .copy() - kopiruyet(bez ssylok)
user4 = user3.copy()
##print(user3.clear()) #empty!
print(user4) #not empty!


#method .pop() - removes with key and get value
print(user3.pop("age"))
print(user3)


#method .popitem() - removes item although
print(user3.popitem()) #be careful! dictionary is not ordered, so it can remove any item
print(user3)


#method .update() - obnovit

print(user3.update({"age":50}))
print(user3)
print(user3.update({"ages":44}))
print(user3)

#method .clear() - очищает словарь

user3.clear()
print(user3)

