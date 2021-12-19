#78_functions



#DRY - do not repeat yourself

def say_hello():
    print("hellooo")
    
say_hello()


#79_arguments_parametres
#parametres

def say_hello(name, emoji):
    print(f"hellooo {name}{emoji}")

#arguments
say_hello("Ayjahan", ";)")  #call, invoke the function
say_hello("Zubeyda", ";)")
say_hello("Kurbanchik", ";)")





#80_default _parametres and keyword arguments

#parametres
#default parametres
def say_hello(name = "Darth Vader", emoji = ")))"):
    print(f"hellooo {name}{emoji}")

#positional arguments
say_hello("Ayjahan", ";)")  #call, invoke the function
say_hello("Zubeyda", ";)")
say_hello("Kurbanchik", ";)")

#keyword arguments
say_hello(emoji = ":)", name = "Bibi")
#default
say_hello()
say_hello("Timmy")


