CC = gcc
CFLAGS = -Wall -Wextra -g -lSDL2 -lm
all : compile

compile :
	@echo "Compiling..."
	$(CC) -o main main.c $(CFLAGS)
	@echo "Compilation done."

run : compile
	@echo "Running..."
	./main
	@echo "Done."