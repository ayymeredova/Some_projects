#====================LIST================================
li = [1,2,3,4,5]
li2 = ["a", "b", "c"]
li3 = [1, 2, "a", True]
amazon_cart = ["notebooks", "sunglasses"]
print(amazon_cart[0])

#===========================List Slicing===============================

amazon_cart = [
    "notebooks",
    "sunglasses",
    "toys",
    "grapes"
]
#print(amazon_cart[0::2])

amazon_cart[0] = "laptop"
new_cart = amazon_cart[0:3]
new_cart = amazon_cart[:]
new_cart[0] = "gym"
print(new_cart)
print(amazon_cart)

#Вывод: когда мы делаем new_cart = amazon_cart, то эти два листа будут указывать
#на одну память, и если будут изменения в одном, то эти изменения произойдут и в другом листе.
#Поэтому для создании копии листа, мы используем slicing: new_cart = amazon_cart[:].
#Таким образом, в новом листе будет копия, и они не будут связаны.


