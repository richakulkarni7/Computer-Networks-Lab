import random

def gcd(a, b):
	while True:
		temp = a%b
		if temp==0:
			return b
		a = b
		b = temp

print("Enter two different prime numbers: ")
p, q = raw_input().split()
p = int(p)
q = int(q)

n = p*q
phi = (p-1)*(q-1)
e = random.choice(range(2, phi))
while gcd(e, phi)!=1:
	e = random.choice(range(2, phi))
print("Public key: ("+str(e)+", "+str(n)+")")	
k = 0
while True:
	temp = (k*phi + 1)
	if(temp%e==0):
		d = int(temp/e)
		break
	k+=1	
print("Private key: ("+str(d)+", "+str(n)+")")
msg = int(input("Enter number to be encrypted: "))
ciphered = pow(msg, e)%n
print("Encrypted text: "+str(ciphered))
deciphered = pow(ciphered, d)%n
print("Decrypted text: "+str(deciphered))
print
