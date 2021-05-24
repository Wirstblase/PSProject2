//
//  door.cpp
//  sfmltest
//
//  Created by Suflea Marius on 24/05/2021.
//  Copyright © 2021 Suflea Marius. All rights reserved.
//

//#include <stdio.h>
#include <iostream>
#include <SFML/Graphics.hpp>

class Door {
public:
    int doorName = 0;
    int leadsTo = 0;
    Door(sf::Vector2f size) {
        door.setSize(size);
        door.setFillColor(sf::Color::White);
    }
    void drawTo(sf::RenderWindow &window) {
        window.draw(door);
    }
    sf::FloatRect getGlobalBounds() {
        return door.getGlobalBounds();
    }
    void setPos(sf::Vector2f newPos) {
        door.setPosition(newPos);
    }
private:
    sf::RectangleShape door;
};
