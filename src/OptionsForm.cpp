#include "OptionsForm.h"

OptionsForm::OptionsForm() : Form("../res/map_menu.txt") {
    initMenuView();
    initImages();
}

OptionsForm::~OptionsForm() {
    delete menuView;
    delete logoIV;
    delete dialog;
}

void OptionsForm::pollEvents(sf::Event &event, sf::RenderWindow *window, Application *context) {
    switch (event.type) {
        case sf::Event::Closed:
            window->close();
            break;
        case sf::Event::KeyPressed:
            switch (event.key.code) {
                case sf::Keyboard::Enter:
                    switch (menuView->getSelectedItemIndex()) {
                        case 0:
                            if (!dialog) {
                                dialog = new DialogView("Reset game", "clear all game data", "reset",
                                                        "cancel", window->getSize(),
                                                        [&]() -> void {
                                                            context->resetGame();
                                                            context->pushFront(new GameForm());
                                                            delete dialog;
                                                            dialog = nullptr;
                                                        },
                                                        [&]() -> void {
                                                            delete dialog;
                                                            dialog = nullptr;
                                                        });
                            }
                            break;
                        case 1:
                            if (!dialog) {
                                dialog = new DialogView("Clear Record", "reset game record", "clear",
                                                        "cancel", window->getSize(),
                                                        [&]() -> void {
                                                            if (remove("high_score.txt") != 0)
                                                                cerr << "Error deleting file";
                                                            delete dialog;
                                                            dialog = nullptr;
                                                        },
                                                        [&]() -> void {
                                                            delete dialog;
                                                            dialog = nullptr;
                                                        });
                            }
                            break;
                        case 2:
                            context->popForm();
                            break;
                    }
                    break;
                case sf::Keyboard::Down:
                    menuView->selectItem(menuView->getSelectedItemIndex() + 1);
                    break;
                case sf::Keyboard::Up:
                    menuView->selectItem(menuView->getSelectedItemIndex() - 1);
                    break;
                    //handling dialog click events
            }
            break;
        case sf::Event::MouseButtonReleased:
        case sf::Event::MouseButtonPressed:
            if (event.mouseButton.button == sf::Mouse::Left) {
                if (dialog)
                    dialog->pollEvents(event, window);
            }
            break;
    }

}

void OptionsForm::update(sf::RenderWindow *window, const sf::Time &dt) {
}

void OptionsForm::render(sf::RenderWindow *window) {
    menuView->render(window);
    window->draw(*logoIV);
    if (dialog)
        dialog->render(window);
}

void OptionsForm::initMenuView() {
    menuView = new MenuView(sf::Vector2f(Config::videoMode.width / 2.f, 355));
    menuView->pushItem("reset");
    menuView->pushItem("clear score");
    menuView->pushItem("back to menu");
}

void OptionsForm::initImages() {
    logoIV = new sf::RectangleShape({385, 91});
    logoIV->setOrigin(logoIV->getLocalBounds().width / 2, 0);
    logoIV->setPosition(Config::videoMode.width / 2, 208);
    if (!logoSrc.loadFromFile("../res/images/logo.png")) throw runtime_error("Cannot open resource");
    logoIV->setTexture(&logoSrc);
}