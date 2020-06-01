DEBUG := true
PROFILING := false

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
ifeq ($(PROFILING),true)
	CFLAGS := -g -pg -Wall -Werror
	LFLAGS := -pg
else
	CFLAGS := -g -Wall -Werror
	LFLAGS :=
endif
else
	CFLAGS := -Wall -Werror
	LFLAGS :=
endif

coinche.exe: $(OBJS)
ifeq ($(DEBUG),true)
ifeq ($(PROFILING),true)
	@echo "Profiling compilation"
else
	@echo "Debug compilation"
endif
else
	@echo "Release compilation"
endif
	$(CC) $(LFLAGS) -o $@ $^

%.o: src/%.c
	$(CC) $(CFLAGS) -o $@ -c $<

clean:
	$(RM)