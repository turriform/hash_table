CC:= gcc

PROG:= prog

INCLUDE:= -I./include/


FLAGS:= -std=c11  -Wall -Wextra -Wpedantic \
          -Wformat=2 -Wno-unused-parameter -Wshadow \
          -Wwrite-strings -Wstrict-prototypes -Wold-style-definition \
          -Wredundant-decls -Wnested-externs -Wmissing-include-dirs -g 

C_SRC:= $(wildcard ./src/*.c ./src/hash_table/*.c)

TARGET:= ./bin/$(PROG)

all:
	$(CC) $(FLAGS)  $(INCLUDE) $(C_SRC) -o $(TARGET) && $(TARGET)


val:
	valgrind -s --leak-check=full --track-origins=yes $(TARGET) 

gdb:
	gdb $(TARGET)

test:
	$(TARGET) ./input/test.txt
