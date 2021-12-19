#157 Error Handlig 3

while(True):
    try:
        age = int(input("What is your age? "))
        10/age
        raise Exception('Hey cut it out')
    except ValueError:
        print("Please enter a number")
        continue

    except ZeroDivisionError:
        print("Please enter age higher than 0")
        break

    else:
        print('Thank you')
        

    finally:
        print('ok, i am finally done')

    print("Can you hear me?")

    
