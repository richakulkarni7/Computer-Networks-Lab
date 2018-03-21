import socket
s = socket.socket()
port = input("Enter port number: ")
s.bind(('', int(port)))
s.listen(5)
c, addr = s.accept()
print('Got connection from'+str(addr)+'\n')

def show_frame(msg):
    show_msg = ""
    l = len(msg)
    show_msg += "| "
    for i in range(0, l):
        if i == l/2:
            show_msg += " | "
        show_msg += msg[i]+" "
    show_msg += "|"
    show_msg_deco = ""
    for i in range(0, len(show_msg)):
        show_msg_deco += "-"
    print(show_msg_deco)
    print(show_msg)
    print(show_msg_deco)

while True:
    msg = ""
    msg = str(c.recv(1024).decode())
    if msg == "exit":
        print("Exiting...")
        break
    print("\nReceived frames: ")
    show_frame(msg)
    if not (int(input("Are there errors? (No: 0, Yes: 1) "))):
        c.send("-1".encode())
    else:
        ack_sn = input("\tEnter the sequence number of the error: ")
        ack_window = input("\tEnter the window size: ")
        c.send((ack_sn+"+"+ack_window).encode())
        re_msg = str(c.recv(1024).decode())
        re_msg = re_msg[:int(ack_window)*2]
        print("\tReceived retransmitted frames: ")
        show_frame(re_msg)
        c.send("-1".encode())
c.close()