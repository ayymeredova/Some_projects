#116_exercise_cats_everywhere
##################################_My_solution_################################
#Given the below class:
class Cat:
    species = 'mammal'
    def __init__(self, name, age):
        self.name = name
        self.age = age


# 1 Instantiate the Cat object with 3 cats
cat1 = Cat('1', 20)
cat2 = Cat('2', 10)
cat3 = Cat('3', 30)


# 2 Create a function that finds the oldest cat
def oldest(age1, age2, age3):
  return max(age3,(max(age1, age2)))




# 3 Print out: "The oldest cat is x years old.". x will be the oldest cat age by using the function in #2

print(f'The oldest cat is {oldest(cat1.age, cat2.age, cat3.age)} years old.')


#######################################andrei's_solution###############

class Cat:
    species = 'mammal'
    def __init__(self, name, age):
        self.name = name
        self.age = age


# Instantiate the Cat object with 3 cats
peanut = Cat("Peanut", 3)
garfield = Cat("Garfield", 5)
snickers = Cat("Snickers", 1)


# Find the oldest cat
def get_oldest_cat(*args):
    return max(args)


# Output
print(f"The oldest cat is {get_oldest_cat(peanut.age, garfield.age, snickers.age)} years old.")
