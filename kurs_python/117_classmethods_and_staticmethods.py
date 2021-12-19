#117_@classmethod and @staticmethod

#oop

class PlayerCharacter:
    membership = True
    def __init__(self, name, age):
        self.name = name
        self.age= age
    def shout(self):
        print(f'My name is {self.name}')


    @classmethod
    def adding_things(cls, num1, num2):
        return cls('Teddy',num1+num2)
    @staticmethod
    def adding_things(num1, num2):
        return num1+num2
    
##player1 = PlayerChatacter('Tom', 20)

player3 = PlayerCharacter.adding_things(2,3)
print(player3.age)
