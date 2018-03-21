import socket              
s = socket.socket()         
port = input("Enter port number: ")               
s.bind(('', port))        
s.listen(5)
c, addr = s.accept()     
print 'Got connection from', addr
public_key = c.recv(1024).split(",")
e = int(public_key[0])
n = int(public_key[1])
print '\nReceived public key: ('+str(e)+', '+str(n)+')'
msg = int(input("Enter number to be encrypted: "))
ciphered = pow(msg, e)%n
print("Encrypted message: "+str(ciphered))
c.send(str(ciphered))
print '\n---Encrypted message sent to server---\n'
print 'Decrypted number from server: '+c.recv(1024)
print
c.close()
