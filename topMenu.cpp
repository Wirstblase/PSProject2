//
//  topMenu.cpp
//  sfmltest
//
//  Created by Suflea Marius on 28/05/2021.
//  Copyright © 2021 Suflea Marius. All rights reserved.
//

//#include <stdio.h>
#include <iostream>
#include <SFML/Graphics.hpp>

class UI{
public:
    
    sf::Sprite coinIcon;
    sf::Sprite heartIcon;
    
    sf::Text lblScore;
    sf::Text lblHP;
    sf::Text lblspd;
    
    sf::RectangleShape bgbox;
    sf::RectangleShape bgbox1;
    
    int coins = 10;
    float damage = 0.0;
    float health = 3.0;
    
    float movementSpeed = 0.5;
    
    int inventory[10];
    
    void initUI(sf::Font &arial,sf::Texture &coinTexture,sf::Texture &heartTexture){
        
        inventory[0] = 0;
        inventory[1] = 1;
        inventory[2] = 2;
        
        sf::Color color1;
        sf::Color color2;
        
        color2.b = 64;
        color2.r = 64;
        color2.g = 64;
        color2.a = 255;
        
        color1.b = 32;
        color1.r = 32;
        color1.g = 32;
        color1.a = 255;
        
        bgbox.setSize({900,59});
        bgbox.setFillColor(color2);
        
        bgbox1.setPosition({5,5});
        bgbox1.setSize({890,48});
        bgbox1.setFillColor(color1);
        
        //sf::Text lblScore;
        lblScore.setCharacterSize(30);
        lblScore.setPosition({ 50, 10 });
        lblScore.setFont(arial);
        lblScore.setString("0");
        
        lblHP.setCharacterSize(30);
        lblHP.setPosition({150, 10});
        lblHP.setFont(arial);
        lblHP.setString("3.0");
        
        coinIcon.setTexture(coinTexture);
        coinIcon.setPosition({5,5});
        coinIcon.setScale({3.0,3.0});
        
        heartIcon.setTexture(heartTexture);
        heartIcon.setPosition({100,5});
        heartIcon.setScale({3.0,3.0});
        
    }
    
    void updateCoinLabel(){
        
        lblScore.setString(std::to_string(coins+1));
        
    }
    
    void updateStats(){
        
        
        
    }
    
    void drawTo(sf::RenderWindow &window) {
        
        window.draw(bgbox);
        window.draw(bgbox1);
        window.draw(coinIcon);
        window.draw(lblScore);
        window.draw(lblHP);
        window.draw(heartIcon);
        //window.draw(lblHP);
        //window.draw(lblspd);
        
    }
    
    UI(){
        
        
        
    }
    
private:
};
