#include "Inky.h"

Inky::Inky(sf::Vector2f position, GameForm *context) : Ghost(position, context) {

    animator->add("right", sf::milliseconds(300), "../res/sprites/inky.png", sf::Vector2i(120, 0), 2);
    animator->add("left", sf::milliseconds(300), "../res/sprites/inky.png", sf::Vector2i(60, 0), 2);
    animator->add("up", sf::milliseconds(300), "../res/sprites/inky.png", sf::Vector2i(180, 0), 2);
    animator->add("down", sf::milliseconds(300), "../res/sprites/inky.png", sf::Vector2i(0,0), 2);

    animator->setAnimation("right");
    animator->update(sf::milliseconds(300));
}

void Inky::update(sf::Time dt) {

}