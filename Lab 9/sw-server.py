import socket
s = socket.socket()
host = socket.gethostname()
port = int(input("Enter port number: "))
s.connect((host, port))
f = int(input("\nEnter size of frame: "))
msg = input("Enter text to be transmitted: ")
l = len(msg)
seq = ""
for i in range(0, l):
    seq += str(i)
i = 0
while(i<l):
    frame = ""
    if i+f > l:
        frame += msg[i:l]
        frame += seq[i:l]
    else:
        frame += msg[i:i+f]
        frame += seq[i:i+f]
    print("\nSending frames "+seq[i:i+f])
    s.send(frame.encode())
    ack = str(s.recv(1024).decode())
    if(ack=="-1"):
        print("Transmission successful\n")
    else:
        ack = ack.split('+')
        ack_sn = int(ack[0])
        ack_window = int(ack[1])
        print("\n\tReceived error: From frame "+str(ack_sn)+" with window size "+str(ack_window))
        print("\tRetransmitting frames...")
        re_frame = ""
        re_frame += msg[ack_sn:ack_sn+ack_window]
        re_frame += seq[ack_sn:ack_sn+ack_window]
        s.send(re_frame.encode())
        s.recv(1024)
    i += f
s.send("exit".encode())
print("Exiting...")
s.close()


