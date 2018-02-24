CC = g++ -O3 -fopenmp -DLINKASN1C -DREQUIRE_XML_EXPORT -static -I"boost_1_65_1"
CC2 = gcc -O3 -s -static 

LIBS = -I"asn1c-0.9.28/libasn1compiler" -I"asn1c-0.9.28/libasn1print" -I"asn1c-0.9.28/libasn1parser" -I"asn1c-0.9.28/libasn1fix" -I"asn1c-0.9.28/skeletons"

all: nspdh.exe enber.exe unber.exe enber.o

nspdh.exe: src/main.o src/nspdh_io.o src/nspdh_utilities.o enber.o
	$(CC) src/main.o src/nspdh_io.o src/nspdh_utilities.o enber.o -o nspdh.exe 

enber.o: 
	$(CC2) $(LIBS) -c asn1c-0.9.28/asn1c/enber.c -o enber.o -DBufferMode

enber.exe:  
	$(CC2) $(LIBS) asn1c-0.9.28/asn1c/enber.c -o enber.exe

unber.exe:  
	$(CC2) $(LIBS) asn1c-0.9.28/asn1c/unber.c -o unber.exe

src/main.o: 
	$(CC) -c src/main.cpp -o src/main.o 

src/nspdh_io.o:
	$(CC) -c src/nspdh_io.cpp -o src/nspdh_io.o

src/nspdh_utilities.o:
	$(CC) -c src/nspdh_utilities.cpp -o src/nspdh_utilities.o