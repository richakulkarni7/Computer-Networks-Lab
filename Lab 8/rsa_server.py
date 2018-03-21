import socket   
import random
def gcd(a, b):
	while True:
		temp = a%b
		if temp==0:
			return b
		a = b
		b = temp          
s = socket.socket()      
host = socket.gethostname()
port = input("Enter port number: ")               
s.connect((host, port))
print("\nEnter two prime numbers: " )
p, q = raw_input().split()
p = int(p)
q = int(q)
n = p*q
phi = (p-1)*(q-1)
e = random.choice(range(2, phi))
while gcd(e, phi)!=1:
	e = random.choice(range(2, phi))
print 'Public key: ('+str(e)+', '+str(n)+')'	
k = 0
while True:
	temp = (k*phi + 1)
	if(temp%e==0):
		d = int(temp/e)
		break
	k+=1	
print 'Private key: ('+str(d)+', '+str(n)+')'
public_key = str(e)+","+str(n)
private_key = [d, n]
s.send(public_key)
print '\n---Sent public key---\n'
ciphered = int(s.recv(1024))
print 'Received encrypted message: '+str(ciphered)
deciphered = pow(ciphered, d)%n
print 'Decrypted text: '+str(deciphered)
print
s.send(str(deciphered))
s.close 
