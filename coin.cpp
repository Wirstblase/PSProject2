//
//  coin.cpp
//  sfmltest
//
//  Created by Suflea Marius on 28/04/2021.
//  Copyright © 2021 Suflea Marius. All rights reserved.
//

//#include "coin.hpp"

#include <iostream>
#include <SFML/Graphics.hpp>

class Coin {
public:
    Coin(sf::Vector2f size) {
        coin.setSize(size);
        coin.setFillColor(sf::Color::Yellow);
    }
    void drawTo(sf::RenderWindow &window) {
        window.draw(coin);
    }
    sf::FloatRect getGlobalBounds() {
        return coin.getGlobalBounds();
    }
    void setPos(sf::Vector2f newPos) {
        coin.setPosition(newPos);
    }
private:
    sf::RectangleShape coin;
};
