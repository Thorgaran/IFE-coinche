OS=$(shell uname)
ifeq ($(OS), CYGWIN_NT-10.0)
	CLEANCMD=rm
else
	CLEANCMD=del
endif

clean: coinche.exe
	$(CLEANCMD) main.o
	$(CLEANCMD) core.o
	$(CLEANCMD) play.o
	$(CLEANCMD) ai.o
	$(CLEANCMD) userIO.o

coinche.exe: main.o core.o play.o ai.o userIO.o
	gcc -o $@ $^

main.o: main.c
	gcc -Wall -Werror -g -c $<

core.o: core.c
	gcc -Wall -Werror -g -c $<

play.o: play.c
	gcc -Wall -Werror -g -c $<

ai.o: ai.c
	gcc -Wall -Werror -g -c $<

userIO.o: userIO.c
	gcc -Wall -Werror -g -c $<
