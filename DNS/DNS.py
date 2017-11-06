import socket

print("1- DNS to IP ");
print("2- IP to DNS ");
choice = int(input("Enter your choice : "))

if choice==1:
	ip = " ";
	w = raw_input("Enter DNS : ")
	ip = socket.gethostbyaddr(w);
	print("IP : ",ip)
	
if choice==2:
	w1 = " ";
	ip1 = raw_input("Enter DNS : ")
	w1 = socket.gethostbyname(ip1);
	print("DNS : ",w1)
