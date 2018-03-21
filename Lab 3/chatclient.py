import socket               
s = socket.socket()         
port = input("Enter port number: ")               
s.bind(('', port))        
s.listen(5)
while True:
	c, addr = s.accept()     
   	print 'Got connection from', addr
	for i in range(3): 
   		c.send(raw_input("CLIENT: "))
		print "SERVER: "+c.recv(1024)
 	c.close()
	break
