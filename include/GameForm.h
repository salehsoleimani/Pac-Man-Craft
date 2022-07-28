#ifndef PACMAN_GAMEFORM_H
#define PACMAN_GAMEFORM_H

#include <array>
#include "Wall.h"
#include "TextView.h"
#include "MainForm.h"
#include "Form.h"
#include "File.h"
#include "ButtonView.h"
#include "DialogView.h"

using namespace std;

class Pacman;
class Ghost;

class GameForm : public Form {
public:
    GameForm();

    ~GameForm();

    const vector<Food *> &getFoods() const;

    const vector<Ghost *> &getGhosts() const;

    void raiseScore(int);

private:
    unsigned score = 0;
    unsigned highScore = 0;

    Food *food;

    vector<Food *> foods;

    vector<Ghost *> ghosts;

    Pacman *pacman;

    TextView *txtScore;
    TextView *txtRecord;
    TextView *btnBack;

    sf::Sprite btnBackIc;

    DialogView *dialog = nullptr;

    void pollEvents(sf::Event &, sf::RenderWindow *, Application *) override;

    void update(sf::RenderWindow *, const sf::Time &) override;

    void render(sf::RenderWindow *) override;

    void initTexts();

    void initSprites();
};

#endif //PACMAN_GAMEFORM_H
