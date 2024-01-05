
SOURCES = main.c wish.c
OBJECTS = $(SOURCES:.c=.o)
TARGET = wish
C_FLAGS = -Werror -Wall -g



wish: $(OBJECTS)
	gcc -o $@ $^ $(C_FLAGS) 
clean:
	rm wish *.o
