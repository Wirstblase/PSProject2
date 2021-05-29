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
    
    sf::RectangleShape itmSlBg1;
    sf::RectangleShape itmSlFg1;
    sf::Sprite itmSlSp1;
    
    sf::RectangleShape itmSlBg2;
    sf::RectangleShape itmSlFg2;
    sf::Sprite itmSlSp2;
    
    sf::RectangleShape itmSlBg3;
    sf::RectangleShape itmSlFg3;
    sf::Sprite itmSlSp3;
    
    int coins = 0;
    float damage = 0.0;
    float health = 3.0;
    
    int activeItem = 1; //1-3
    
    float movementSpeed = 0.5;
    
    int inventory[10];
    
    void initUI(sf::Font &arial,sf::Texture &coinTexture,sf::Texture &heartTexture){
        
        inventory[0] = 0;
        inventory[1] = 1;
        inventory[2] = 2;
        
        sf::Color color1;
        sf::Color color2;
        sf::Color color3;
        
        color3.b = 128;
        color3.r = 128;
        color3.g = 128;
        color3.a = 255;
        
        color2.b = 64;
        color2.r = 64;
        color2.g = 64;
        color2.a = 255;
        
        color1.b = 32;
        color1.r = 32;
        color1.g = 32;
        color1.a = 255;
        
        itmSlBg1.setFillColor(color2);
        itmSlBg1.setSize({40,40});
        itmSlBg1.setPosition({750,10});
        
        itmSlFg1.setFillColor(color3);
        itmSlFg1.setSize({34,34});
        itmSlFg1.setPosition({753,13});
        
        itmSlBg2.setFillColor(color2);
        itmSlBg2.setSize({40,40});
        itmSlBg2.setPosition({800,10});
        
        itmSlFg2.setFillColor(color3);
        itmSlFg2.setSize({34,34});
        itmSlFg2.setPosition({803,13});
        
        itmSlBg3.setFillColor(color2);
        itmSlBg3.setSize({40,40});
        itmSlBg3.setPosition({850,10});
        
        itmSlFg3.setFillColor(color3);
        itmSlFg3.setSize({34,34});
        itmSlFg3.setPosition({853,13});
        
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
        
        lblspd.setCharacterSize(30);
        lblspd.setPosition({250, 10});
        lblspd.setFont(arial);
        lblspd.setString(std::to_string(coins));
        
    }
    
    void updateCoinLabel(){
        
        lblScore.setString(std::to_string(coins));
        
    }
    
    void updateStats(){
        
        char healthFormatted[40],movementSpeedFormatted[40];
        
        snprintf(movementSpeedFormatted, 10, "%.1f", movementSpeed);
        snprintf(healthFormatted, 10, "%.1f", health);
        
        lblScore.setString(std::to_string(coins));
        lblHP.setString(healthFormatted);
        lblspd.setString(movementSpeedFormatted);
        
        sf::Color color2;
        sf::Color color3;
        
        color3.b = 128;
        color3.r = 128;
        color3.g = 128;
        color3.a = 255;
        
        color2.b = 64;
        color2.r = 64;
        color2.g = 64;
        color2.a = 255;
        
        if(activeItem == 1){
            itmSlBg1.setFillColor(color2);
            itmSlFg1.setFillColor(color3);
            itmSlBg2.setFillColor(color3);
            itmSlFg2.setFillColor(color2);
            itmSlBg3.setFillColor(color3);
            itmSlFg3.setFillColor(color2);
            
        } else if (activeItem == 2){
            itmSlBg1.setFillColor(color3);
            itmSlFg1.setFillColor(color2);
            itmSlBg2.setFillColor(color2);
            itmSlFg2.setFillColor(color3);
            itmSlBg3.setFillColor(color3);
            itmSlFg3.setFillColor(color2);
            
        } else if (activeItem == 3){
            itmSlBg1.setFillColor(color3);
            itmSlFg1.setFillColor(color2);
            itmSlBg2.setFillColor(color3);
            itmSlFg2.setFillColor(color2);
            itmSlBg3.setFillColor(color2);
            itmSlFg3.setFillColor(color3);
        }
        
    }
    
    void drawTo(sf::RenderWindow &window) {
        
        window.draw(bgbox);
        window.draw(bgbox1);
        window.draw(coinIcon);
        window.draw(lblScore);
        window.draw(lblHP);
        window.draw(heartIcon);
        window.draw(lblspd);
        window.draw(itmSlBg1);
        window.draw(itmSlFg1);
        window.draw(itmSlBg2);
        window.draw(itmSlFg2);
        window.draw(itmSlBg3);
        window.draw(itmSlFg3);
        //window.draw(lblHP);
        //window.draw(lblspd);
        
    }
    
    UI(){
        
        
        
    }
    
private:
};
