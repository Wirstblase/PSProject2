
//
// Disclaimer:
// ----------
//
// This code will work only if you selected window, graphics and audio.
//
// In order to load the resources like cute_image.png, you have to set up
// your target scheme:
//
// - Select "Edit Scheme…" in the "Product" menu;
// - Check the box "use custom working directory";
// - Fill the text field with the folder path containing your resources;
//        (e.g. your project folder)
// - Click OK.
//

#include <iostream>
#include <cstdlib>
#include <string.h>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

//#include "coin.cpp"
//#include "door.cpp"
#include "player.cpp"
#include "map.cpp"
//#include "itemGrid.cpp"

#include <fstream>

int main() {
    sf::RenderWindow window;
    
    sf::Vector2i centerWindow((sf::VideoMode::getDesktopMode().width / 2) - 445, (sf::VideoMode::getDesktopMode().height / 2) - 480);
    
    // Load a music to play
    sf::Music music;
    if (!music.openFromFile("Meadowsoundscapes.wav")) {
        return EXIT_FAILURE;
    }
    
    sf::Music coinPickupSfx;
    if (!coinPickupSfx.openFromFile("coinpickup.ogg")) {
        return EXIT_FAILURE;
    }
    
    sf::Music doorCloseSfx;
    if (!doorCloseSfx.openFromFile("close_door_1.wav")) {
        return EXIT_FAILURE;
    }
    
    // Play the music
    music.setLoop(true);
    //music.play();
    
    window.create(sf::VideoMode(900, 900), "gametest1", sf::Style::Titlebar | sf::Style::Close);
    window.setPosition(centerWindow);
    
    window.setKeyRepeatEnabled(true);
    
    //Player Object:
    Player player({ 40, 90 });
    player.setPos({ 50, 700 });
    player.playerSpriteOffset({-10,0});
    //dplayer.playerSpriteScale({-1.0,1.0});
    
    Map map;
    
    sf::Texture playerTexture;
    if (!playerTexture.loadFromFile("penguin.png")) {
        return EXIT_FAILURE;
    }
    //const sf::Texture *playerTexture2;
    player.playerSprite.setTexture(playerTexture);
    
    sf::Texture emptyTex;
    if (!emptyTex.loadFromFile("emptyTex.png")) {
        return EXIT_FAILURE;
    }
    sf::Texture doorHaloTexture;
    if (!doorHaloTexture.loadFromFile("doorhalo.png")) {
        return EXIT_FAILURE;
    }
    
    sf::Texture mapTexture;
    sf::Texture groundTexture1;
    sf::Texture groundTexture2;
    
    if (!mapTexture.loadFromFile("pixeltile1.png")) {
        return EXIT_FAILURE;
    } else std::cout<<"mapTexture loaded\n";
    if (!groundTexture1.loadFromFile("pixeltile1.png")) {
        return EXIT_FAILURE;
    } else std::cout<<"ground texture 1 loaded\n";
    if (!groundTexture2.loadFromFile("pixeltile2.png")) {
        return EXIT_FAILURE;
    } else std::cout<<"ground texture 2 loaded\n";
    
    //std::string myText;
    
    
    //Door objects
    
    std::vector<Door*> doorVec;
    Door door1({120,60});
    Door door2({120,60});
    Door door3({120,60});
    Door door4({120,60});
    
    door1.doorHaloSprite.setTexture(doorHaloTexture);
    door2.doorHaloSprite.setTexture(doorHaloTexture);
    door3.doorHaloSprite.setTexture(doorHaloTexture);
    door4.doorHaloSprite.setTexture(doorHaloTexture);
    
    doorVec.push_back(&door1);
    doorVec.push_back(&door2);
    doorVec.push_back(&door3);
    doorVec.push_back(&door4);
    
    door1.doorName = 1;
    door2.doorName = 2;
    door3.doorName = 3;
    door4.doorName = 4;
    
    door1.setPos({-60,530});
    door2.setPos({400,0});
    door3.setPos({960,400});
    door4.setPos({500,960});
    
    door1.doorHaloSpriteOffset({60,30});
    door2.doorHaloSpriteOffset({-30,60});
    door3.doorHaloSpriteOffset({-60,-30});
    door4.doorHaloSpriteOffset({30,-60});
    
    door1.setRot(-90);
    door2.setRot(0);
    door3.setRot(90);
    door4.setRot(180);
    
    int shouldLoadLevel = 1;
    int fileLoadValue = 0;
    
    //Coin Objects:
    
    std::vector<Coin*> coinVec;
    /*Coin coin1({ 20, 20 });
    Coin coin2({ 20, 20 });
    coinVec.push_back(&coin1);
    coinVec.push_back(&coin2);
    
    coin1.setPos({ 50, 600 });
    coin2.setPos({ 750, 600 });*/
    
    //Score Objects:
    
    int coins = 0;
    
    sf::Font arial;
    arial.loadFromFile("sansation.ttf");
    
    //std::ostringstream ssScore;
    //ssScore << "Score: " << coins;
    
    sf::Text lblScore;
    lblScore.setCharacterSize(30);
    lblScore.setPosition({ 10, 10 });
    lblScore.setFont(arial);
    lblScore.setString("0");
    //lblScore.setString(ssScore.str());
    
    //Gravity Variables:
    const int groundHeight = 700;
    const float gravitySpeed = 0.3;
    bool isJumping = false;
    
    std::cout<<"BEFORE LOOP\n";
    
    //Main Loop:
    while (window.isOpen()) {
        
        if(shouldLoadLevel == 1){
        
        char loadFile[20];
        snprintf(loadFile, 10, "%d.txt", fileLoadValue);
        
        std::ifstream MyReadFile(loadFile);
        
        MyReadFile>>door1.leadsTo;
        MyReadFile>>door2.leadsTo;
        MyReadFile>>door3.leadsTo;
        MyReadFile>>door4.leadsTo;
            
            
        //doors enabling or disabling logic
            
            if(door1.leadsTo == 99){
                door1.isEnabled = false;
                door1.doorHaloSprite.setTexture(emptyTex);
            } else
            {
                door1.isEnabled = true;
                door1.doorHaloSprite.setTexture(doorHaloTexture);
            }
            if(door2.leadsTo == 99){
                door2.isEnabled = false;
                door2.doorHaloSprite.setTexture(emptyTex);
            } else
            {
                door2.isEnabled = true;
                door2.doorHaloSprite.setTexture(doorHaloTexture);
            }
            if(door3.leadsTo == 99){
                door3.isEnabled = false;
                door3.doorHaloSprite.setTexture(emptyTex);
            } else
            {
                door3.isEnabled = true;
                door3.doorHaloSprite.setTexture(doorHaloTexture);
            }
            if(door4.leadsTo == 99){
                door4.isEnabled = false;
                door4.doorHaloSprite.setTexture(emptyTex);
            } else
            {
                door4.isEnabled = true;
                door4.doorHaloSprite.setTexture(doorHaloTexture);
            }
            
        //end doors enabling or disabling logic
        
        int texVec[256],n=256;
        for(int i=0;i<=256;i++){
            MyReadFile >> texVec[i];
            std::cout << texVec[i] << " ";
        }
        
        int i=0;
        for(int aa=0;aa<16;aa++){
            for(int bb=0;bb<16;bb++){
                
                if(texVec[i] == 1){
                    map.sprites[bb][aa].setTexture(groundTexture1);
                } else if(texVec[i] == 2){
                    map.sprites[bb][aa].setTexture(groundTexture2);
                }
                
                i++;
            }
        }
        
        MyReadFile.close();
        shouldLoadLevel = 0;
        }
        
        
        sf::Event Event;
        
        const float moveSpeed = 0.4;
        
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
            player.move({ 0, -moveSpeed });
            isJumping = true;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
            player.move({ 0, moveSpeed });
            //isJumping = true;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
            
            if(player.facing == 1){
                player.playerSpriteScale({1.0,1.0});
                player.playerSpriteOffset({-10,0});
                player.facing = 0;
            }
            player.move({ moveSpeed, 0 });
        
            
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
            
            if(player.facing == 0){
                player.playerSpriteScale({-1.0,1.0});
                player.playerSpriteOffset({50,0});
                player.facing = 1;
            }
            player.move({ -moveSpeed, 0 });
            
        }
        
        //Event Loop:
        while (window.pollEvent(Event)) {
            switch (Event.type) {
                    
                case sf::Event::Closed:
                    window.close();
                    
                case sf::Event::KeyReleased:
                    isJumping = false;
            }
        }
        
        //bounds logic
        if(player.getY() < 59){
            player.move({0, 1});
        }
        if(player.getX() < -1){
            player.move({1,0});
        }
        if(player.getX() > 860){
            player.move({-1,0});
        }
        if(player.getY() > 860){
            player.move({0,-1});
        }
        //end bounds logic
        
        //Gravity Logic:
        /*if (player.getY() < groundHeight && isJumping == false) {
            player.move({ 0, gravitySpeed });
        }*/
        /*if (player.getY() > 300 && isJumping == true) {
            player.move({ 0, -gravitySpeed });
        }*/
        
        //Coin Logic:
        for (int i = 0; i < coinVec.size(); i++) {
            if (player.isCollidingWithCoin(coinVec[i])) {
                
                
                coinPickupSfx.stop();
                coinPickupSfx.play();
                
                coinVec[i]->setPos({ 422234, 423432 });
                coins++;
                lblScore.setString(std::to_string(coins));
                std::cout<<"coins:"<<coins<<"\n";
            }
            
        }
        
        //door logic
        
        for (int i = 0; i < doorVec.size(); i++) {
            if (player.isCollidingWithDoor(doorVec[i])) {
                
                //if(collideOnce == 0){
                if(player.collideCooldown > 100){
                    
                    if(doorVec[i]->leadsTo != 99){
                        fileLoadValue = doorVec[i]->leadsTo;
                        shouldLoadLevel = 1;
                    }
                    
                    if(i == 0){
                        player.setPos({800,400});
                        
                        player.playerSpriteOffset({50,0});
                        player.playerSpriteScale({-1.0,1.0});
                        
                    } else if(i == 1){
                        player.setPos({400,750});
                        
                        player.playerSpriteOffset({-10,0});
                        player.playerSpriteScale({1.0,1.0});
                        
                        
                    } else if(i == 2){
                        player.setPos({5,450});
                        
                        player.playerSpriteOffset({-10,0});
                        player.playerSpriteScale({1.0,1.0});
                        
                        
                    } else if(i == 3){
                        player.setPos({400,100});
                        
                        player.playerSpriteOffset({-10,0});
                        player.playerSpriteScale({1.0,1.0});
                        
                        
                    }
                    
                    
                    
                    doorCloseSfx.stop();
                    doorCloseSfx.play();
                    player.collideCooldown = 0;
                }
                //    collideOnce = 1;
                //}
                
                //coinVec[i]->setPos({ 422234, 423432 });
                //coins++;
                //lblScore.setString(std::to_string(coins));
                //std::cout<<"coins:"<<coins<<"\n";
            } else if(player.isCollidingWithDoor(doorVec[i]) == false) {
                //collideOnce = 0;
            }
            
        }
        
        //end door logica
        
        window.clear();
        map.drawTo(window);
        //coin1.drawTo(window);
        window.draw(lblScore);
        //coin2.drawTo(window);
        player.drawTo(window);
        
        door1.drawTo(window);
        door2.drawTo(window);
        door3.drawTo(window);
        door4.drawTo(window);
        
        window.display();
    }
}
