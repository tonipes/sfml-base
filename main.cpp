#include <SFML/Graphics.hpp>

int main() {
    sf::RenderWindow window(sf::VideoMode(640, 480, 32), "Tere!");
    sf::Font font;
    font.loadFromFile("../OpenSans-Bold.ttf");
    sf::Text text("Tere!", font, 11);

    text.setFillColor(sf::Color::Black);
    text.setCharacterSize(64);
    text.setPosition(window.getSize().x/2 - text.getGlobalBounds().width/2,
                     window.getSize().y/2 - text.getGlobalBounds().height/2);

    while(window.isOpen()){

        sf::Event event;
        while(window.pollEvent(event)) {
            if(event.type == sf::Event::Closed){
                window.close();
            }

            window.clear(sf::Color::Blue);
            window.draw(text);
            window.display();
        }
    }
    return 0;
}