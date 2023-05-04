FLAGS = -pedantic-errors -std=c++11

highscore.txt:
	touch highscore.txt

game.o: game.cpp
	g++ $(FLAGS) -lncurses -c game.cpp 

game: game.o highscore.txt
	g++ $(FLAGS) game.o -lncurses -o game

clearscores:
	rm -f highscore.txt

clean:
	rm -f game.o game

uninstall:
	rm -f game.o game highscore.txt

.PHONY: clearscores clean uninstall
