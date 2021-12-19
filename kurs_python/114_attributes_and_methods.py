#oop attributes and methods



class PlayerCharacter:
    #Class Object Attribute
    membership = True #static attribute
    def __init__(self, name, age):
        if(self.membership):
            self.name = name #attributes
            self.age = age


    def shout(self):
        print(f'My name is {self.name}')

    def run(self, hello):
        print(f'My name is {self.name}')
player1 = PlayerCharacter("Cindy", 44)
player2 = PlayerCharacter("Tom", 21)
player2.attack = 50

print(player1.run('hello'))
print(player2.shout())
