###129 Dunder methods (magic methods)
##
##
##class User(object):
##    def __init__(self, email):
##        self.email = email
##        
##    def sign_in(self):
##        print('logged in')
##
####    def attack(self):
####        print('do nothing')
##
##
##class Wizard(User):
##    def __init__(self, name, power,email):
####        User.__init__(self, email)
##        super().__init__(email)
##        self.name = name
##        self.power = power
##        
##
##    def attack(self):
##
##        print(f'Attacking with power of {self.power}')
##
##
##class Archer(User):
##    def __init__(self, name, num_arrows):
##        self.name = name
##        self.num_arrows = num_arrows
##
##    def attack(self):
##        print(f'Attacking with arrows: arrows left - {self.num_arrows}')
##
##
##
##wizard1 = Wizard('Merlin', 50, 'merlin@gmail.com')
##print(dir(wizard1))
###dir - give us all methods of wizard

class Toy():
    def __init__(self, color, age):
        self.color = color
        self.age = age
        self.my_dict = {
            'name': 'Yoyo',
            'has_pets': False
            }

    def __str__(self):
        return f'{self.color}'

    def __len__(self):
        return 5

    def __call__(self):
        return 'yesss?'

    def __getitem__(self, i):
        return self.my_dict[i]
    
action_figure = Toy('red', 0)
print(action_figure.__str__())
print(str(action_figure))
print(str('action_figure'))
print(len(action_figure))

print(action_figure())
print(action_figure['name']) 
