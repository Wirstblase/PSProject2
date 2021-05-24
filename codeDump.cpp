//
//  codeDump.cpp
//  sfmltest
//
//  Created by Suflea Marius on 07/05/2021.
//  Copyright © 2021 Suflea Marius. All rights reserved.
//


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
