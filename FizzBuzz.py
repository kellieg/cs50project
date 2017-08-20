#!/usr/bin/env python3

import cs50

#Get number from user, repeat if number is not between 1-100
while True:
    print("Number(1-100):", end = "")
    num = cs50.get_int()
    if num >= 0 and num <= 100:
        break

#iterate over each number, if divisible by 3 print fizz, if divisible by 5 print buzz
#if divisible by both. print "fizzbuzz"

for num in range(1,num + 1):
    if (num % 5) == 0 and (num % 3) == 0:
        print("FizzBuzz")
    elif (num % 3) == 0: 
        print("Fizz")
    elif (num % 5) == 0: 
        print("Buzz")
#if divisible by neither, print the number    
    else:
        print(num)