# tetris-SFML

This program is a Tetris game designed with the purpose of having some fun 
while also learning the basics of the SFML library.

## Usage

Note: The Makefile is meant to only work for my personal computer. It probably
will not work on another computer other than my own. You will need to figure
out how to properly link SFML to compile this program on your own computer.

To use this program, you must have some basic C++ libraries installed and 
SFML installed on your computer. You also must know how to compile with the
SFML libraries linked.

If you have a mac, you can use the file manager called Brew to download SFML.
[Information on Brew](https://brew.sh)

=====================================================

* Technologies and Libraries:
  * Libraries
    * SFML - to deal with sprites, opening/closing windows.
    * time - to seed random number generator "randomly" with time(NULL)
    * random - to generate a random number (to randomly choose the next piece)
  * Other Technologies
    * C++ - a type of database that holds user table and comments table
    
* To be improved
  * I would like to add an animation when a tetris row is removed. Something
    like the row flashes and then disappears.
  * I would've also like to add some sound or music to the game as well.
  * Some mechanics of the game are not how I would want them to work optimally.
    Something specific is that if a tetris piece is on the side of the board
    and the user tries to rotate it, the game currently won't let the user 
    rotate it because part of the piece would go off the board. I would rather
    have it to where the piece rotates anyway but is moved to the left or right
    where it would still be on the board.
    
* Things learned
  * How to deal with SFML. It's super useful and (in hindsight) pretty easy
    to use after setting up.
  * How to make more realistic games.
