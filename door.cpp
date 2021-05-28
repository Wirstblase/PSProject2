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
    sf::Sprite doorHaloSprite;
    
    int doorName = 0;
    int leadsTo = 0;
    int isEnabled = 1;
    
    Door(sf::Vector2f size) {
        door.setSize(size);
        doorHaloSprite.setScale(5.0, 5.0);
        door.setFillColor(sf::Color::Transparent);
    }
    
    void setRot(float rotation){
        
        door.setRotation(rotation);
        doorHaloSprite.setRotation(rotation);
        
    }
    
    void drawTo(sf::RenderWindow &window) {
        window.draw(door);
        window.draw(doorHaloSprite);
    }
    
    sf::FloatRect getGlobalBounds() {
        return door.getGlobalBounds();
    }
    
    void doorHaloSpriteOffset(sf::Vector2f offset){
        sf::Vector2f pos = doorHaloSprite.getPosition();
        doorHaloSprite.setPosition(offset + pos);
    }
    
    void setPos(sf::Vector2f newPos) {
        door.setPosition(newPos);
        doorHaloSprite.setPosition(newPos /*- sf::Vector2f(30,-60)*/);
    }
private:
    sf::RectangleShape door;
};
