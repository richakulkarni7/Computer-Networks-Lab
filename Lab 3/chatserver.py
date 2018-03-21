import socket             
s = socket.socket()      
host = socket.gethostname()
port = input("Enter port number: ")               
s.connect((host, port))
for i in range(3):
	print "CLIENT: " + s.recv(1024)
	s.send(raw_input("SERVER: "))
s.close 
