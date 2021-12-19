#======================COMMON LIST PATTERNS===================================
basket = ["a", "x", "b", "c", "d", "e", "d"]
basket.sort()
basket.reverse()
#slicing
##print(basket[::-1]) #-sozdayot nobyi, staryi ne menyayet
##print(basket)



#range
##print(list(range(1, 100)))
##print(list(range(101)))




#join

new_sentence = " ".join(["HI", "my",  "name" , "is",  "JOJO"])
print(new_sentence)


#============================dz===========================================
#fix this code so that it prints a sorted list of all of our friends (alphabetical). Scroll to see answer
friends = ['Simon', 'Patty', 'Joy', 'Carrie', 'Amira', 'Chu']

new_friend = ['zuzu']

#print(friends.sort() + new_friend) - tak kak .sort() nichego ne vozvrashayet
print(sorted(friends) + new_friend)

# Solution: (keep in mind there are multiple ways to do this, so your answer may vary. As long as it works that's all that matters!)
# friends.extend(new_friend)
# print(sorted(friends))



#========================LIST UNPACKING=======================================
basket = [1, 2, 3]
a,b, c = [1, 2, 3] #a = 1, b = 2, c = 3
a, b, c, *other, d = [1, 2, 3, 4, 5, 6, 7, 8,9] #kruto!!!!!!
print(a)
print(b)
print(c)
print(other)
print(d)


      
