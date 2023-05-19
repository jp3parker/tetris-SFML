
#include "game.h"

Tetris::Tetris() : window(sf::VideoMode(600, 1200), "Tetris!") {
  window.setFramerateLimit(30);
  srand(time(NULL));
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
  makeLPiece();
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
            break;
          }
          case sf::Event::KeyPressed: {
            switch (event.key.code) {
              case sf::Keyboard::Left: {
                goLeft();
                drawSprites();
                break;
              }
              case sf::Keyboard::Right: {
                goRight();
                drawSprites();
                break;
              }
              case sf::Keyboard::Up: {
                drawSprites();
                break;
              }
              case sf::Keyboard::Down: {
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
    if (window.isOpen())
      lowerCurrentTetromino();
  }
}

void Tetris::goLeft() {
  bool canGoLeft = true;
  for (int i = 0; i < ROWS + 3; ++i) {
    for (int j = 0; j < COLS; ++j) {
      if (board[i][j] != NULL and board[i][j]->tetromino->current == true) {
        if (canGoLeft and j - 1 >= 0 and
        (board[i][j - 1] == NULL or board[i][j - 1]->tetromino->current == true)) {
          // the current square can go left
        }
        else {
          /* either this square can't go left or another square on the
          current tetromino was already deemed to not be able to go left */
          canGoLeft = false;
        }
      }
    }
  }
  if (canGoLeft) {
    for (int j = 0; j < COLS; ++j) {
      for (int i = 0; i < ROWS + 3; ++i) {
        if (board[i][j] != NULL and board[i][j]->tetromino->current == true) {
          board[i][j]->sprite.move(-1 * SPRITE_WIDTH, 0);
          board[i][j - 1] = board[i][j];
          board[i][j] = NULL;
        }
      }
    }
  }
  else {
    // current tetromino can't go left
    // do nothing
  }
}

void Tetris::goRight() {
  bool canGoRight = true;
  for (int i = 0; i < ROWS + 3; ++i) {
    for (int j = COLS - 1; j >= 0; --j) {
      if (board[i][j] != NULL and board[i][j]->tetromino->current == true) {
        if (canGoRight and j + 1 < COLS and
        (board[i][j + 1] == NULL or board[i][j + 1]->tetromino->current == true)) {
          // the current square can go right
        }
        else {
          /* either this square can't go right or another square on the
          current tetromino was already deemed to not be able to go right */
          canGoRight = false;
        }
      }
    }
  }
  if (canGoRight) {
    for (int j = COLS - 1; j >= 0; --j) {
      for (int i = 0; i < ROWS + 3; ++i) {
        if (board[i][j] != NULL and board[i][j]->tetromino->current == true) {
          board[i][j]->sprite.move(SPRITE_WIDTH, 0);
          board[i][j + 1] = board[i][j];
          board[i][j] = NULL;
        }
      }
    }
  }
  else {
    // current tetromino can't go right
    // do nothing
  }
}

void Tetris::lowerCurrentTetromino() {
  bool canLower = true;
  for (int i = 0; i < ROWS + 3; ++i) {
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
    checkToRemoveRows();
    makeNewTetromino();
  }
}

void Tetris::checkToRemoveRows() {
  for (int i = 0; i < ROWS + 3; ++i) {
    bool removeRow = true;
    for (int j = 0; j < COLS and removeRow; ++j) {
      if (board[i][j] == NULL) {
        removeRow = false;
      }
    }
    if (removeRow) {
      for (int j = 0; j < COLS; ++j) {
        delete board[i][j];
        board[i][j] = NULL;
      }
      for (int x = i - 1; x >= 0; --x) {
        for (int y = 0; y < COLS; ++y) {
          if (board[x][y] != NULL) {
            board[x][y]->sprite.move(0, SPRITE_WIDTH);
          }
          board[x + 1][y] = board[x][y];
          board[x][y] = NULL;
        }
      }
    }
  }
}

void Tetris::makeNewTetromino() {
  int randomNum0to6 = rand() % 7;
  switch (randomNum0to6) {
    case 0: {
      makeIPiece();
      break;
    }
    case 1: {
      makeOPiece();
      break;
    }
    case 2: {
      makeTPiece();
      break;
    }
    case 3: {
      makeSPiece();
      break;
    }
    case 4: {
      makeZPiece();
      break;
    }
    case 5: {
      makeJPiece();
      break;
    }
    case 6: {
      makeLPiece();
      break;
    }
    default: {
      break;
    }
  }
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
  board[2][COLS / 2]->sprite.setPosition(SPRITE_WIDTH * 5, SPRITE_WIDTH * -1);
  board[2][COLS / 2 + 1]->sprite.setPosition(SPRITE_WIDTH * 6, SPRITE_WIDTH * -1);
  board[3][COLS / 2]->sprite.setPosition(SPRITE_WIDTH * 5, SPRITE_WIDTH * 0);
  board[3][COLS / 2 + 1]->sprite.setPosition(SPRITE_WIDTH * 6, SPRITE_WIDTH * 0);
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
  board[1][COLS / 2]->sprite.setPosition(SPRITE_WIDTH * 5, SPRITE_WIDTH * -2);
  board[2][COLS / 2]->sprite.setPosition(SPRITE_WIDTH * 5, SPRITE_WIDTH * -1);
  board[3][COLS / 2]->sprite.setPosition(SPRITE_WIDTH * 5, SPRITE_WIDTH * 0);
  board[2][COLS / 2 + 1]->sprite.setPosition(SPRITE_WIDTH * 6, SPRITE_WIDTH * -1);
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
  board[2][COLS / 2 + 1]->sprite.setPosition(SPRITE_WIDTH * 6, SPRITE_WIDTH * -1);
  board[2][COLS / 2]->sprite.setPosition(SPRITE_WIDTH * 5, SPRITE_WIDTH * -1);
  board[3][COLS / 2]->sprite.setPosition(SPRITE_WIDTH * 5, SPRITE_WIDTH * 0);
  board[3][COLS / 2 - 1]->sprite.setPosition(SPRITE_WIDTH * 4, SPRITE_WIDTH * 0);
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
  board[2][COLS / 2]->sprite.setPosition(SPRITE_WIDTH * 5, SPRITE_WIDTH * -1);
  board[2][COLS / 2 + 1]->sprite.setPosition(SPRITE_WIDTH * 6, SPRITE_WIDTH * -1);
  board[3][COLS / 2 + 1]->sprite.setPosition(SPRITE_WIDTH * 6, SPRITE_WIDTH * 0);
  board[3][COLS / 2 + 2]->sprite.setPosition(SPRITE_WIDTH * 7, SPRITE_WIDTH * 0);
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
  board[1][COLS / 2]->sprite.setPosition(SPRITE_WIDTH * 5, SPRITE_WIDTH * -2);
  board[2][COLS / 2]->sprite.setPosition(SPRITE_WIDTH * 5, SPRITE_WIDTH * -1);
  board[3][COLS / 2]->sprite.setPosition(SPRITE_WIDTH * 5, SPRITE_WIDTH * 0);
  board[3][COLS / 2 - 1]->sprite.setPosition(SPRITE_WIDTH * 4, SPRITE_WIDTH * 0);
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
  board[1][COLS / 2]->sprite.setPosition(SPRITE_WIDTH * 5, SPRITE_WIDTH * -2);
  board[2][COLS / 2]->sprite.setPosition(SPRITE_WIDTH * 5, SPRITE_WIDTH * -1);
  board[3][COLS / 2]->sprite.setPosition(SPRITE_WIDTH * 5, SPRITE_WIDTH * 0);
  board[3][COLS / 2 + 1]->sprite.setPosition(SPRITE_WIDTH * 6, SPRITE_WIDTH * 0);
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
