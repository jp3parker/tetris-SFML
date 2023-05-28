
# This makefile will (probably) only work for my system. You will need to
# install SFML and figure out how to compile it on your system if you wish to
# run this code

output: main.o game.o
	g++ -O3 main.o game.o -o output -L /usr/local/Cellar/sfml/2.5.1_2/lib -lsfml-graphics -lsfml-window -lsfml-system -std=c++17

main.o: main.cpp main.h game.o
	g++ -c -O3 main.cpp -std=c++17

game.o: game.cpp game.h
	g++ -c -O3 game.cpp -std=c++17

clean: 
	rm *.o output

