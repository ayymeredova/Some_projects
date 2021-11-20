

# Написать метод/функцию, который/которая на вход принимает массив городов. 
# В качестве результата возвращает строку, где города разделены запятыми, а в конце стоит точка. 



def cities (array):
    res = ','.join(array)
    res += '.'
    return res        

# cities_array = ["Москва", "Санкт-Петербург", "Воронеж"]
# print(cities(cities_array))



def number_round(number):
    if round(number) - int(number):
        pass




def right_word(number):
    ost = number % 10
    if  ost % 10 >= 5:
        return(f'{number} компьютеров')
    else:
        return(f'{number} компьютер')



# print(right_word(1048)) 


def ordinary_num(num):
    k = 0
    for i in range(2, num+1):
        if(num % i == 0):
            k+=1

    if k > 1:
        print('Not ordinary number.')
            
    else:
        print('Ordinary number.')
            
# ordinary_num(22)


def two_lists(lst1, lst2):
    res = []
    for i in range(len(lst1)):
        for j in range(len(lst2)):
            if lst1[i] == lst2[j] and lst2[j] not in res:
                res.append(lst2[j])
    return res

a1 = [1,2,3,4,5]

a2 = [1,2,3,4,5]
print(two_lists(a1, a2))


