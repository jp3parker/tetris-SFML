
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
  
}

void Tetris::makeOPiece() {

}

void Tetris::makeTPiece() {

}

void Tetris::makeSPiece() {

}

void Tetris::makeZPiece() {

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
