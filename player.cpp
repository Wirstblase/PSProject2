//
//  player.cpp
//  sfmltest
//
//  Created by Suflea Marius on 28/04/2021.
//  Copyright © 2021 Suflea Marius. All rights reserved.
//

//#include "player.hpp"
#include <iostream>
#include <SFML/Graphics.hpp>
#include "coin.cpp"

//sf::Texture playerTexture;

class Player {
public:
    sf::Sprite playerSprite;
    Player(sf::Vector2f size) {
        player.setSize(size);
        player.setFillColor(sf::Color::Transparent);
        
        /*sf::Texture playerTexture;
        if (!playerTexture.loadFromFile("ghost1.png")) {
                return EXIT_FAILURE;
            }
        //const sf::Texture *playerTexture2;
        playerSprite.setTexture(playerTexture);*/
        //playerSprite.setTextureRect(sf::IntRect(10, 10, 32, 32));
        playerSprite.setScale(sf::Vector2f(0.2f, 0.2f));
        //playerSprite.move(sf::Vector2f(5.0f, 1.1f));
        
        //player.setTexture(playerTexture2);
        
    }
    
    void drawTo(sf::RenderWindow &window) {
        //sf::Texture playerTexture;
        //if (!playerTexture.loadFromFile("ghost1.png")) {
        //    return EXIT_FAILURE;
        //}
        //playerSprite.setTexture(playerTexture);
        window.draw(player);
        window.draw(playerSprite);
    }
    
    void move(sf::Vector2f distance) {
        player.move(distance);
        playerSprite.move(distance);
    }
    
    void setPos(sf::Vector2f newPos) {
        player.setPosition(newPos);
        //playerSprite.setOrigin(sf::Vector2f(newPos) - sf::Vector2f({35,22}));
        playerSprite.setPosition(newPos /*- sf::Vector2f({35,22})*/); // spawning ghost with offset
    }
    
    int getY() {
        return player.getPosition().y;
    }
    
    bool isCollidingWithCoin(Coin *coin) {
        if (player.getGlobalBounds().intersects(coin->getGlobalBounds())) {
            return true;
        }
        return false;
    }
private:
    //sf::Sprite player;
    sf::RectangleShape player;
};
