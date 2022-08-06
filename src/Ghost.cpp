#include "Ghost.h"
#include <random>

int Ghost::deadGhosts = 0;

Ghost::Ghost(sf::Vector2f position, GameForm *context) : GameObject(position), context(context) {
    ghost.setPosition(position);
    initialPosition = position;

    animator = new Animator(ghost);

    if (context->getLevel() > 128) frightenedDuration = sf::Time::Zero;
    else if (context->getLevel() >= 64) frightenedDuration = sf::seconds(1);
    else if (context->getLevel() >= 32) frightenedDuration = sf::seconds(1);
    else if (context->getLevel() >= 17) frightenedDuration = sf::seconds(2);
    else if (context->getLevel() >= 11) frightenedDuration = sf::seconds(3);
    else if (context->getLevel() >= 6) frightenedDuration = sf::seconds(4);
    else if (context->getLevel() == 5) frightenedDuration = sf::seconds(2);
    else if (context->getLevel() == 4) frightenedDuration = sf::seconds(3);
    else if (context->getLevel() == 3) frightenedDuration = sf::seconds(4);
    else if (context->getLevel() == 2) frightenedDuration = sf::seconds(5);
    else frightenedDuration = sf::seconds(6);

    updateRelativePosition();

    nextTile = relativePosition;
}

Ghost::~Ghost() {
    delete animator;
}

void Ghost::pollEvents(sf::Event &event) {

}

void Ghost::render(sf::RenderTarget *target) {
    target->draw(ghost);
}

void Ghost::changeState(GhostState state) {
    ghostState = state;

    switch (ghostState) {
        case Ghost::GhostState::FRIGHTENED:
            if (animator->getCurrentAnimationId() != "frightened")
                animator->setAnimation("frightened");
            frightenedTimer -= frightenedDuration.asSeconds();
            break;
        case GhostState::CHASE:
            break;
        case GhostState::SCATTER:
            break;
        case GhostState::DEAD:
            animator->setAnimation("die");
            break;
    }
}

void Ghost::update(sf::Time dt) {

    animator->update(dt);

    int x = speed;

    //normal speeds!
    if (context->getLevel() >= 21) x *= .95;
    else if (context->getLevel() >= 5) x *= .85;
    else x *= .75;

    nextMove = {0, 0};

    switch (direction) {
        case Directions::DOWN:
            if (ghostState != GhostState::FRIGHTENED)
                animator->setAnimation("down");
            nextMove.y += x;
            break;
        case Directions::UP:
            if (ghostState != GhostState::FRIGHTENED)
                animator->setAnimation("up");
            nextMove.y -= x;
            break;
        case Directions::LEFT:
            if (ghostState != GhostState::FRIGHTENED)
                animator->setAnimation("left");
            nextMove.x -= x;
            break;
        case Directions::RIGHT:
            if (ghostState != GhostState::FRIGHTENED)
                animator->setAnimation("right");
            nextMove.x += x;
            break;
        case Directions::INIT:
            nextMove = {0, 0};
            break;
    }

    switch (ghostState) {
        case Ghost::GhostState::FRIGHTENED:
            frightenedTimer += dt.asSeconds();
            if (frightenedTimer >= frightenedDuration.asSeconds()) {
                frightenedTimer = 0;
                ghostState = GhostState::CHASE;
                deadGhosts = 0;
            }
            break;
        case GhostState::CHASE:
            break;
        case GhostState::SCATTER:
            break;
        case GhostState::DEAD:
            break;
    }

    if (isInTile()) {

        if (relativePosition != nextTile)
            ghost.setPosition(nextTile.x * Dimensions::wallSize.x, nextTile.y * Dimensions::wallSize.y);

        updateRelativePosition();

        possibleRoutes.clear();
        checkPossibleRoutes();

        std::random_device dev;
        std::mt19937 rng(dev());
        std::uniform_int_distribution<std::mt19937::result_type> randomRoute(0, possibleRoutes.size() - 1);

        Direction nextDirection = possibleRoutes[randomRoute(rng)];

        if (nextDirection.tile != lastTile || possibleRoutes.size() == 1) {
            lastTile = nextTile;
            direction = nextDirection.direction;
            nextTile = nextDirection.tile;
        }
    }

    ghost.move(nextMove);
}


bool Ghost::isInTile() {
    updateRelativePosition();

    switch (direction) {
        case Directions::INIT:
            return true;
        case Directions::UP:
            if (relativePosition.y <= nextTile.y)
                return true;
            break;
        case Directions::DOWN:
            if (relativePosition.y >= nextTile.y)
                return true;
            break;
        case Directions::LEFT:
            if (relativePosition.x <= nextTile.x)
                return true;
            break;
        case Directions::RIGHT:
            if (relativePosition.x >= nextTile.x)
                return true;
    }
    return false;
}


void Ghost::checkPossibleRoutes() {

    if (context->getBoard()[relativePosition.y][relativePosition.x + 1] !=
        GameObject::ObjectType::WALL) {
        possibleRoutes.push_back({Directions::RIGHT, {relativePosition.x + 1, relativePosition.y}});
    }
    if (context->getBoard()[relativePosition.y][relativePosition.x - 1] !=
        GameObject::ObjectType::WALL) {
        possibleRoutes.push_back({Directions::LEFT, {relativePosition.x - 1, relativePosition.y}});
    }
    if (context->getBoard()[relativePosition.y + 1][relativePosition.x] !=
        GameObject::ObjectType::WALL) {
        possibleRoutes.push_back({Directions::DOWN, {relativePosition.x, relativePosition.y + 1}});
    }
    if (context->getBoard()[relativePosition.y - 1][relativePosition.x] !=
        GameObject::ObjectType::WALL) {
        possibleRoutes.push_back({Directions::UP,
                                  {relativePosition.x, relativePosition.y - 1}});
    }
}

void Ghost::updateRelativePosition() {
    relativePosition = {ghost.getPosition().x / Dimensions::wallSize.x,
                        ghost.getPosition().y / Dimensions::wallSize.x};
}

const Ghost::GhostState &Ghost::getGhostState() const {
    return ghostState;
}

void Ghost::die() {
    ghostState = GhostState::DEAD;
    animator->setAnimation("die");
    context->raiseScore((++deadGhosts) * 200);
}

bool Ghost::isColided(const sf::Rect<float> &rect) const {
    return ghost.getGlobalBounds().intersects(rect);
}

void Ghost::setPosition(const sf::Vector2f &pos) {
    ghost.setPosition(pos);
    updateRelativePosition();
    nextTile = relativePosition;
    lastTile = {0, 0};
    frightenedTimer = 0;
}

const sf::Vector2f &Ghost::getInitialPosition() const {
    return initialPosition;
}
