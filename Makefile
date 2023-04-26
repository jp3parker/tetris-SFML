
# This makefile will (probably) only work for my system. You will need to
# install SFML and figure out how to compile it on your system if you wish to
# run this code

output: main.o game.o
	g++ main.o game.o -o output -L /usr/local/Cellar/sfml/2.5.1_2/lib -lsfml-graphics -lsfml-window -lsfml-system

main.o: main.cpp main.h
	g++ -c main.cpp

game.o: game.cpp game.h
	g++ -c game.cpp

clean: 
	rm *.o output

