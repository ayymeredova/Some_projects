#120 - encapsulation
class PlayerCharacter:
    def __init__(self, name, age):
        self.name = name
        self.age = age

player1 = PlayerCharacter("Ayjahan", 20)
print(player1.name)
print(player1.age)


player2 = {'name': 'Ayjahan', 'age':20}
print(player2["name"])
print(player2["age"])

    
