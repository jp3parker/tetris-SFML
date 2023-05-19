
#ifndef GAME_HEADER
#define GAME_HEADER

#include <iostream>
#include "stdlib.h"
#include "time.h"
#include <SFML/Graphics.hpp>
#include <vector>
#include "string.h"

#define ROWS 20
#define COLS 10
#define SPRITE_WIDTH 60

using std::vector;
using std::cout;
using std::endl;
using sf::Texture;
using sf::Sprite;

struct Tetromino {
  bool current;
};

struct Square {
  char typeOfPiece; // either I, O, T, ...
  Sprite sprite;
  Tetromino* tetromino;
};

class Tetris {
public:
  Tetris();
  void playGame();
private:
  void loadTextures();
  void drawSprites();
  void lowerCurrentTetromino();
  void goLeft();
  void goRight();
  void checkToRemoveRows();
  
  sf::RenderWindow window;
  std::string FailureToLoadError;
  
  void makeNewTetromino();
  void makeIPiece();
  void makeOPiece();
  void makeTPiece();
  void makeSPiece();
  void makeZPiece();
  void makeJPiece();
  void makeLPiece();
  
  /*
     for info on the different pieces
     visit: https://shorturl.at/fgnBV
  */
  Texture I; // Straight piece
  Texture O; // Square piece
  Texture T; // T-shaped piece
  Texture S; // S-shaped piece
  Texture Z; // Z-shaped piece
  Texture J; // J-shaped piece
  Texture L; // L-shaped piece
  Texture Background;
  Sprite background;
  Square* board [ROWS + 3][COLS];
};

#endif//GAME_HEADER
