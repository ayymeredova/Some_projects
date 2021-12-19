# 179_debugging

#linting
#ide/editor
#read errors

#pdb

import pdb

def add(num1, num2):
    pdb.set_trace()
    t = 4*5
    return num1+ num2

add(4, 5)
