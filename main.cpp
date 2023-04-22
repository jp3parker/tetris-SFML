
#include "main.h"

int main(int argc, char* argv[]) {
  sf::RenderWindow window(sf::VideoMode(600, 1200), "SFML works!");
  window.setFramerateLimit(30);
  
  std::string FailureToLoadError = "";
  
  sf::Texture BackgroundTexture;
  if (!BackgroundTexture.loadFromFile("images/tetris-background.png")) {
    FailureToLoadError += "Could not load images/tetris-background.png\n";
  }
  sf::Texture YellowTexture;
  if (!YellowTexture.loadFromFile("images/yellow-square.png")) {
    FailureToLoadError += "Could not load images/yellow-square.png\n";
  }
  sf::Texture RedTexture;
  if (!RedTexture.loadFromFile("images/red-square.png")) {
    FailureToLoadError += "Could not load images/red-square.png\n";
  }
  sf::Texture PurpleTexture;
  if (!PurpleTexture.loadFromFile("images/purple-square.png")) {
    FailureToLoadError += "Could not load images/purple-square.png\n";
  }
  sf::Texture OrangeTexture;
  if (!OrangeTexture.loadFromFile("images/orange-square.png")) {
    FailureToLoadError += "Could not load images/orange-square.png\n";
  }
  sf::Texture LightBlueTexture;
  if (!LightBlueTexture.loadFromFile("images/light-blue-square.png")) {
    FailureToLoadError += "Could not load images/light-blue-square.png\n";
  }
  sf::Texture GreenTexture;
  if (!GreenTexture.loadFromFile("images/green-square.png")) {
    FailureToLoadError += "Could not load images/green-square.png\n";
  }
  sf::Texture DarkBlueTexture;
  if (!DarkBlueTexture.loadFromFile("images/dark-blue-square.png")) {
    FailureToLoadError += "Could not load images/dark-blue-square.png\n";
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
