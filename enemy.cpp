
#include <iostream>
#include <SFML/Graphics.hpp>
#include <cmath>

class Enemy {
public:

    sf::RectangleShape enemy;

    int facing = 0; //0-stanga, 1-drepta
    sf::Sprite enemySprite;

    float WONDERING_SPEED = .2;
    float ATTACK_SPEED = 0.5;
    int ATTACK_IF_CLOSER_THAN = 100;
    int LOSE_INTEREST_AT = 200;
    bool target = false;
    sf::Vector2f wonderTo = {-1, -1};
    int first = 0;

    sf::Vector2f velocity = {0, 0};
    sf::Vector2f acceleration = {0, 0};

    Enemy(sf::Vector2f size, sf::Texture &texture) { // Enemy(position)
        enemy.setSize(size);
        enemy.setFillColor(sf::Color::Transparent);

        enemySprite.setScale(sf::Vector2f(0.1f, 0.1f));
        enemySprite.setTexture(texture);
    }

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

    void testFor(Player player) {
        if (distance(player) < ATTACK_IF_CLOSER_THAN) {
            target = true;
        } else if (target && distance(player) > LOSE_INTEREST_AT) {
            target = false;
        }
        if (wonderTo.x < 0 || wonderTo.y < 0) {
            wonderTo = getRandomLocation();
        }
        if (distance(wonderTo.x, wonderTo.y, getX(), getY()) < 10) {
            wonderTo = getRandomLocation();
        }

        update(player);
    }

    void update(Player player) {
        sf::Vector2f dir;
        if (target) {
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
        return {std::rand() % 900, std::rand() % 900};
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

    bool isCollidingPlayer(Player *player) {
        if (enemy.getGlobalBounds().intersects(player->getGlobalBounds())) {
            return true;
        }
        return false;
    }
};
