CC = gcc
CFLAGS = -Wall -Wextra -g -lSDL2 -lm -std=c99
CLOAD = myBubble.h
CFILES = main.c
COUT = main
BIN = bin
LOG = log
SRC = src
INCLUDE = include
LOGFILE = error.log

all : compile

compile :
	@echo "Sous Licence GPLv3"
	if [ ! -d $(BIN) ]; then mkdir $(BIN); fi
	if [ ! -d $(LOG) ]; then mkdir $(LOG); fi
	@echo "Compiling..."
	$(CC) $(SRC)/$(CFILES) $(CFLAGS) $(CLIBS) -o $(BIN)/$(COUT) 2> $(LOG)/$(LOGFILE)
	@echo "Compilation done."

run : compile
	@echo "Running..."
	./$(BIN)/$(COUT)
	@echo "Done."

clean :
	@echo "Cleaning..."
	rm -f $(BIN)/* $(LOG)/*
	@echo "Done."
