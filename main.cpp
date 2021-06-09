
#include <iostream>
#include <cstdlib>
#include <string.h>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

//#include "coin.cpp"
//#include "door.cpp"
#include "player.cpp"
#include "map.cpp"
#include "particleTest.cpp"
#include "topMenu.cpp"
//#include "itemGrid.cpp"

#include <fstream>



#include <cmath>

class Enemy {
public:
    
    sf::RectangleShape enemy;
    
    int facing = 0; //0-stanga, 1-drepta
    sf::Sprite enemySprite;
    
    float WONDERING_SPEED = .2;
    float ATTACK_SPEED = 0.5;
    int ATTACK_IF_CLOSER_THAN = 100;
    int LOSE_INTEREST_AT = 100;
    
    int DAMAGE_AT = 10;
    bool target = false;
    float DAMAGE = .5f;
    float hasAttacked = false;
    
    sf::Vector2f wonderTo = {-1, -1};
    int first = 0;
    
    sf::Vector2f velocity = {0, 0};
    sf::Vector2f acceleration = {0, 0};
    
    Enemy(sf::Vector2f size, sf::Texture &texture) { // Enemy(position)
        enemy.setSize(size);
        enemy.setFillColor(sf::Color::Transparent);
        
        enemySprite.setScale(sf::Vector2f(3.0f, 3.0f));
        enemySprite.setTexture(texture);
    }
    
    /*~Enemy(){
        
    }
    
    void destruct() {
        delete[] this -> enemy;
        
    }*/
    
    void playerSpriteScale(sf::Vector2f scale) {
        enemySprite.setScale(scale);
    }
    
    void playerSpriteOffset(sf::Vector2f offset) {
        sf::Vector2f pos = enemy.getPosition();
        
        enemySprite.setPosition(pos + offset);
    }
    
    void drawTo(sf::RenderWindow &window) {
        window.draw(enemy);
        window.draw(enemySprite);
    }
    
    void move(sf::Vector2f distance) {
        enemy.move(distance);
        enemySprite.move(distance);
    }
    
    void setPos(sf::Vector2f newPos) {
        enemy.setPosition(newPos);
        enemySprite.setPosition(newPos /*- sf::Vector2f({35,22})*/); // spawning ghost with offset
    }
    
    void testFor(UI& ui, Player &player) {
        //if (disabled) return;
        if (distance(player) < ATTACK_IF_CLOSER_THAN && distance(player) > 10) {
            target = true;
        } else if (target && (distance(player) > LOSE_INTEREST_AT || distance(player) < 10) ) {
            target = false;
        }
        
        if (distance(player) <= DAMAGE_AT && !hasAttacked){
            ui.health -= DAMAGE;
            target = false;
            hasAttacked = true;
            
            // enable / disable based on ghost AI type -> comment the while for basic, uncomment for advanced
            while (distance(wonderTo) < 100){
                wonderTo = getRandomLocation();
            }
            //
        }
        
        if (wonderTo.x < 0 || wonderTo.y < 0) {
            wonderTo = getRandomLocation();
        }
        if (distance(wonderTo.x, wonderTo.y, getX(), getY()) < 10) {
            wonderTo = getRandomLocation();
        }
        
        update(player);
    }
    
    void update(Player &player) {
        sf::Vector2f dir;
        if (target && !hasAttacked) {
            dir = player.player.getPosition() - enemy.getPosition();
        } else {
            dir = wonderTo - enemy.getPosition();
        }
        
        dir = normalize(dir) * 0.5f;
        acceleration = dir;
        velocity += acceleration;
        velocity = limit(velocity, target ? ATTACK_SPEED : WONDERING_SPEED);
        setPos(enemy.getPosition() + velocity);
    }
    
    sf::Vector2f limit(sf::Vector2f &source, float max) {
        float n = sqrt(source.x * source.x + source.y * source.y);
        float f = std::min(n, max) / n;
        return source * f;
    }
    
    sf::Vector2f normalize(sf::Vector2f &source) {
        float length = sqrt((source.x * source.x) + (source.y * source.y));
        if (length != 0)
            return sf::Vector2f(source.x / length, source.y / length);
        else
            return source;
    }
    
    sf::Vector2f getRandomLocation() {
        hasAttacked = false;
        return {static_cast<float>(std::rand() % 900), static_cast<float>(std::rand() % 900)};
    }
    
    float distance(int x1, int y1, int x2, int y2) {
        return sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2) * 1.0);
    }
    
    float distance(Player player) {
        return sqrt(pow(getX() - player.getX(), 2) + pow(getY() - player.getY(), 2) * 1.0);
    }
    
    int getY() {
        return enemy.getPosition().y;
    }
    
    int getX() {
        return enemy.getPosition().x;
    }
    
    bool isCollidingPlayer(Player &player) {
        if (enemy.getGlobalBounds().intersects(player.player.getGlobalBounds())) {
            return true;
        }
        return false;
    }
};
int shouldSpawnGhosts = 0;


int itmVec[256];

int autosave = 1;

void loadPlayerStats(UI &ui, Player &player){
    std::ifstream MyStatReadFile("playerstats.txt");
    
    MyStatReadFile >> ui.coins;
    MyStatReadFile >> ui.damage;
    MyStatReadFile >> ui.health;
    MyStatReadFile >> ui.movementSpeed;
    MyStatReadFile >> ui.inventory[0];
    MyStatReadFile >> ui.inventory[1];
    MyStatReadFile >> ui.inventory[2];
    
    player.activeItem = ui.inventory[0];
    player.shouldUpdateItem = 1;
    
    //ui.updateStats();
    //ui.updateCoinLabel();
    
    MyStatReadFile.close();
    
}

void savePlayerStats(UI &ui, Player &player){
    
    std::ofstream myStatWriteFile("playerstats.txt");
    
    myStatWriteFile << ui.coins;
    myStatWriteFile << "\n";
    myStatWriteFile << ui.damage;
    myStatWriteFile << "\n";
    myStatWriteFile << ui.health;
    myStatWriteFile << "\n";
    myStatWriteFile << ui.movementSpeed;
    myStatWriteFile << "\n";
    myStatWriteFile << ui.inventory[0];
    myStatWriteFile << "\n";
    myStatWriteFile << ui.inventory[1];
    myStatWriteFile << "\n";
    myStatWriteFile << ui.inventory[2];
    myStatWriteFile << "\n";
    
    myStatWriteFile.close();
    
}

void saveFile(int fileLoadValue){
    
    char loadItemFile[20];
    snprintf(loadItemFile, 10, "itm%d.txt", fileLoadValue);
    
    std::ofstream MyItemWriteFile(loadItemFile);
    
    for (int i=0;i<=255;i++)
    {
        char thing[10];
        snprintf(thing, 10, "%d" ,itmVec[i]);
        MyItemWriteFile << thing;
        MyItemWriteFile << " ";
        if(i%16 == 0)
        MyItemWriteFile << "\n";
    }
    
    MyItemWriteFile.close();
    
}

int main() {
    sf::RenderWindow window;
    
    sf::Vector2i centerWindow((sf::VideoMode::getDesktopMode().width / 2) - 445, (sf::VideoMode::getDesktopMode().height / 2) - 480);
    
    // Load a music to play
    sf::Music music;
    if (!music.openFromFile("bgdrone.wav")) {
        return EXIT_FAILURE;
    }
    
    sf::Music itemPickupSfx;
    if (!itemPickupSfx.openFromFile("harp1.wav")) {
        return EXIT_FAILURE;
    }
    
    sf::Music coinPickupSfx;
    if (!coinPickupSfx.openFromFile("coinpickup1fixed.wav")) {
        return EXIT_FAILURE;
    }
    
    sf::Music doorCloseSfx;
    if (!doorCloseSfx.openFromFile("close_door_1fixedfaster.wav")) {
        return EXIT_FAILURE;
    }
    
    // Play the music
    music.setLoop(true);
    music.play();
    
    window.create(sf::VideoMode(900, 900), "gametest1", sf::Style::Titlebar | sf::Style::Close /*sf::Style::Fullscreen*/);
    window.setPosition(centerWindow);
    
    window.setKeyRepeatEnabled(true);
    
    //Player Object:
    Player player({ 40, 90 });
    player.setPos({ 425, 400 });
    player.playerSpriteOffset({-10,0});
    //dplayer.playerSpriteScale({-1.0,1.0});
    
    itemGrid itemgrid;
    Map map;
    UI ui;
    
    // Enemy init
    std::vector <Enemy> enemies;
    srand(time(0));
    int ENEMIES = 5;
    
    
    sf::Font arial;
    if(!arial.loadFromFile("sansation.ttf")){
        return EXIT_FAILURE;
    }
    
    sf::Texture playerTexture;
    if (!playerTexture.loadFromFile("penguin.png")) {
        return EXIT_FAILURE;
    }
    //const sf::Texture *playerTexture2;
    
    player.playerSprite.setTexture(playerTexture);
    
    sf::Texture enemyTexture1;
    if (!enemyTexture1.loadFromFile("ghost3.png")) return EXIT_FAILURE;
    
    sf::Texture enemyTexture2;
    if (!enemyTexture2.loadFromFile("ghost4.png")) return EXIT_FAILURE;
    
    sf::Texture emptyTex;
    if (!emptyTex.loadFromFile("emptyTex.png")) {
        return EXIT_FAILURE;
    }
    sf::Texture doorHaloTexture;
    if (!doorHaloTexture.loadFromFile("doorhalo.png")) {
        return EXIT_FAILURE;
    }
    
    sf::Texture heart1Tex;
    if (!heart1Tex.loadFromFile("heart1.png")) {
        return EXIT_FAILURE;
    }
    
    sf::Texture coinTex;
    if (!coinTex.loadFromFile("coin1andbg.png")) {
        return EXIT_FAILURE;
    }
    
    sf::Texture coinTexWithoutBG;
    if (!coinTexWithoutBG.loadFromFile("coin1.png")) {
        return EXIT_FAILURE;
    }
    
    sf::Texture jackOLanternTex;
    if (!jackOLanternTex.loadFromFile("jackolantern.png")) {
        return EXIT_FAILURE;
    }
    
    sf::Texture jackOLanternAndBGTex;
    if (!jackOLanternAndBGTex.loadFromFile("jackolanternandbg.png")) {
        return EXIT_FAILURE;
    }
    
    sf::Texture knifeTex;
    if (!knifeTex.loadFromFile("knife1andbg.png")) {
        return EXIT_FAILURE;
    }
    
    sf::Texture candy1Tex;
    if (!candy1Tex.loadFromFile("candy1.png")) {
        return EXIT_FAILURE;
    }
    
    sf::Texture candy2Tex;
    if (!candy2Tex.loadFromFile("candy2.png")) {
        return EXIT_FAILURE;
    }
    
    sf::Texture mapTexture;
    sf::Texture groundTexture1;
    sf::Texture groundTexture2;
    sf::Texture solidBlockTexture1;
    
    if (!solidBlockTexture1.loadFromFile("solidblock1.png")) {
        return EXIT_FAILURE;
    } else std::cout<<"mapTexture loaded\n";
    if (!mapTexture.loadFromFile("pixeltile1.png")) {
        return EXIT_FAILURE;
    } else std::cout<<"mapTexture loaded\n";
    if (!groundTexture1.loadFromFile("pixeltile1.png")) {
        return EXIT_FAILURE;
    } else std::cout<<"ground texture 1 loaded\n";
    if (!groundTexture2.loadFromFile("pixeltile2.png")) {
        return EXIT_FAILURE;
    } else std::cout<<"ground texture 2 loaded\n";
    
    
    sf::Texture marbleTexture1;
    sf::Texture plankTexture1;
    sf::Texture caveBlockTex1;
    sf::Texture grassTex1;
    sf::Texture groundTexture1Rocks;
    sf::Texture waterCorner1;
    sf::Texture waterCorner2;
    sf::Texture waterCorner3;
    sf::Texture waterCorner4;
    sf::Texture waterBlock1;
    sf::Texture cobble1;
    sf::Texture waterTop1;
    sf::Texture waterBottom1;
    sf::Texture waterLeft1;
    sf::Texture waterRight1;
    sf::Texture brickBlock1;
    
    if(!brickBlock1.loadFromFile("brick1.png")) {return EXIT_FAILURE;}
    
    if(!marbleTexture1.loadFromFile("marble1.png")) {return EXIT_FAILURE;}
    if(!plankTexture1.loadFromFile("plank1.png")) {return EXIT_FAILURE;}
    if(!caveBlockTex1.loadFromFile("caveblock1.png")) {return EXIT_FAILURE;}
    if(!grassTex1.loadFromFile("grass1.png")) {return EXIT_FAILURE;}
    if(!groundTexture1Rocks.loadFromFile("pixeltile1withrocks.png")) {return EXIT_FAILURE;}
    if(!waterCorner1.loadFromFile("watercorner1.png")) {return EXIT_FAILURE;}
    if(!waterCorner2.loadFromFile("watercorner2.png")) {return EXIT_FAILURE;}
    if(!waterCorner3.loadFromFile("watercorner3.png")) {return EXIT_FAILURE;}
    if(!waterCorner4.loadFromFile("watercorner4.png")) {return EXIT_FAILURE;}
    if(!waterBlock1.loadFromFile("waterblock1.png")) {return EXIT_FAILURE;}
    if(!cobble1.loadFromFile("cobblestone1.png")) {return EXIT_FAILURE;}
    if(!waterTop1.loadFromFile("watertop1.png")) {return EXIT_FAILURE;}
    if(!waterBottom1.loadFromFile("waterbottom1.png")) {return EXIT_FAILURE;}
    if(!waterLeft1.loadFromFile("waterleft1.png")) {return EXIT_FAILURE;}
    if(!waterRight1.loadFromFile("waterright1.png")) {return EXIT_FAILURE;}
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
    int shouldUpdateItems = 0;
    int shouldLoadItems = 1;
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
    
    //int coins = 0;
    
    
    
    //std::ostringstream ssScore;
    //ssScore << "Score: " << coins;
    
    ui.initUI(arial,coinTexWithoutBG,heart1Tex);
    
    loadPlayerStats(ui,player);
    //lblScore.setString(ssScore.str());
    
    //Gravity Variables:
    const int groundHeight = 700;
    const float gravitySpeed = 0.3;
    bool isJumping = false;
    
    //float moveSpeed = 0.5;
    
    int goingLeft = 0;
    int goingRight = 0;
    int goingUp = 0;
    int goingDown = 0;
    
    int windowFocusLost = 0;
    
    //std::cout<<"BEFORE LOOP\n";
    
    int texVec[256],n=256;
    
    ParticleSystem particles(100); // particle related
    sf::Clock clock; // particle related
    
    
    
    particles.setEmitter({-1000,-1000});
    
    ui.updateStats();
    ui.updateCoinLabel();
    
    
    
    //Main Loop:
    while (window.isOpen()) {
        
        if(ui.activeItemSlot == 1){
            if(player.activeItem != ui.inventory[0])
                player.shouldUpdateItem = 1;
                
            player.activeItem = ui.inventory[0];
            
        } else if(ui.activeItemSlot == 2){
            if(player.activeItem != ui.inventory[1])
                player.shouldUpdateItem = 1;
            
            player.activeItem = ui.inventory[1];
            
        } else if(ui.activeItemSlot ==3){
            if(player.activeItem != ui.inventory[2])
                player.shouldUpdateItem = 1;
            
            player.activeItem = ui.inventory[2];
            
        }
        
        ui.updateStats();
        //ui.updateCoinLabel();
        
        sf::Time elapsed = clock.restart(); // particle related
        particles.update(elapsed); // particle related
        
        
        if(shouldLoadLevel == 1){  //LEVEL LOADER
        
        std::cout<<"level loaded:"<<fileLoadValue<<"\n";
            
        
        
        char loadFile[20];
        snprintf(loadFile, 10, "%d.txt", fileLoadValue);
        
        std::ifstream MyReadFile(loadFile);
        
        MyReadFile>>door1.leadsTo;
        MyReadFile>>door2.leadsTo;
        MyReadFile>>door3.leadsTo;
        MyReadFile>>door4.leadsTo;
            
        MyReadFile>>shouldSpawnGhosts;
            
        enemies.clear();
        //std::vector <Enemy> enemies;
            
            ENEMIES = shouldSpawnGhosts;
            for (int i = 0; i < ENEMIES; ++i) {
                Enemy enemy({40, 90}, std::rand() % 2 == 1 ? enemyTexture1 : enemyTexture2);
                int x = 425 + (std::rand() % 250) * (std::rand() % 2 == 0 ? -1 : 1);
                int y = 400 + (std::rand() % 250) * (std::rand() % 2 == 0 ? -1 : 1);
                enemy.setPos({static_cast<float>(x), static_cast<float>(y)});
                enemies.push_back(enemy);
                //        enemy.playerSpriteOffset({-10, 0});
            }
            
            
            
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
        for(int i=0;i<=256;i++){
            MyReadFile >> texVec[i];
            //std::cout << texVec[i] << " ";
        }
        
        int i=0;
        for(int aa=0;aa<16;aa++){
            for(int bb=0;bb<16;bb++){
                
                if(texVec[i] == 0){
                    map.sprites[bb][aa].setTexture(emptyTex);
                } else if(texVec[i] == 1){
                    map.sprites[bb][aa].setTexture(groundTexture1);
                } else if(texVec[i] == 2){
                    map.sprites[bb][aa].setTexture(groundTexture2);
                } else if(texVec[i] == 3){
                    map.sprites[bb][aa].setTexture(solidBlockTexture1);
                } else if(texVec[i] == 4){
                    map.sprites[bb][aa].setTexture(brickBlock1);
                } else if(texVec[i] == 5){
                    map.sprites[bb][aa].setTexture(marbleTexture1);
                } else if(texVec[i] == 6){
                    map.sprites[bb][aa].setTexture(plankTexture1);
                } else if(texVec[i] == 7){
                    map.sprites[bb][aa].setTexture(caveBlockTex1);
                } else if(texVec[i] == 8){
                    map.sprites[bb][aa].setTexture(grassTex1);
                } else if(texVec[i] == 9){
                map.sprites[bb][aa].setTexture(groundTexture1Rocks);
                }   else if(texVec[i] == 10){
                    map.sprites[bb][aa].setTexture(waterCorner1);
                } else if(texVec[i] == 11){
                    map.sprites[bb][aa].setTexture(waterCorner2);
                } else if(texVec[i] == 12){
                    map.sprites[bb][aa].setTexture(waterCorner3);
                } else if(texVec[i] == 13){
                    map.sprites[bb][aa].setTexture(waterCorner4);
                } else if(texVec[i] == 14){
                    map.sprites[bb][aa].setTexture(waterBlock1);
                } else if(texVec[i] == 15){
                    map.sprites[bb][aa].setTexture(waterTop1);
                }else if(texVec[i] == 16){
                    map.sprites[bb][aa].setTexture(waterBottom1);
                }else if(texVec[i] == 17){
                    map.sprites[bb][aa].setTexture(waterLeft1);
                }else if(texVec[i] == 18){
                    map.sprites[bb][aa].setTexture(waterRight1);
                }else if(texVec[i] == 19){
                    map.sprites[bb][aa].setTexture(cobble1);
                }
                
                
                else map.sprites[bb][aa].setTexture(emptyTex);
                
                i++;
            }
        }
        
        MyReadFile.close();
        // END LEVEL LOADER
            
        
        shouldLoadLevel = 0;
        }
        
        //int test = std::rand() % 3;
        //std::cout<<"\n test ="<<test;
        
        if(shouldLoadItems == 1){
            
            // ITEMGRID FOR LEVEL LOADER
            
            char loadItemFile[20];
            snprintf(loadItemFile, 10, "itm%d.txt", fileLoadValue);
            
            std::ifstream MyItemReadFile(loadItemFile);
            
            //std::cout<<"LOADING ITEMS FROM FILE"<<"\n\n";
            
            for(int i=0;i<=256;i++){
                MyItemReadFile >> itmVec[i];
                //std::cout << texVec[i] << " ";
            }
            
            int jj=0;
            for(int aa=0;aa<16;aa++){
                for(int bb=0;bb<16;bb++){
                    
                    if(itmVec[jj] == 0){
                        itemgrid.sprites[bb][aa].setTexture(emptyTex);
                    } else if(itmVec[jj] == 1){
                        itemgrid.sprites[bb][aa].setTexture(coinTex);
                    } else if(itmVec[jj] == 2){
                        itemgrid.sprites[bb][aa].setTexture(knifeTex);
                    } else if(itmVec[jj] == 3){
                        itemgrid.sprites[bb][aa].setTexture(candy1Tex);
                    } else if(itmVec[jj] == 4){
                        itemgrid.sprites[bb][aa].setTexture(candy2Tex);
                    } else if(itmVec[jj] == 5){
                        itemgrid.sprites[bb][aa].setTexture(jackOLanternAndBGTex);
                    }
                    //std::cout<<itmVec[jj]<<" ";
                    
                    jj++;
                }
                //std::cout<<"\n";
            }
            
            MyItemReadFile.close();
            
            //std::cout<<"\nFILE CLOSED\n\n";
            
            
            // END ITEMGRID FOR LEVEL LOADER
            
        shouldLoadItems = 0;
        }
        
        if(shouldUpdateItems == 1){
            int jj=0;
            for(int aa=0;aa<16;aa++){
                for(int bb=0;bb<16;bb++){
                    
                    if(itmVec[jj] == 0){
                        itemgrid.sprites[bb][aa].setTexture(emptyTex);
                    } else if(itmVec[jj] == 1){
                        itemgrid.sprites[bb][aa].setTexture(coinTex);
                    } else if(itmVec[jj] == 2){
                        itemgrid.sprites[bb][aa].setTexture(knifeTex);
                    } else if(itmVec[jj] == 3){
                        itemgrid.sprites[bb][aa].setTexture(candy1Tex);
                    } else if(itmVec[jj] == 4){
                        itemgrid.sprites[bb][aa].setTexture(candy2Tex);
                    } else if(itmVec[jj] == 5){
                        itemgrid.sprites[bb][aa].setTexture(jackOLanternAndBGTex);
                    }
                    //std::cout<<itmVec[jj]<<" ";
                    
                    jj++;
                }
                //std::cout<<"\n";
            }
            shouldUpdateItems = 0;
        }
        
        
        sf::Event Event;
        
        //player movement + item collision logic??
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)){
            
            if(windowFocusLost == 0)
            windowFocusLost = 1;
            
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space)){
            windowFocusLost = 0;
        }
        
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
            
            if(windowFocusLost == 0){
            player.move({ 0, -ui.movementSpeed });
                isJumping = true;
                goingUp = 1;
            }
        } else {goingUp = 0;}
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
            
            if(windowFocusLost == 0){
                player.move({ 0, ui.movementSpeed });
                goingDown = 1;
            }
                //isJumping = true;}
        } else {goingDown = 0;}
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
            
            if(windowFocusLost == 0){
            if(player.facing == 1){
                player.playerSpriteScale({1.0,1.0});
                player.playerSpriteOffset({-10,0});
                player.facing = 0;
            }
                player.move({ ui.movementSpeed, 0 });
                goingRight = 1;
            }
        
            
        } else {goingRight = 0;}
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
            
            if(windowFocusLost == 0){
            if(player.facing == 0){
                player.playerSpriteScale({-1.0,1.0});
                player.playerSpriteOffset({50,0});
                player.facing = 1;
            }
                player.move({ -ui.movementSpeed, 0 });
                goingLeft = 1;
            }
            
        } else {goingLeft = 0;}
        
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z)) {
            ui.activeItemSlot = 1;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::X)) {
            ui.activeItemSlot = 2;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::C)) {
            ui.activeItemSlot = 3;
        }
        
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
            
            
            
            if( player.activeItem == 5 ){
                
                std::cout<<"\n USED JACK O LANTERN!!!";
                
                
                if(ui.activeItemSlot == 1){
                    ui.inventory[0] = 0;
                    ui.itmSlSp1.setTexture(emptyTex);
                } else if(ui.activeItemSlot == 2){
                    ui.inventory[1] = 0;
                    ui.itmSlSp2.setTexture(emptyTex);
                } else if(ui.activeItemSlot == 3){
                    ui.inventory[2] = 0;
                    ui.itmSlSp3.setTexture(emptyTex);
                }
                
                ui.itmSlSp1.setTexture(emptyTex);
                ui.itmSlSp2.setTexture(emptyTex);
                ui.itmSlSp3.setTexture(emptyTex);
                
                player.activeItemSprite.setTexture(emptyTex);
                
                
                
                //hp, speed, damage
                int r = std::rand() % 3;
                
                
                if(r == 1){ //hp
                    
                    int a = std::rand() % 3;
                    int b = std::rand() % 2;
                    
                    if(b == 0){
                        ui.health = ui.health + a;
                    } else {
                        ui.health = ui.health - a;
                    }
                    
                } else if (r == 2){ //speed
                    
                    float a = std::rand() % 10;
                    int b = std::rand() % 2;
                    
                    if(b == 0){
                        ui.movementSpeed = ui.movementSpeed + a / 100;
                    } else {
                        ui.movementSpeed = ui.movementSpeed - a / 100;
                    }
                    
                } else if (r == 3){ //damage
                    
                    float a = std::rand() % 10;
                    int b = std::rand() % 2;
                    
                    if(b == 0){
                        ui.damage = ui.damage + a / 100;
                    } else {
                        ui.damage = ui.damage - a / 100;
                    }
                    
                }
                
                std::cout<<"\n r = "<<r;
                
                player.activeItem = 0;
                //ui.inventory[ui.activeItemSlot] = 0; //deletes item
                
                
                
                
            }
            
            
            
        }
        
        //Event Loop:
        while (window.pollEvent(Event)) {
            switch (Event.type) {
                    
                case sf::Event::Closed:
                    window.close();
                    
                case sf::Event::KeyReleased:
                    isJumping = false;
                    
                //case sf::Event::LostFocus:
                    //windowFocusLost = 1;
                    
                //case sf::Event::GainedFocus:
                    //windowFocusLost = 0;
                    
            }
        }
        
        if(windowFocusLost == 0){
        //lblScore.setString("0");
        //lblScore.setString(std::to_string(coins));
        //ui.updateCoinLabel();
        //ui.coins = coins;
        
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
            
        //more bounds logic
            
        int i=0;
        for(int aa=0;aa<16;aa++){
                for(int bb=0;bb<16;bb++){
                  
                    
                if((texVec[i] == 0 || texVec[i] == 4) &&player.player.getGlobalBounds().intersects(map.collRect[bb][aa].getGlobalBounds())){
                    
                    if(goingLeft == 1){
                        player.move({1,0});
                    }
                    if(goingRight == 1){
                        player.move({-1,0});
                    }
                    if(goingUp == 1){
                        player.move({0,1});
                    }
                    if(goingDown == 1){
                        player.move({0,-1});
                    }
                    
                    //lblScore.setString("COLLIDING");
                    //std::cout<<"COLLIDING";
                }
                
                //if ()
                //if(player.getGlobalBounds() == 0)
                //i = 0;
                
                    
                i++;
            }
        }
        
            
        //end more bounds logic
            
        //item collision logic
            
            i=0;
            for(int aa=0;aa<16;aa++){
                for(int bb=0;bb<16;bb++){
                    
                    
                    if(itmVec[i] != 0 && player.player.getGlobalBounds().intersects(itemgrid.collRect[bb][aa].getGlobalBounds())){
                        
                        //std::cout<<"COLLIDING!";
                        
                        if(itmVec[i] == 1){
                            //std::cout<<"\nDEBUG: COIN COLLECTED\n";
                            
                            ui.coins++;
                            //ui.updateStats();
                            //lblScore.setString(std::to_string(coins));
                            //ui.updateCoinLabel();
                            //ui.coins = coins;
                            
                            //std::cout<<"\nui.coins:"<<ui.coins;
                            
                            coinPickupSfx.stop();
                            coinPickupSfx.play();
                        }
                        
                        if(itmVec[i] == 2){
                            
                            //std::cout<<"\nDEBUG: KNIFE COLLECTED\n";
                            itemPickupSfx.stop();
                            itemPickupSfx.play();
                            
                            ui.damage = 1;
                            
                            if(ui.activeItemSlot == 1){
                                ui.inventory[0] = 2;
                                ui.itmSlSp1.setTexture(knifeTex);
                            } else if(ui.activeItemSlot == 2){
                                ui.inventory[1] = 2;
                                ui.itmSlSp2.setTexture(knifeTex);
                            } else if(ui.activeItemSlot == 3){
                                ui.inventory[2] = 2;
                                ui.itmSlSp3.setTexture(knifeTex);
                            }
                            
                            //player.activeItem = 2;
                            //player.activeItemSprite.setTexture(knifeTex);
                            
                            //if(ui.activeItemSlot)
                            
                            
                        }
                        
                        if(itmVec[i] == 3){
                            
                            //std::cout<<"\nDEBUG: BLUE CANDY COLLECTED";
                            itemPickupSfx.stop();
                            itemPickupSfx.play();
                            ui.movementSpeed = ui.movementSpeed + 0.05;
                            std::cout<<ui.movementSpeed;
                        }
                        
                        if(itmVec[i] == 4){
                            
                            //std::cout<<"\nDEBUG: RED CANDY COLLECTED";
                            itemPickupSfx.stop();
                            itemPickupSfx.play();
                            ui.movementSpeed = ui.movementSpeed - 0.05;
                            std::cout<<ui.movementSpeed;
                            
                        }
                        
                        if(itmVec[i] == 5){
                            
                            //std::cout<<"\nDEBUG: JACK O LANTERN COLLECTED";
                            itemPickupSfx.stop();
                            itemPickupSfx.play();
                            
                            if(ui.activeItemSlot == 1){
                                ui.inventory[0] = 5;
                                ui.itmSlSp1.setTexture(jackOLanternTex);
                            } else if(ui.activeItemSlot == 2){
                                ui.inventory[1] = 5;
                                ui.itmSlSp2.setTexture(jackOLanternTex);
                            } else if(ui.activeItemSlot == 3){
                                ui.inventory[2] = 5;
                                ui.itmSlSp3.setTexture(jackOLanternTex);
                            }
                            
                            //player.activeItem = 5;
                            //player.activeItemSprite.setTexture(jackOLanternTex);
                            
                            
                        }
                        
                        
                        itmVec[i] = 0;
                        shouldUpdateItems = 1;
                        
                        if(autosave == 1){
                            
                        saveFile(fileLoadValue);
                        savePlayerStats(ui,player);
                            
                        }
                        
                        //lblScore.setString("COLLIDING");
                        //std::cout<<"COLLIDING";
                    }
                    
                    //if ()
                    //if(player.getGlobalBounds() == 0)
                    //i = 0;
                    
                    
                    i++;
                }
            }
            
        //end item collision logic
            
        //player update item logic
            
            if(player.shouldUpdateItem == 1){
                
                if(player.activeItem == 2){
                    player.activeItemSprite.setTexture(knifeTex);
                } else if(player.activeItem == 5){
                    player.activeItemSprite.setTexture(jackOLanternTex);
                } else if(player.activeItem == 0){
                    player.activeItemSprite.setTexture(emptyTex);
                }
                
                std::cout<<"\nplayer active item:"<<player.activeItem<<"\n";
                
                player.shouldUpdateItem = 0;
                
            }
            
        //end player update item logic
            
            
        
        
        //door logic
        
        for (int i = 0; i < doorVec.size(); i++) {
            if (player.isCollidingWithDoor(doorVec[i])) {
                
                //if(collideOnce == 0){
                if(player.collideCooldown > 100){
                    
                    if(doorVec[i]->leadsTo != 99){
                        fileLoadValue = doorVec[i]->leadsTo;
                        shouldLoadLevel = 1;
                        shouldLoadItems = 1;
                        
                        doorCloseSfx.stop();
                        doorCloseSfx.play();
                    }
                    
                    if(i == 0 && shouldLoadLevel == 1){
                        player.setPos({800,400});
                        
                        player.playerSpriteOffset({50,0});
                        player.playerSpriteScale({-1.0,1.0});
                        
                    } else if(i == 1 && shouldLoadLevel == 1){
                        player.setPos({400,750});
                        
                        player.playerSpriteOffset({-10,0});
                        player.playerSpriteScale({1.0,1.0});
                        
                        
                    } else if(i == 2 && shouldLoadLevel == 1){
                        player.setPos({5,450});
                        
                        player.playerSpriteOffset({-10,0});
                        player.playerSpriteScale({1.0,1.0});
                        
                        
                    } else if(i == 3 && shouldLoadLevel == 1){
                        player.setPos({400,100});
                        
                        player.playerSpriteOffset({-10,0});
                        player.playerSpriteScale({1.0,1.0});
                        
                        
                    }
                
                    player.collideCooldown = 0;
                }
                
            } else if(player.isCollidingWithDoor(doorVec[i]) == false) {
                //collideOnce = 0;
            }
            
        }
            
        } else {
            //lblScore.setString("GAME PAUSED, SPACE TO RESUME");
        }//window focus lost
        
        //end door logica
        
        for (auto enemy = enemies.begin(); enemy != enemies.end(); ++enemy) {
            enemy->testFor(ui,player);
        }
        
        window.clear();
        map.drawTo(window);
        //coin1.drawTo(window);
        //window.draw(lblScore);
        
        //coin2.drawTo(window);
        
        //sf::Vector2f plcrds = ({player.getX(),player.getY()});
        particles.setEmitter(window.mapPixelToCoords({player.getX()+15,player.getY()+30}));
        window.draw(particles);
        
        player.drawTo(window);
        
        for (auto enemy = enemies.begin(); enemy != enemies.end(); ++enemy) {
            enemy->drawTo(window);
        }
        
        itemgrid.drawTo(window);
        
        door1.drawTo(window);
        door2.drawTo(window);
        door3.drawTo(window);
        door4.drawTo(window);
        
        ui.drawTo(window);
        
        window.display();
    }
}
