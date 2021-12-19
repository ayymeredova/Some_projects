#81 return
def sum(num1, num2):
    return num1+num2

#should do one thing really well
# should return something

total = sum(10, 5)
print(sum(10, total))


def sum1(num1, num2):
    def another_func(num1, num2):
        return num1+num2
    return another_func(num1, num2)

total = sum1(10, 20)
print(total)
##print(total(10,20))


#exercise



def checkDriverAge(age = 0):
  age = input("What is your age?: ")
  if int(age) < 18:
    print("Sorry, you are too young to drive this car. Powering off")
  elif int(age) > 18:
    print("Powering On. Enjoy the ride!");
  elif int(age) == 18:
    print("Congratulations on your first year of driving. Enjoy the ride!")



def checkDriverAge(age = 0):
  if int(age) < 18:
    print("Sorry, you are too young to drive this car. Powering off")
  elif int(age) > 18:
    print("Powering On. Enjoy the ride!");
  elif int(age) == 18:
    print("Congratulations on your first year of driving. Enjoy the ride!")

checkDriverAge()
checkDriverAge()

#1. Wrap the above code in a function called checkDriverAge(). Whenever you call this function, you will get prompted for age. 
# Notice the benefit in having checkDriverAge() instead of copying and pasting the function everytime?

#2 Instead of using the input(). Now, make the checkDriverAge() function accept an argument of age, so that if you enter:
#checkDriverAge(92);
#it returns "Powering On. Enjoy the ride!"
#also make it so that the default age is set to 0 if no argument is given.
