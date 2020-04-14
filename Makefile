clean: coinche.exe
	rm main.o
	rm coinche.o

coinche.exe: main.o coinche.o
	gcc -o coinche.exe main.o coinche.o

main.o: main.c
	gcc -Wall -Werror -g -c main.c

coinche.o: coinche.c
	gcc -Wall -Werror -g -c coinche.c