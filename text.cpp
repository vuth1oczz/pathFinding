#include "text.h"
sf::Font font;
void huong_dan (sf::Text& text) {
    if (!font.loadFromFile("Bebas-Regular.ttf")) {
        std::cout << "Error load file";
    }
    text.setFont(font);
    text.setString("Huong dan...");
    text.setPosition(sf::Vector2f(420, 0));
    text.setFillColor(sf::Color::Green);
    text.setOutlineColor(sf::Color::Black);
    text.setOutlineThickness(2);
    text.setCharacterSize(25);
}