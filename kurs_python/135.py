#135 pure functions

#this is not pure fucntion
wizard = {
    'name': 'Merlin'
    'power': 50
    }

def attack(character):
    new_list = []
    for item in li:
        new_list.append(item*2)

    return new_list





##new_list = [] - глобальная переменная, тоже неправильно - side effects
def multiply_by2(li):
    new_list = []
    for item in li:
        new_list.append(item*2)

    return new_list   #return print(new_list) - неправильно, так как идет взаимодействие с внешними(полем вывода) данными


print(multiply_by2([1,2,3]))
