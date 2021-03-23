def primefactor(number):
    if number == 1:
        return ["1 is neither prime nor composite"]
    elif number < 1:
        return ["please use positive non zero integers"]
    l = []
    prime = 2
    while number > 1:
        while (number % prime != 0):
            prime += 1
        print(number, prime)
        number = number // prime
        print (number, prime)
        l.append(prime)
    if len(l) == 1:
        return [f"{l[0]} is a prime number"]
    else:
        return l
if __name__ == '__main__':
    a = primefactor(78645245)
    print("prime factors =", a)
    print("highest prime factor =", a[-1])