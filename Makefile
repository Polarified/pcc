CC = gcc
CFLAGS = -Wall -Wextra -Werror -O2
SRCS = $(wildcard src/*.c)
OBJS = $(patsubst src/%.c, obj/%.o, $(SRCS))
TARGET = bin/pcc

all: $(TARGET)

$(TARGET): $(OBJS)
	@mkdir -p bin
	$(CC) $(CFLAGS) -o $@ $^

obj/%.o: src/%.c
	@mkdir -p obj
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f obj/*.o obj/*.s $(TARGET)

.PHONY: all clean
