
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
  cout << "got to play game" << endl;
  if (FailureToLoadError != "") {
    std::cout << FailureToLoadError << std::endl;
    return;
  }
  makeLPiece();
  cout << "make first piece" << endl;
  background.setTexture(Background);
  sf::Clock clock;
  while (window.isOpen()) {
    drawSprites();
    clock.restart();
    sf::Event event;
    while (clock.getElapsedTime().asSeconds() < 1) {
      if (window.pollEvent(event))
      {
        switch (event.type) {
          case sf::Event::Closed: {
            window.close();
            cout << "window is closed" << endl;
            break;
          }
          case sf::Event::KeyPressed: {
            cout << "key pressed" << endl;
            switch (event.key.code) {
              case sf::Keyboard::Left: {
                cout << "Left" << endl;
                goLeft();
                drawSprites();
                break;
              }
              case sf::Keyboard::Right: {
                cout << "Right" << endl;
                goRight();
                drawSprites();
                break;
              }
              case sf::Keyboard::Up: {
                cout << "Up" << endl;
                drawSprites();
                break;
              }
              case sf::Keyboard::Down: {
                cout << "Down" << endl;
                lowerCurrentTetromino();
                drawSprites();
                clock.restart();
                break;
              }
              default: {
                break;
              }
            }
            break;
          }
          default: {
            break;
          }
        }
      }
    }
    // time runs out
    cout << "time ran out" << endl;
    if (window.isOpen())
      lowerCurrentTetromino();
  }
  cout << "got here" << endl;
}

void Tetris::goLeft() {
  
}

void Tetris::goRight() {

}

void Tetris::lowerCurrentTetromino() {
  bool canLower = true;
  for (int i = ROWS + 2; i >= 0; --i) {
    for (int j = 0; j < COLS; ++j) {
      if (board[i][j] != NULL and board[i][j]->tetromino->current == true) {
        if (canLower and i + 1 < ROWS + 3 and
        (board[i + 1][j] == NULL or board[i + 1][j]->tetromino->current == true)) {
          // the current square is lowerable
        }
        else {
          /* either this square is not lowerable or another square on the
          current tetromino was already deemed not lowerable */
          canLower = false;
        }
      }
    }
  }
  if (canLower) {
    for (int i = ROWS + 2; i >= 0; --i) {
      for (int j = 0; j < COLS; ++j) {
        if (board[i][j] != NULL and board[i][j]->tetromino->current == true) {
          board[i][j]->sprite.move(0, SPRITE_WIDTH);
          board[i + 1][j] = board[i][j];
          board[i][j] = NULL;
        }
      }
    }
  }
  else { // can't lower anymore
    bool stopped = false;
    for (int i = 0; i < ROWS + 3 and !stopped; ++i) {
      for (int j = 0; j < COLS; ++j) {
        if (board[i][j] != NULL and board[i][j]->tetromino->current == true) {
          board[i][j]->tetromino->current = false;
        }
      }
    }
    makeNewTetromino();
  }
}

void Tetris::makeNewTetromino() {
  makeOPiece();
}

void Tetris::drawSprites() {
  window.clear();
  window.draw(background);
  for (int i = 3; i < ROWS + 3; ++i) {
    for (int j =  0; j < COLS; ++j) {
      if (board[i][j] != NULL) {
        window.draw(board[i][j]->sprite);
      }
    }
  }
  window.display();
}

void Tetris::makeIPiece() {
  board[0][COLS / 2] = new Square;
  board[1][COLS / 2] = new Square;
  board[2][COLS / 2] = new Square;
  board[3][COLS / 2] = new Square;
  Tetromino* t = new Tetromino;
  t->current = true;
  board[0][COLS / 2]->tetromino = t;
  board[1][COLS / 2]->tetromino = t;
  board[2][COLS / 2]->tetromino = t;
  board[3][COLS / 2]->tetromino = t;
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
  Tetromino* t = new Tetromino;
  t->current = true;
  board[2][COLS / 2]->tetromino = t;
  board[2][COLS / 2 + 1]->tetromino = t;
  board[3][COLS / 2]->tetromino = t;
  board[3][COLS / 2 + 1]->tetromino = t;
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
  Tetromino* t = new Tetromino;
  t->current = true;
  board[1][COLS / 2]->tetromino = t;
  board[2][COLS / 2]->tetromino = t;
  board[3][COLS / 2]->tetromino = t;
  board[2][COLS / 2 + 1]->tetromino = t;
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
  board[2][COLS / 2 + 1] = new Square;
  board[2][COLS / 2] = new Square;
  board[3][COLS / 2] = new Square;
  board[3][COLS / 2 - 1] = new Square;
  Tetromino* t = new Tetromino;
  t->current = true;
  board[2][COLS / 2 + 1]->tetromino = t;
  board[2][COLS / 2]->tetromino = t;
  board[3][COLS / 2]->tetromino = t;
  board[3][COLS / 2 - 1]->tetromino = t;
  board[2][COLS / 2 + 1]->typeOfPiece = 'S';
  board[2][COLS / 2]->typeOfPiece = 'S';
  board[3][COLS / 2]->typeOfPiece = 'S';
  board[3][COLS / 2 - 1]->typeOfPiece = 'S';
  board[2][COLS / 2 + 1]->sprite.setTexture(S);
  board[2][COLS / 2]->sprite.setTexture(S);
  board[3][COLS / 2]->sprite.setTexture(S);
  board[3][COLS / 2 - 1]->sprite.setTexture(S);
  board[2][COLS / 2 + 1]->sprite.setPosition(SPRITE_WIDTH * 5, SPRITE_WIDTH * -1);
  board[2][COLS / 2]->sprite.setPosition(SPRITE_WIDTH * 4, SPRITE_WIDTH * -1);
  board[3][COLS / 2]->sprite.setPosition(SPRITE_WIDTH * 4, SPRITE_WIDTH * 0);
  board[3][COLS / 2 - 1]->sprite.setPosition(SPRITE_WIDTH * 3, SPRITE_WIDTH * 0);
}

void Tetris::makeZPiece() {
  board[2][COLS / 2] = new Square;
  board[2][COLS / 2 + 1] = new Square;
  board[3][COLS / 2 + 1] = new Square;
  board[3][COLS / 2 + 2] = new Square;
  Tetromino* t = new Tetromino;
  t->current = true;
  board[2][COLS / 2]->tetromino = t;
  board[2][COLS / 2 + 1]->tetromino = t;
  board[3][COLS / 2 + 1]->tetromino = t;
  board[3][COLS / 2 + 2]->tetromino = t;
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
  board[1][COLS / 2] = new Square;
  board[2][COLS / 2] = new Square;
  board[3][COLS / 2] = new Square;
  board[3][COLS / 2 - 1] = new Square;
  Tetromino* t = new Tetromino;
  t->current = true;
  board[1][COLS / 2]->tetromino = t;
  board[2][COLS / 2]->tetromino = t;
  board[3][COLS / 2]->tetromino = t;
  board[3][COLS / 2 - 1]->tetromino = t;
  board[1][COLS / 2]->typeOfPiece = 'J';
  board[2][COLS / 2]->typeOfPiece = 'J';
  board[3][COLS / 2]->typeOfPiece = 'J';
  board[3][COLS / 2 - 1]->typeOfPiece = 'J';
  board[1][COLS / 2]->sprite.setTexture(J);
  board[2][COLS / 2]->sprite.setTexture(J);
  board[3][COLS / 2]->sprite.setTexture(J);
  board[3][COLS / 2 - 1]->sprite.setTexture(J);
  board[1][COLS / 2]->sprite.setPosition(SPRITE_WIDTH * 4, SPRITE_WIDTH * -2);
  board[2][COLS / 2]->sprite.setPosition(SPRITE_WIDTH * 4, SPRITE_WIDTH * -1);
  board[3][COLS / 2]->sprite.setPosition(SPRITE_WIDTH * 4, SPRITE_WIDTH * 0);
  board[3][COLS / 2 - 1]->sprite.setPosition(SPRITE_WIDTH * 3, SPRITE_WIDTH * 0);
}

void Tetris::makeLPiece() {
  board[1][COLS / 2] = new Square;
  board[2][COLS / 2] = new Square;
  board[3][COLS / 2] = new Square;
  board[3][COLS / 2 + 1] = new Square;
  Tetromino* t = new Tetromino;
  t->current = true;
  board[1][COLS / 2]->tetromino = t;
  board[2][COLS / 2]->tetromino = t;
  board[3][COLS / 2]->tetromino = t;
  board[3][COLS / 2 + 1]->tetromino = t;
  board[1][COLS / 2]->typeOfPiece = 'L';
  board[2][COLS / 2]->typeOfPiece = 'L';
  board[3][COLS / 2]->typeOfPiece = 'L';
  board[3][COLS / 2 + 1]->typeOfPiece = 'L';
  board[1][COLS / 2]->sprite.setTexture(L);
  board[2][COLS / 2]->sprite.setTexture(L);
  board[3][COLS / 2]->sprite.setTexture(L);
  board[3][COLS / 2 + 1]->sprite.setTexture(L);
  board[1][COLS / 2]->sprite.setPosition(SPRITE_WIDTH * 4, SPRITE_WIDTH * -2);
  board[2][COLS / 2]->sprite.setPosition(SPRITE_WIDTH * 4, SPRITE_WIDTH * -1);
  board[3][COLS / 2]->sprite.setPosition(SPRITE_WIDTH * 4, SPRITE_WIDTH * 0);
  board[3][COLS / 2 + 1]->sprite.setPosition(SPRITE_WIDTH * 5, SPRITE_WIDTH * 0);
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
