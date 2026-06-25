CC=g++
CFLAGS=--std=c++17 -Wall -Werror -Wshadow -pedantic -g
OBJ=main.o

main.o : main.cc
	$(CC) -c $< -o $@ $(CFLAGS)

%.o : %.cc %.h
	$(CC) -c $< -o $@ $(CFLAGS)

chess : $(OBJ)
	$(CC) -o $@ $^
	mv ./$@ ./build/
