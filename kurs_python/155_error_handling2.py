#155 Error Handlig2

def sum(num1, num2):
    try:
        return num1 + num2
    except TypeError as err:
        print(f'Please enter a numbers { err}')


print(sum('1', 2))

    
