#=============================Built-In Functions + Methods============Встроенные Функции + Методы=================
#length of string
greet = 'helloooo'
print(len(greet))
print(greet[0:len(greet)])
#some methods
quote = "to be or not to be"
print(quote.upper())  #vse bykvy zaglavnyye
print(quote.lower())#vse bukvy strochnyye
print(quote.capitalize()) #pervaya bukva zaglavnaya
print(quote.find("be")) #pokazyvayet index pervogo vhojdeniya sleva
print(quote.replace("be", "me")) #zamenyayet be na me (vse vhojdeniya)
#vse eti metody ne byli sohraneni, tak kak they are not changable(immutable)
quote2 = quote.replace("be", "me")
print()
print()
print(quote2)
print(quote)

