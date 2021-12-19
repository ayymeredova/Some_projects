#162_exercise: Fibonacci Numbers


def fib(number):
    a = 0
    b = 1
    for i in range(number):
        yield a
        temp = a
        a = b
        b += temp

##for x in fib(21):
##    print(x)
        
        
##    return (fib(index-1) + fib(index - 2))


def fib2(number):
    a = 0
    b = 1
    result = []
    for i in range(number):
        result.append(a)
        temp = a
        a = b
        b += temp

    return result

print(fib2(21))

    
