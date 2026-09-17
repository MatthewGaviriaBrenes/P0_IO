CC = gcc
TARGET = out

SRC = src/main.c \
      src/knapsack_items.c \
      src/knapsack_bag.c \
      src/greedy_algorithms.c \
      src/knapsack_run.c \
      src/demo_mode.c \
      src/experimental_mode.c \
      src/dynamic_programming.c \
      src/tex_generator.c

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRC)

clean:
	rm -f $(TARGET)

.PHONY: clean