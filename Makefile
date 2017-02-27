hw3: hw3.o solve.o histo.o invkey.o keygen.o crypt.o stream.o 
	gcc -o hw3 -g hw3.o solve.o histo.o invkey.o keygen.o crypt.o stream.o -L/usr/include/openssl/lib -lcrypto -lm

hw3.o: hw3.c stream.h keygen.h crypt.h invkey.h histo.h solve.h
	gcc -g -c -Wall hw3.c

solve.o: solve.c solve.h
	gcc -g -c -Wall solve.c

histo.o: histo.c histo.h
	gcc -g -c -Wall histo.c

invkey.o: invkey.c invkey.h
	gcc -g -c -Wall invkey.c

crypt.o: crypt.c crypt.h
	gcc -g -c -Wall crypt.c

keygen.o: keygen.c keygen.h
	gcc -g -c -Wall keygen.c

stream.o: stream.c stream.h
	gcc -g -c -Wall stream.c -I/usr/include/openssl/include

clean:
	rm -rf *.o hw3