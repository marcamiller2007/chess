CC=g++
CFLAGS=--std=c++17 -Wall -Werror -Wshadow -pedantic -g -I/opt/homebrew/include
DEPENDENCIES=-L/opt/homebrew/lib -lsfml-graphics -lsfml-system -lsfml-window
OBJ=main.o

main.o : main.cc
	$(CC) -c $< -o $@ $(CFLAGS)

%.o : %.cc %.h
	$(CC) -c $< -o $@ $(CFLAGS)

chess_game : $(OBJ)
	$(CC) -o $@ $^ $(DEPENDENCIES)

clean:
	rm *.o
	rm chess_game
