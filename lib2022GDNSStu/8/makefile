# cphex\makefile

LIBS=
all:	dnslib.o udplib.o cli ser	

dnslib.o:	../ndnslib/dnslib.h	../ndnslib/dnslib.c
	echo "Compilation de ListeSimple"
	cc -c ../ndnslib/dnslib.c	

udplib.o:	../udplib/udplib.h	../udplib/udplib.c
	echo "Compilation de udplib.o"
	gcc -c ../udplib/udplib.c	

cli:	cli.c	udplib.o
	echo "Compilation de client"
	gcc  -o cli  cli.c udplib.o dnslib.o	$(LIBS)

ser:	ser.c	udplib.o
	echo "Compilation de serveur"
	gcc -o ser  ser.c udplib.o dnslib.o	$(LIBS)