#148_higher order functions HOF

def greet(func):
    func()


def greet2():
    def func():
        return 5

    return func
greet2()
print(greet2())

#HOF - фукнции, которые возвращают другие новые функции или принимают в качестве параметров и вызывают их


