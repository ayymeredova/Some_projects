#149 decorators2

#decorator

#декоратор позволяет вносить в функции различные элементы, как декоратор отдельный
#n other words decorator is able to add fuctionality



    
def my_decorator(func):
    def wrap_func():
        print('*******')
        func()
        print('*******')
    return wrap_func


##@my_decorator
def hello():
    print('helloo')
##@my_decorator
def bye():
    print(' see ya later')

hello2 = my_decorator(hello)
hello2()
