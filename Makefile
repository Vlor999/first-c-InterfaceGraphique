CC = gcc
CFLAGS = -Wall -Wextra -g -lSDL2 -lm
CLOAD = myBubble.h
CFILES = main.c
COUT = main
BIN = bin
all : compile

compile :
	@echo "Compiling..."
	$(CC) -o $(BIN)/$(COUT) $(CFILES) $(CFLAGS) $(CLOAD) 2> log/error.log
	@echo "Compilation done."

run : compile
	@echo "Running..."
	./$(BIN)/$(COUT)
	@echo "Done."