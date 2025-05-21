CFILES = $(wildcard *.c)
HFILES = $(wildcard *.h)
OFILES = $(patsubst %.c,%.o,$(CFILES))

CFLAGS = -Wall -g
LDFLAGS = -g         
LIBS = -lSDL2

all: main

%.o: %.c $(HFILES)
	gcc $(CFLAGS) -c $< -o $@

main: $(OFILES)
	gcc $(LDFLAGS) -o $@ $^ $(LIBS)

clean:
	rm -f $(OFILES) main
