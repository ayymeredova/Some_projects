#115_oop_  __init__


class PlayerCharacter:
    #Class Object Attribute
    membership = True #static attribute
    def __init__(self, name = 'anonymous', age = 0):
        if(age > 18):
            self.name = name #attributes
            self.age = age
        print("constructor")


    def shout(self):
        print(f'My name is {self.name}')

    def run(self, hello):
        print(f'My name is {self.name}')
        
player1 = PlayerCharacter()
##print(player1.shout())
