
#include "game.h"

Tetris::Tetris() : window(sf::VideoMode(600, 1200), "Tetris!") {
  window.setFramerateLimit(30);
  loadTextures();
  for (int i = 0; i < ROWS + 3; ++i) {
    for (int j = 0; j < COLS; ++j) {
      board[i][j] = NULL;
    }
  }
}

void Tetris::playGame() {
  if (FailureToLoadError != "") {
    std::cout << FailureToLoadError << std::endl;
    return;
  }
  makeZPiece();
  background.setTexture(Background);
  while (window.isOpen()) {
    sf::Event event;
    while (window.pollEvent(event))
    {
      if (event.type == sf::Event::Closed) {
        window.close();
      }
    }
    window.clear();
    drawSprites();
    window.display();
  }
}

void Tetris::drawSprites() {
  window.draw(background);
  for (int i = 3; i < ROWS + 3; ++i) {
    for (int j =  0; j < COLS; ++j) {
      if (board[i][j] != NULL) {
        window.draw(board[i][j]->sprite);
      }
    }
  }
}

void Tetris::makeIPiece() {
  board[0][COLS / 2] = new Square;
  board[1][COLS / 2] = new Square;
  board[2][COLS / 2] = new Square;
  board[3][COLS / 2] = new Square;
  board[0][COLS / 2]->typeOfPiece = 'I';
  board[1][COLS / 2]->typeOfPiece = 'I';
  board[2][COLS / 2]->typeOfPiece = 'I';
  board[3][COLS / 2]->typeOfPiece = 'I';
  board[0][COLS / 2]->sprite.setTexture(I);
  board[1][COLS / 2]->sprite.setTexture(I);
  board[2][COLS / 2]->sprite.setTexture(I);
  board[3][COLS / 2]->sprite.setTexture(I);
  board[0][COLS / 2]->sprite.setPosition(SPRITE_WIDTH * 5, SPRITE_WIDTH * -3);
  board[1][COLS / 2]->sprite.setPosition(SPRITE_WIDTH * 5, SPRITE_WIDTH * -2);
  board[2][COLS / 2]->sprite.setPosition(SPRITE_WIDTH * 5, SPRITE_WIDTH * -1);
  board[3][COLS / 2]->sprite.setPosition(SPRITE_WIDTH * 5, SPRITE_WIDTH * 0);
  
}

void Tetris::makeOPiece() {
  board[2][COLS / 2] = new Square;
  board[2][COLS / 2 + 1] = new Square;
  board[3][COLS / 2] = new Square;
  board[3][COLS / 2 + 1] = new Square;
  board[2][COLS / 2]->typeOfPiece = 'O';
  board[2][COLS / 2 + 1]->typeOfPiece = 'O';
  board[3][COLS / 2]->typeOfPiece = 'O';
  board[3][COLS / 2 + 1]->typeOfPiece = 'O';
  board[2][COLS / 2]->sprite.setTexture(O);
  board[2][COLS / 2 + 1]->sprite.setTexture(O);
  board[3][COLS / 2]->sprite.setTexture(O);
  board[3][COLS / 2 + 1]->sprite.setTexture(O);
  board[2][COLS / 2]->sprite.setPosition(SPRITE_WIDTH * 4, SPRITE_WIDTH * -1);
  board[2][COLS / 2 + 1]->sprite.setPosition(SPRITE_WIDTH * 5, SPRITE_WIDTH * -1);
  board[3][COLS / 2]->sprite.setPosition(SPRITE_WIDTH * 4, SPRITE_WIDTH * 0);
  board[3][COLS / 2 + 1]->sprite.setPosition(SPRITE_WIDTH * 5, SPRITE_WIDTH * 0);
}

void Tetris::makeTPiece() {
  board[1][COLS / 2] = new Square;
  board[2][COLS / 2] = new Square;
  board[3][COLS / 2] = new Square;
  board[2][COLS / 2 + 1] = new Square;
  board[1][COLS / 2]->typeOfPiece = 'T';
  board[2][COLS / 2]->typeOfPiece = 'T';
  board[3][COLS / 2]->typeOfPiece = 'T';
  board[2][COLS / 2 + 1]->typeOfPiece = 'T';
  board[1][COLS / 2]->sprite.setTexture(T);
  board[2][COLS / 2]->sprite.setTexture(T);
  board[3][COLS / 2]->sprite.setTexture(T);
  board[2][COLS / 2 + 1]->sprite.setTexture(T);
  board[1][COLS / 2]->sprite.setPosition(SPRITE_WIDTH * 4, SPRITE_WIDTH * -2);
  board[2][COLS / 2]->sprite.setPosition(SPRITE_WIDTH * 4, SPRITE_WIDTH * -1);
  board[3][COLS / 2]->sprite.setPosition(SPRITE_WIDTH * 4, SPRITE_WIDTH * 0);
  board[2][COLS / 2 + 1]->sprite.setPosition(SPRITE_WIDTH * 5, SPRITE_WIDTH * -1);
}

void Tetris::makeSPiece() {

}

void Tetris::makeZPiece() {
  board[2][COLS / 2] = new Square;
  board[2][COLS / 2 + 1] = new Square;
  board[3][COLS / 2 + 1] = new Square;
  board[3][COLS / 2 + 2] = new Square;
  board[2][COLS / 2]->typeOfPiece = 'Z';
  board[2][COLS / 2 + 1]->typeOfPiece = 'Z';
  board[3][COLS / 2 + 1]->typeOfPiece = 'Z';
  board[3][COLS / 2 + 2]->typeOfPiece = 'Z';
  board[2][COLS / 2]->sprite.setTexture(Z);
  board[2][COLS / 2 + 1]->sprite.setTexture(Z);
  board[3][COLS / 2 + 1]->sprite.setTexture(Z);
  board[3][COLS / 2 + 2]->sprite.setTexture(Z);
  board[2][COLS / 2]->sprite.setPosition(SPRITE_WIDTH * 4, SPRITE_WIDTH * -1);
  board[2][COLS / 2 + 1]->sprite.setPosition(SPRITE_WIDTH * 5, SPRITE_WIDTH * -1);
  board[3][COLS / 2 + 1]->sprite.setPosition(SPRITE_WIDTH * 5, SPRITE_WIDTH * 0);
  board[3][COLS / 2 + 2]->sprite.setPosition(SPRITE_WIDTH * 6, SPRITE_WIDTH * 0);
}

void Tetris::makeJPiece() {

}

void Tetris::makeLPiece() {

}

void Tetris::loadTextures() {
  if (!Background.loadFromFile("images/tetris-background.png")) {
    FailureToLoadError += "Could not load images/tetris-background.png\n";
  }
  if (!O.loadFromFile("images/yellow-square.png")) {
    FailureToLoadError += "Could not load images/yellow-square.png\n";
  }
  if (!Z.loadFromFile("images/red-square.png")) {
    FailureToLoadError += "Could not load images/red-square.png\n";
  }
  if (!T.loadFromFile("images/purple-square.png")) {
    FailureToLoadError += "Could not load images/purple-square.png\n";
  }
  if (!L.loadFromFile("images/orange-square.png")) {
    FailureToLoadError += "Could not load images/orange-square.png\n";
  }
  if (!I.loadFromFile("images/light-blue-square.png")) {
    FailureToLoadError += "Could not load images/light-blue-square.png\n";
  }
  if (!S.loadFromFile("images/green-square.png")) {
    FailureToLoadError += "Could not load images/green-square.png\n";
  }
  if (!J.loadFromFile("images/dark-blue-square.png")) {
    FailureToLoadError += "Could not load images/dark-blue-square.png\n";
  }
}
