DEBUG := true

CC := gcc

SRCS := $(wildcard src/*.c)
OBJS := $(SRCS:.c=.o)

OS=$(shell gcc -dumpmachine)
ifeq ($(OS), x86_64-pc-cygwin)
	RM=rm -f src/*.o
else
	RM=del src\*.o
endif

ifeq ($(DEBUG),true)
	CFLAGS := -g -Wall -Werror
else
	CFLAGS := -Wall -Werror
endif

coinche.exe: $(OBJS)
ifeq ($(DEBUG),true)
	@echo "Debug compilation"
else
	@echo "Release compilation"
endif
	$(CC) -o $@ $^

%.o: src/%.c
	$(CC) $(CFLAGS) -o $@ -c $<

clean:
	$(RM)