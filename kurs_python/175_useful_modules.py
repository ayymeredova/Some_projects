#175 useful modules

from collections import Counter, defaultdict, OrderedDict

li = [1,2,3,4,5,6,7, 3, 4, 5]
#выводит словарь, ключ - сами элементы списка, значения - их количество в этом списке
sentence = 'blah blah blah thinking about python'

print(Counter(li))
print(Counter(sentence))


dictionary = defaultdict(lambda:'does not exist', {'a':1, 'b':2})

print(dictionary['c'])



d = {'c':100}

d['a'] = 1
d['b'] = 2




d2 = {'c':100}

d2['b'] = 2
d2['a'] = 1

print(d2 == d)
