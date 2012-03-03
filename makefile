CC = gcc
OBJECTS =
LIBS = -lm
CFLAGS = -I ./ #-Wall
BINDIR = 
NAME = piccolo
SOURCES = piccolo.c

main:
	$(CC) $(SOURCES) -DPICCOLO=128 $(CFLAGS) $(LIBS) -o piccolo-128
	$(CC) $(SOURCES) -DPICCOLO=80 $(CFLAGS) $(LIBS) -o piccolo-80

clean:
	rm -vf *.o $(NAME)
