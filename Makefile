DEBUG := true
PROFILING := false

CC := gcc

SRCS := $(wildcard src/*.c)
OBJS := $(SRCS:.c=.o)

ifeq ($(OS), Windows_NT)
	MACHINE=$(shell gcc -dumpmachine)
ifeq ($(MACHINE), x86_64-pc-cygwin)
	RM=rm -f src/*.o
else
	RM=del src\*.o
endif
	EXT=.exe
else
	RM=rm -f src/*.o
	EXT=
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

coinche: $(OBJS)
ifeq ($(DEBUG),true)
ifeq ($(PROFILING),true)
	@echo "Profiling compilation"
else
	@echo "Debug compilation"
endif
else
	@echo "Release compilation"
endif
	$(CC) $(LFLAGS) -o $@$(EXT) $^

%.o: src/%.c
	$(CC) $(CFLAGS) -o $@ -c $<

clean:
	$(RM)
