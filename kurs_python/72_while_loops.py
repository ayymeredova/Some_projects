#72_while_loops
#while condition:
    #do smth

##i = 0
##while i<50:
##    print(i)

my_list = [1,2,3]
for i in my_list:
    print(i)

i = 0
while i < len(my_list):
    print(my_list[i])
    i+=1

while True:
    response = input("say something: ")
    if response == "bye":
        break
