import socket
s = socket.socket()
port = input("Enter port number: ")
s.bind(('', int(port)))
s.listen(5)
c, addr = s.accept()
print('Got connection from'+str(addr)+'\n')
print('---Welcome to FTP simulation---')
print('Available commands: cd, ls, pwd, get, put, quit')
print('----------------------')
while True:
	cmd = ""
	cmd = str(input("\nftp> "))
	if cmd[:3] == "get":
		c.send(cmd.encode())
		get_file = cmd[4:]
		get_new_file = open(get_file, "w")
		get_new_file.write(c.recv(4096).decode())
		print('Created file '+cmd[4:])

	elif cmd[:3] == "put":
		c.send(cmd.encode())
		put_file = cmd[4:]
		put_client_file = open(put_file, "r")
		c.send(put_client_file.read().encode())
		print('Sent contents')

	elif cmd == "pwd":
		c.send("pwd".encode())
		print(c.recv(1024).decode())


	elif cmd == "ls":
		c.send("ls".encode())
		print(c.recv(1024).decode())

	elif cmd[:2] == "cd":
		c.send(cmd.encode())
		cd_path = cmd[3:]
		status = c.recv(1024).decode()
		if status == "1":
			print('Remote directory changed successfully.')
		else:
			print('cd operation failed')

	elif cmd == "quit":
		c.send("quit".encode())
		status = c.recv(1024).decode()
		if status == "1":
			print('Exiting')
			break
		else:
			print('Quit failed')

c.close()