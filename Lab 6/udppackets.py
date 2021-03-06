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
n = input('Enter number of packets you want: ')
i = 0
# receive a packet
while(i<n):	
	packet = s.recvfrom(65565)
	 
	#packet string from tuple
	packet = packet[0]
	 
	#parse ethernet header
	eth_length = 14
	 
	eth_header = packet[:eth_length]
	eth = unpack('!6s6sH' , eth_header)
	eth_protocol = socket.ntohs(eth[2])
	
	#Parse IP header
	#take first 20 characters for the ip header
	ip_header = packet[eth_length:20+eth_length]
	 
	#now unpack them
	iph = unpack('!BBHHHBBH4s4s' , ip_header)

	version_ihl = iph[0]
	version = version_ihl >> 4
	ihl = version_ihl & 0xF

	iph_length = ihl * 4

	ttl = iph[5]
	protocol = iph[6]
	s_addr = socket.inet_ntoa(iph[8]);
	d_addr = socket.inet_ntoa(iph[9]);


	if protocol == 17 :
		i+=1
		print
		print
		print '--PACKET '+str(i)+'--'
		print 'Destination MAC : ' + eth_addr(packet[0:6]) + ' Source MAC : ' + eth_addr(packet[6:12]) + ' Protocol : ' + str(eth_protocol)
		print '--UDP--'
		u = iph_length + eth_length
		udph_length = 8
		udp_header = packet[u:u+8]

		#now unpack them :)
		udph = unpack('!HHHH' , udp_header)
		 
		source_port = udph[0]
		dest_port = udph[1]
		length = udph[2]
		checksum = udph[3]
		 
		print 'Source Port : ' + str(source_port) + ' Dest Port : ' + str(dest_port) + ' Length : ' + str(length) + ' Checksum : ' + str(checksum)
		 
		h_size = eth_length + iph_length + udph_length
		data_size = len(packet) - h_size
		 
		#get data from the packet
		data = packet[h_size:]
		 
		print 'Data : ' + data
