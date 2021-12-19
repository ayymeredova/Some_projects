#147_decorators

##def hello():
##    print('hello')
##
####hello() - error!
##greet = hello
##del hello
##greet()


def hello(func):
    func()

def greet():
    print('still here!')


a = hello(greet)

print(a)


