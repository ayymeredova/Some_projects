#================Exercise:Password Checker========================
name  = input("Input your name: ")
password = input("Input password: ")
password_len = len(password)
hidden_password = '*' * password_len
print(f'{name}, your password {hidden_password} is {password_len} letters long')
