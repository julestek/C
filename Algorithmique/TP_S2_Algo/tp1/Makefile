CFILES = $(wildcard *.c)
HFILES = $(wildcard *.h)
OFILES = $(patsubst %.c,%.o,$(CFILES))
GCC_FLAGS = -Wall -g -Wextra 
LD_FLAGS = 

all: main

%.o: %.c $(HFILES)
	gcc $(GCC_FLAGS) -c $<

main: $(OFILES) $(HFILES)
	gcc $(LD_FLAGS) -o main $(OFILES) -fsanitize=address,undefined

clean:
	-rm $(OFILES)
