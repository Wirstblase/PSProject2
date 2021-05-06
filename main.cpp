
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
#include "player.cpp"
#include "map.cpp"

/*int main(int argc, char const** argv)
{
    // Create the main window
    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML window");

    // Set the Icon
    sf::Image icon;
    if (!icon.loadFromFile("40031.png")) {
        return EXIT_FAILURE;
    }
    window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());

    // Load a sprite to display
    sf::Texture texture;
    if (!texture.loadFromFile("ghost1.png")) {
        return EXIT_FAILURE;
    }
    sf::Sprite sprite(texture);

    // Create a graphical text to display
    sf::Font font;
    if (!font.loadFromFile("sansation.ttf")) {
        return EXIT_FAILURE;
    }
    sf::Text text("henlo wrlod", font, 100);
    text.setFillColor(sf::Color::Black);

    // Load a music to play
    sf::Music music;
    if (!music.openFromFile("Meadowsoundscapes.wav")) {
        return EXIT_FAILURE;
    }

    // Play the music
    music.play();
    
    Player player({ 40, 40 });
    player.setPos({ 50, 700 });
    
    std::vector<Coin*> coinVec;
    Coin coin1({ 20, 20 });
    Coin coin2({ 20, 20 });
    coinVec.push_back(&coin1);
    coinVec.push_back(&coin2);
    
    coin1.setPos({ 50, 600 });
    coin2.setPos({ 100, 600 });
    
    int coins = 0;
    
    sf::Font arial;
    arial.loadFromFile("sansation.ttf");
    
    //std::ostringstream ssScore;
    //ssScore << "Score: " << coins;
    
    sf::Text lblScore;
    lblScore.setCharacterSize(30);
    lblScore.setPosition({ 10, 10 });
    lblScore.setFont(arial);
    //lblScore.setString(ssScore.str());
    
    const int groundHeight = 700;
    const float gravitySpeed = 0.3;
    bool isJumping = false;

    // Start the game loop
    while (window.isOpen())
    {
        // Process events
        
        
        sf::Event event;
        while (window.pollEvent(event))
        {
            switch (event.type) {
                    
                case sf::Event::Closed:
                    window.close();
                    
                case sf::Event::KeyReleased:
                    if (event.key.code == sf::Keyboard::Up) {
                        isJumping = false;
                    }
            // Close window: exit
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            // Escape pressed: exit
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
                window.close();
            }
        }
        
        
        const float moveSpeed = 0.2;
        
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
            player.move({ 0, -moveSpeed });
            isJumping = true;
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
            player.move({ moveSpeed, 0 });
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
            player.move({ -moveSpeed, 0 });
        }
        
        if (player.getY() < groundHeight && isJumping == false) {
            player.move({ 0, gravitySpeed });
        }
        }
        

        // Clear screen
        window.clear();

        // Draw the sprite
        //window.draw(sprite);

        // Draw the string
        window.draw(text);

        // Update the window
        window.display();
    }

    return EXIT_SUCCESS;
}
*/

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
    
    // Play the music
    music.setLoop(true);
    //music.play();
    
    window.create(sf::VideoMode(900, 900), "gametest1", sf::Style::Titlebar | sf::Style::Close);
    window.setPosition(centerWindow);
    
    window.setKeyRepeatEnabled(true);
    
    //Player Object:
    Player player({ 40, 40 });
    player.setPos({ 50, 700 });
    
    Map map;
    
    sf::Texture playerTexture;
    if (!playerTexture.loadFromFile("ghost2.png")) {
        return EXIT_FAILURE;
    }
    //const sf::Texture *playerTexture2;
    player.playerSprite.setTexture(playerTexture);
    
    sf::Texture mapTexture;
    if (!mapTexture.loadFromFile("pixeltile1.png")) {
        return EXIT_FAILURE;
    } else std::cout<<"ground texture loaded\n";
    
    for(int aa=0;aa<16;aa++){
        for(int bb=0;bb<16;bb++){
            map.sprites[bb][aa].setTexture(mapTexture);
            //std::cout<<bb<<"-"<<aa<<" ";
        }
        //std::cout<<"\n";
    }
    
    //Coin Objects:
    std::vector<Coin*> coinVec;
    Coin coin1({ 20, 20 });
    Coin coin2({ 20, 20 });
    coinVec.push_back(&coin1);
    coinVec.push_back(&coin2);
    
    coin1.setPos({ 50, 600 });
    coin2.setPos({ 750, 600 });
    
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
    
    //Main Loop:
    while (window.isOpen()) {
        
        sf::Event Event;
        
        const float moveSpeed = 0.8;
        
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
            player.move({ 0, -moveSpeed });
            isJumping = true;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
            player.move({ 0, moveSpeed });
            //isJumping = true;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
            player.move({ moveSpeed, 0 });
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
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
        
        window.clear();
        map.drawTo(window);
        coin1.drawTo(window);
        window.draw(lblScore);
        coin2.drawTo(window);
        player.drawTo(window);
        
        window.display();
    }
}
