# Compiler:
CC=gcc
# Compiler options:
CFLAGS=-w
# Sources folder:
F=normalization/
# Destination folder:
B=bin/
# Objects folder: 
O=obj/


# all:
all: build normalize-game find-transformations-main transform-move-main

build:
	@mkdir -p $(O)

normalize-game: $(O)normalize-game.o $(O)find-transformations.o $(O)util.o $(O)transform-move.o 
	$(CC) -o $(B)$@ $(O)normalize-game.o $(O)find-transformations.o $(O)util.o $(O)transform-move.o 

find-transformations-main: $(O)find-transformations-main.o $(O)find-transformations.o $(O)util.o $(O)argument-checker.o $(O)transform-move.o
	$(CC) -o $(B)$@ $(O)find-transformations-main.o $(O)find-transformations.o $(O)util.o $(O)argument-checker.o $(O)transform-move.o 

transform-move-main: $(O)transform-move-main.o $(O)transform-move.o $(O)util.o $(O)argument-checker.o 
	$(CC) -o $(B)$@ $(O)transform-move-main.o $(O)transform-move.o $(O)util.o $(O)argument-checker.o 

$(O)%.o : $(F)%.c
	$(CC) $(CFLAGS) -c $< -o $@


# clean:
clean:
	rm -rf $(B)normalize-game $(B)find-transformations-main $(B)transform-move-main
	rm -rf $(O)
	find . -name "*~" -exec rm {} \;
	find . -name "*.o" -exec rm {} \;

