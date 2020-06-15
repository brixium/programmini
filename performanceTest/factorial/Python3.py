#! /usr/bin/env python3
import datetime
import math

def main():
    val = 19
    beginning = datetime.datetime.now()
    print (math.factorial(val))
    end = datetime.datetime.now()
    time_elapsed = end - beginning
    print("Time elapsed: ", time_elapsed.microseconds / 1000)

def recursive_factorial(n):
    if (n == 0):
        return 1
    return n * recursive_factorial(n-1)

if __name__ == "__main__":
    main()

