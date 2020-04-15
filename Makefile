clean: coinche.exe
	rm main.o
	rm core.o
	rm play.o

coinche.exe: main.o core.o play.o
	gcc -o coinche.exe main.o core.o play.o

main.o: main.c
	gcc -Wall -Werror -g -c main.c

core.o: main.c
	gcc -Wall -Werror -g -c core.c

play.o: play.c
	gcc -Wall -Werror -g -c play.c