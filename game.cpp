
#include "game.h"

Tetris::Tetris() : window(sf::VideoMode(600, 1200), "Tetris!") {
  window.setFramerateLimit(30);
  loadTextures();
  for (int i = 0; i < ROWS + 3; ++i) {
    for (int j = 0; j < COLS; ++j) {
      board[i][j] = NULL;
    }
  }
  currentTetrominoPositions.push_back({ 0, 0 });
  currentTetrominoPositions.push_back({ 0, 0 });
  currentTetrominoPositions.push_back({ 0, 0 });
  currentTetrominoPositions.push_back({ 0, 0 });
  widthOfCurrentTetromino = 0;
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
                drawSprites();
                clock.restart();
                break;
              }
              case sf::Keyboard::Right: {
                cout << "Right" << endl;
                drawSprites();
                clock.restart();
                break;
              }
              case sf::Keyboard::Up: {
                cout << "Up" << endl;
                drawSprites();
                clock.restart();
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
    lowerCurrentTetromino();
  }
  cout << "got here" << endl;
}

void Tetris::lowerCurrentTetromino() {
  cout << "lowe" << endl;
  bool canLower = true;
  for (int i = 0; i < widthOfCurrentTetromino; ++i) {
    int x = currentTetrominoPositions[i][0];
    int y = currentTetrominoPositions[i][1];
    if (x + 1 > ROWS + 2 or (canLower and board[x + 1][y] != NULL)) {
      canLower = false;
    }
  }
  if (canLower) {
    for (int i = 0; i < 4; ++i) {
      int x = currentTetrominoPositions[i][0]++;
      int y = currentTetrominoPositions[i][1];
      board[x + 1][y] = board[x][y];
      board[x][y] = NULL;
      board[x + 1][y]->sprite.move(0, SPRITE_WIDTH);
    }
  }
  else {
    cout << "can't lower" << endl;
    makeOPiece();
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
  widthOfCurrentTetromino = 1;
  currentTetrominoPositions[0] = {3, COLS / 2};
  currentTetrominoPositions[1] = {2, COLS / 2};
  currentTetrominoPositions[2] = {1, COLS / 2};
  currentTetrominoPositions[3] = {0, COLS / 2};
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
  widthOfCurrentTetromino = 2;
  currentTetrominoPositions[0] = {3, COLS / 2};
  currentTetrominoPositions[1] = {3, COLS / 2 + 1};
  currentTetrominoPositions[2] = {2, COLS / 2};
  currentTetrominoPositions[3] = {2, COLS / 2 + 1};
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
  widthOfCurrentTetromino = 2;
  currentTetrominoPositions[0] = {3, COLS / 2};
  currentTetrominoPositions[1] = {2, COLS / 2 + 1};
  currentTetrominoPositions[3] = {2, COLS / 2};
  currentTetrominoPositions[2] = {1, COLS / 2};
}

void Tetris::makeSPiece() {
  board[2][COLS / 2 + 1] = new Square;
  board[2][COLS / 2] = new Square;
  board[3][COLS / 2] = new Square;
  board[3][COLS / 2 - 1] = new Square;
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
  widthOfCurrentTetromino = 3;
  currentTetrominoPositions[0] = {3, COLS / 2};
  currentTetrominoPositions[1] = {3, COLS / 2 - 1};
  currentTetrominoPositions[2] = {2, COLS / 2 + 1};
  currentTetrominoPositions[3] = {2, COLS / 2};
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
  widthOfCurrentTetromino = 3;
  currentTetrominoPositions[0] = {2, COLS / 2};
  currentTetrominoPositions[1] = {3, COLS / 2 + 1};
  currentTetrominoPositions[2] = {3, COLS / 2 + 2};
  currentTetrominoPositions[3] = {2, COLS / 2 + 1};
}

void Tetris::makeJPiece() {
  board[1][COLS / 2] = new Square;
  board[2][COLS / 2] = new Square;
  board[3][COLS / 2] = new Square;
  board[3][COLS / 2 - 1] = new Square;
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
  widthOfCurrentTetromino = 2;
  currentTetrominoPositions[0] = {3, COLS / 2};
  currentTetrominoPositions[1] = {3, COLS / 2 - 1};
  currentTetrominoPositions[2] = {2, COLS / 2};
  currentTetrominoPositions[3] = {1, COLS / 2};
}

void Tetris::makeLPiece() {
  board[1][COLS / 2] = new Square;
  board[2][COLS / 2] = new Square;
  board[3][COLS / 2] = new Square;
  board[3][COLS / 2 + 1] = new Square;
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
  widthOfCurrentTetromino = 2;
  currentTetrominoPositions[0] = {3, COLS / 2};
  currentTetrominoPositions[1] = {3, COLS / 2 + 1};
  currentTetrominoPositions[2] = {2, COLS / 2};
  currentTetrominoPositions[3] = {1, COLS / 2};
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
