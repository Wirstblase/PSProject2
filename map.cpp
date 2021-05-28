//
//  map.cpp
//  sfmltest
//
//  Created by Suflea Marius on 28/04/2021.
//  Copyright © 2021 Suflea Marius. All rights reserved.
//
#include <math.h>
#include <iostream>
#include <SFML/Graphics.hpp>

class Map{
public:
    
    //
    sf::Sprite sprites[16][16];
    
    sf::RectangleShape collRect[16][16];
    
    int grid[16][16]; //1-grass 2-wall 3-stone
    
    Map(){
        
    }
    
    Map(sf::Vector2f size) {
        map.setSize(size);
        map.setFillColor(sf::Color::Yellow);
    }
    
    void setPos(sf::Vector2f newPos) {
        item.setPosition(newPos);
    }
    
    void drawTo(sf::RenderWindow &window) {
        
        //for(int i=1;i<=1000;i++){
            //window.draw
        //}
            
        //window.draw(coin);
        dot.setSize(sf::Vector2f({60,60}));
        dot.setFillColor(sf::Color::Black);
        //dot.setOutlineColor(sf::Color::Transparent);
        //dot.setOutlineThickness(2.f);
        
        for(int i=0; i<16;i++){
            for(int j=0; j<16;j++){
                //if(i%2 == 0)
                    dot.setPosition(j*distance+xoffset, i*height+yoffset);
                
                    collRect[j][i].setFillColor(sf::Color::Transparent);
                    collRect[j][i].setPosition(j*distance+xoffset, i*height+yoffset);
                    //sprites[j][i].setScale(sf::Vector2f(4.0f, 4.0f));
                    collRect[j][i].setSize({50,50});
                
                    sprites[j][i].setPosition(j*distance+xoffset, i*height+yoffset);
                    sprites[j][i].setScale(sf::Vector2f(4.0f, 4.0f));
                
                window.draw(dot);
                window.draw(sprites[j][i]);
                //window.draw(collRect[j][i]);
            }
        }
        
        /*for (int i=0; i<nofRows; ++i){
            for (int j=0; j<nofCols; ++j){
                if (i%2==0) dot().setPosition(j*distance, i*height); //even rows
                else dot().setPosition(j*distance+offset, i*height); //odd rows
                window.draw(dot());
            }
        }*/
    }
    sf::FloatRect getGlobalBounds() {
        return map.getGlobalBounds();
    }
    
    void loadItems() {
        int m=1000;int n=1000;
        
        sf::Vector2f newPosition = sf::Vector2f({0.0,0.0});
        
        for(int i=1;i<=n;i++){
            for(int j=1;j<=n;i++){
                
                if(grid[i][j] == 2){
                    
                }
                
            }
        }
    }

private:
    const int distance = 60; //distance between dots
    const float offset = distance/2.f; //offset for odd rows
    const float xoffset = 1.f;
    const float yoffset = 60.f;
    const float height = sqrt(pow(distance,2.f) - pow(offset,2.f));
    //
    sf::RectangleShape map;
    sf::RectangleShape item;
    sf::RectangleShape dot;
    
    
};
