from random import randint

answer = randint(1,10)




while True:
    try:
        guess = int(input("Guess a number 1~10:  "))
        if 0 < guess < 11:
            print("all good")
            break
        else:
            print("Hey bozo, I said 1 - 10")

    except ValueError:
        print("Please enter a number")


