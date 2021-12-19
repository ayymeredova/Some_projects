#str - string 
##print(type("hi hello there !"))

username = 'supercoder'
password = "supersecret"
long_string = '''
WOW
0 0
---
'''

##print(long_string)

first_name = "Ayjahan"
last_name = "Meredova"
full_name = first_name + " " +  last_name
##print(full_name)


#----------------------------------------------------------------
#string concatenation
##print("hello" + " Ayjahan")
#print("hello" + 5) - typeerror




#---------------------------------------------------------------
#type conversion - преобразование типов

##print(type(str(100)))  #this is string
##print(type(int(str(100))))  #this is integer

a = str(100)
b = int(a)
c = type(b)
##print(c)



#--------------------------------------------------------------
#escape sequence

weather = "It's sunny"
print(weather)
weather = "It's \"kind of \" sunny"
print(weather)

weather = "\tIt\'s \"kind of \"sunny\n hope you have a good day"
print(weather)

#---------------------------------------------------------------
#formatted string - форматирование строк
name  = 'Johnny'
age = 55
print(f'hi {name}. You are {age} years old') #фигееееть, это работает. Это все вместо 
print('Hi {}. You are {} years old.'.format(name, age))
#2variant
print('Hi {1}. You are {0} years old.'.format(name, age))

#yesho odin interesnyi variant
print('Hi {new_name}. You are {age} years old.'.format(new_name = 'Sally', age = 100)) # - to obyazatelno nujno v figurnyi skobkah ukazat sami peremennyye
new_name = 'sally'
age  =100
print(f'Hi {new_name}. You are {age} years old.')

#====================================================DZ=========================================
print("Hello {}, your balance is {}.".format("Cindy", 50))
#Hello Cindy, your balance is 50.
print("Hello {0}, your balance is {1}.".format("Cindy", 50))
#Hello Cindy, your balance is 50.
print("Hello {name}, your balance is {amount}.".format(name="Cindy", amount=50))
#Hello Cindy, your balance is 50
print("Hello {0}, your balance is {amount}.".format("Cindy", amount=50))
#Hello Cindy, your balance is 50.


# 2 How would you write this using f-string? 
name  = 'Cindy'
amount = 50
print(f'Hello {name}, your balance is {amount}.')





#==========================================STRING INDEXES===========================================
selfish = '01234567'
print(selfish[0])
#[start:stop]
print(selfish[0:2]) # -01
print(selfish[0:7]) #-0123456
print(selfish[0:8]) #01234567
#[start:stop:stepover] - начало:конец:шаг
print(selfish[0:8:2]) #0246
print(selfish[1:]) #1234567
print(selfish[:5]) #01234
print(selfish[::1]) #default 01234567
print(selfish[-1]) # 7 - nachinayem s konsa
print(selfish[::-1]) #reverse 76543210
print(selfish[::-2]) #step 2 from the end 7531

#-----------------------------------------DZ-------------------------------------------------------
python = 'I am PYHTON'

print(python[1:4])#' am'
print(python[1:])#' am PYTHON'
print(python[:])#'I am PYHTON'
print(python[1:100])##' am PYTHON'
print(python[-1])#'N'
print(python[-4])#'H'
print(python[:-3])##'I am PYH'
print(python[-3:])#'TON'
print(python[::-1])#NOTHYP ma I'
#---------------------------------------------------------------------------------------------------


#================================Immutability=================================НЕИЗМЕННОСТЬ==========================
selfish = '01234567'
#selfish[0] = '8' #ERROR! - strings are immutability - неизменность строк
selfish += '8'
#selfish = '8' - OK!
print(selfish)




