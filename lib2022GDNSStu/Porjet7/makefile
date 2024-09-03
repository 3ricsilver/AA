# ListeS

LIBS=
all:	ex07	dnslib.o

dnslib.o:	../ndnslib/dnslib.h	../ndnslib/dnslib.c
	echo "Compilation de ListeSimple"
	cc -c ../ndnslib/dnslib.c	

ex07:	ex07.c	dnslib.o
	echo "Compilation de client"
	cc  -o ex07	ex07.c dnslib.o	$(LIBS)

