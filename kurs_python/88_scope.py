#88_scope

#scope - what variables do i have access to?  к каким переменным у меня есть доступ?

##if True:
##    x = 10
##    
##def some_func():
##    total = 100
##
##print(x)


#SCOPE_RULES

a = 1  #global
def parent():
##    a = 10
    def confusion():
        return sum
    return confusion()

##print(a) # a = 1
##print(confusion()) # a = 5
print(parent())
print(a)

#1 - start with local
#2 - Parent local?
#3 - Global
#4 - buil in python functions



