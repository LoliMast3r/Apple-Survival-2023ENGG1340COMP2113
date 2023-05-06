FLAGS = -pedantic-errors -std=c++11

highscore.txt:
	touch highscore.txt

game.o: highscore.txt game.cpp obtainItem.h PortalGen.h clearwindow.h
	g++ $(FLAGS) -c game.cpp

obtainItem.o: obtainItem.cpp obtainItem.h
	g++ $(FLAGS) -c obtainItem.cpp

PortalGen.o: PortalGen.cpp PortalGen.h
	g++ $(FLAGS) -c PortalGen.cpp

clearwindow.o: clearwindow.cpp clearwindow.h 
	g++ $(FLAGS) -c clearwindow.cpp

game: highscore.txt game.o obtainItem.o PortalGen.o clearwindow.o
	g++ $(FLAGS) game.o obtainItem.o PortalGen.o clearwindow.o -o game -lncurses

clearscores:
	rm -f highscore.txt

clean:
	rm -f game.o game

uninstall:
	rm -f game.o game highscore.txt

.PHONY: clearscores clean uninstall
