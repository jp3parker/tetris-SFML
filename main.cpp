
#include "main.h"

int main(int argc, char* argv[]) {
  sf::RenderWindow window(sf::VideoMode(600, 1200), "SFML works!");
  window.setFramerateLimit(30);
  
  std::string FailureToLoadError = "";
  
  sf::Texture BackgroundTexture;
  if (!BackgroundTexture.loadFromFile("images/tetris-background.png")) {
    FailureToLoadError += "Could not load tetris-background.png\n";
  }
  
  if (FailureToLoadError == "") { // everything loaded successfully
    sf::Sprite Background;
    Background.setTexture(BackgroundTexture);
  
    while (window.isOpen()) {
      sf::Event event;
      while (window.pollEvent(event))
      {
        if (event.type == sf::Event::Closed)
          window.close();
      }
      
      window.clear();
      window.draw(Background);
      window.display();
    }
  }
  else { // at least one image failed to load
    std::cout << FailureToLoadError << std::endl;
  }
  
  return 0;
}
