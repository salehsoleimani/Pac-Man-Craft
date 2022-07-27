#ifndef PACMAN_GHOST_H
#define PACMAN_GHOST_H

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "Values.h"
#include "Animator.h"
#include "GameForm.h"

class Ghost : public GameObject {
public:
    explicit Ghost(sf::Vector2f, GameForm *);

    ~Ghost();

    void pollEvents(sf::Event &);

    void render(sf::RenderTarget *) override;

protected:
    //using game context and it's properties
    GameForm *context;
    //animator used for ghost sprite
    Animator *animator;

    Directions direction;

    sf::Sprite ghost;

    float speed = 3;

    void updateRelativePosition();
};


#endif //PACMAN_GHOST_H
