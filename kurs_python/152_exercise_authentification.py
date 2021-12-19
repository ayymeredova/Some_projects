#152_exercise: @authenticated

############_My_####################################
# Create an @authenticated decorator that only allows the function to run is user1 has 'valid' set to True:
user1 = {
    'name': 'Sorna',
    'valid': False #changing this will either run or not run the message_friends function.
}

def authenticated(fn):
  def wrapper(user):
    if(user['valid']):
      fn(user)
    else:
      print('valid is not true')
    return
  return wrapper

  # code here

@authenticated
def message_friends(user):
    print('message has been sent')

message_friends(user1)



###############_Techer's_###############################
# Create an @authenticated decorator that only allows the function to run is user1 has 'valid' set to True:
user1 = {
    'name': 'Sorna',
    'valid': True
}

def authenticated(fn):
  def wrapper(*args, **kwargs):
    if args[0]['valid']:
        return fn(*args, **kwargs)
  return wrapper

@authenticated
def message_friends(user):
    print('message has been sent')

message_friends(user1)
