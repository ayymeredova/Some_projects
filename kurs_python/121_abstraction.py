#122 - abstraction
class PlayerCharacter:
    def __init__(self, name, age):
        self._name = name #_name - it's a private variable, is a convention between python programmers
        self._age = age    #_age - -||-||-
    def run(self):
        print('run')

    def speak(self):
        print(f"My name is {self.name}, and I'm {self.age} years old")

player1 = PlayerCharacter("Ayjahan", 20)
##player1.name = '!!!'
##player1.speak = 'BEBEBE'

print(player1.speak())  

    
