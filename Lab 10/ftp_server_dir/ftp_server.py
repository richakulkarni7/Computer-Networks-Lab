import socket
import subprocess
import os
s = socket.socket()
host = socket.gethostname()
port = int(input("Enter port number: "))
s.connect((host, port))
while True:
	cmd = s.recv(1024).decode()
	print('\n---Received command '+cmd+'---')
	if cmd[:3] == "get":
		get_file = cmd[4:]
		print('Getting file '+get_file)
		get_server_file = open(get_file, "r")
		s.send(get_server_file.read().encode())
		print('Sent contents')

	elif cmd[:3] == "put":
		put_file = cmd[4:]
		put_new_file = open(put_file, "w")
		put_new_file.write(s.recv(4096).decode())
		print('Received contents')
		print('Created file '+cmd[4:])

	elif cmd == "pwd":
		print('Sending path')
		proc = subprocess.Popen('pwd', stdout = subprocess.PIPE, stderr = subprocess.PIPE)
		output, err = proc.communicate()
		s.send(output)

	elif cmd == "ls":
		proc = subprocess.Popen('ls', stdout = subprocess.PIPE, stderr = subprocess.PIPE)
		output, err = proc.communicate()
		s.send(output)

	elif cmd[:2] == "cd":
		cd_path = cmd[3:]
		os.chdir(cd_path)
		print('Going to '+cd_path)
		s.send("1".encode())

	elif cmd == "quit":
		s.send("1".encode())
		print('Exiting')
		break

s.close()