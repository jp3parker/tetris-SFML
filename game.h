
#ifndef GAME_HEADER
#define GAME_HEADER

#include <iostream>
#include <SFML/Graphics.hpp>
#include "string.h"

using sf::Texture;
using sf::Sprite;

class Tetris {
public:
  Tetris();
  void playGame();
private:
  void loadTextures();
  
  sf::RenderWindow window;
  std::string FailureToLoadError;
  
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
  Sprite* board [10][23];
};

#endif//GAME_HEADER