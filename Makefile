FLAGS = -pedantic-errors -std=c++11

highscore.txt:
	touch highscore.txt

game: highscore.txt
	g++ $(FLAGS) game.cpp -o game -lncurses

clearscores:
	rm -f highscore.txt

clean:
	rm -f game.o game

uninstall:
	rm -f game.o game highscore.txt

.PHONY: clearscores clean uninstall
