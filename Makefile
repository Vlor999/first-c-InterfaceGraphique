CC = gcc
CFLAGS = -Wall -Wextra -g -lSDL2 -lm
CLOAD = myBubble.h
CFILES = main.c
COUT = main
BIN = bin
LOG = log
LOGFILE = error.log

all : compile

compile :
	@echo "Sous Licence GPLv3"
	if [ ! -d $(BIN) ]; then mkdir $(BIN);fi
	if [ ! -d $(LOG) ]; then mkdir $(LOG);fi
	@echo "Compiling..."
	$(CC) -o $(BIN)/$(COUT) $(CFILES) $(CFLAGS) $(CLOAD) 2> $(LOG)/$(LOGFILE)
	@echo "Compilation done."

run : compile
	@echo "Running..."
	./$(BIN)/$(COUT)
	@echo "Done."

clean :
	@echo "Cleaning..."
	rm -f $(BIN)/* $(LOG)/*
	@echo "Done."