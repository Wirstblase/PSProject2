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
#include "door.cpp"
#include "itemGrid.cpp"

//sf::Texture playerTexture;

class Player {
public:
    int facing = 0; //0-stanga, 1-drepta
    int collideCooldown = 0;
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
        playerSprite.setScale(sf::Vector2f(1.0f, 1.0f));
        //playerSprite.move(sf::Vector2f(5.0f, 1.1f));
        
        //player.setTexture(playerTexture2);
        
    }
    
    void playerSpriteScale(sf::Vector2f scale){
        playerSprite.setScale(scale);
    }
    
    void playerSpriteOffset(sf::Vector2f offset){
        sf::Vector2f pos = player.getPosition();
        //playerSprite.move(pos + offset);
        playerSprite.setPosition(pos + offset);
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
    int getX(){
        return player.getPosition().x;
    }
    
    bool isCollidingWithCoin(Coin *coin) {
        if (player.getGlobalBounds().intersects(coin->getGlobalBounds())) {
            return true;
        }
        return false;
    }
    
    bool isCollidingWithDoor(Door *door) {
        if (player.getGlobalBounds().intersects(door->getGlobalBounds())) {
            collideCooldown++;
            return true;
        }
        return false;
    }
    /*bool isCollidingWithItem(Item *item) {
        if (player.getGlobalBounds().intersects(item->getGlobalBounds())) {
            return true;
        }
        return false;
    }*/
private:
    //sf::Sprite player;
    int collideOnce = 1;
    sf::RectangleShape player;
};
