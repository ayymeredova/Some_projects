#SHORT CIRCUITING

is_Friend = True
is_User = True
##print(is_Friend and is_User)

if is_Friend or is_User:
    print('best friend forever')
#Смысл басни такова:
    #короткое замыкание - когда в логических операциях в некоторых условиях вторая часть
    #не рассматривается интерпретатором.
    #e.g. if true or false - в этом случае интерпретатор посмторит на первую часть
    #увидит, что условие истинно и следовательно для лог. операции или важно, чтобы
    #хотя бы одно условие было истинным. Следовательно остальная чатсь условия рассматриваться не будет
    #e.g. if false and true - здесь та же ситуация.

#Вывод басни такова:
    #Если хотите, чтобы все условия были рассмотрены до конца, то нужно учитывать эти моменты.



############################################################################################################################################################

#logical operators.

# > < >= <= != == and or not

print(not(True))
print(not(1 == 1))



################################
#exercises

is_magician = False
is_expert= True

#check if magician and expert: " you are a master magician

#check if magician but not expert: "at least you're getting there"

#check if you're not a magician: "you need  magic powers"

if is_magician and is_expert:
    print("you're a master magician")

elif is_magician and not is_expert:
    print("at least you're getting there")

elif not is_magician:
    print("you need magic powers")
