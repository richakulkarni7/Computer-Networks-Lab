import socket, sys
from struct import *
	
#Convert a string of 6 characters of ethernet address into a dash separated hex string
def eth_addr (a) :
	b = "%.2x:%.2x:%.2x:%.2x:%.2x:%.2x" % (ord(a[0]) , ord(a[1]) , ord(a[2]), ord(a[3]), ord(a[4]) , ord(a[5]))
	return b
 
#create a AF_PACKET type raw socket

try:
	s = socket.socket( socket.AF_PACKET , socket.SOCK_RAW , socket.ntohs(0x0003))
except socket.error , msg:
	print 'Socket could not be created. Error Code : ' + str(msg[0]) + ' Message ' + msg[1]
	sys.exit()
# receive a packet
icmp = 0
tcp  = 0
udp  = 0
igmp = 0
for i in range(0, 10000):
	packet = s.recvfrom(65565)
	 
	#packet string from tuple
	packet = packet[0]
	eth_length = 14
 
	#Parse IP packets, IP Protocol number = 8
	#Parse IP header
	#take first 20 characters for the ip header
	ip_header = packet[eth_length:20+eth_length]
	 
	#now unpack them
	iph = unpack('!BBHHHBBH4s4s' , ip_header)
	ttl = iph[5]
	protocol = iph[6]
	#TCP protocol
	if protocol == 6 :
		tcp+=1	

	#ICMP Packets
	elif protocol == 1 :
		icmp+=1		

	#UDP packets
	elif protocol == 17 :
		udp+=1

	#IGMP Packets
	elif protocol == 88 :
		igmp+=1
	sys.stdout.write("\rTCP: %d UDP: %d ICMP: %d IGMP: %d Total: %d" %(tcp, udp, icmp, igmp, i+1))
	sys.stdout.flush()
print

	

	
		

	
