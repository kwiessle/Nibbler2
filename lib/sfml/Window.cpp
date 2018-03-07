#include "Window.hpp"

Window::Window(void) { return; }

Window::Window(unsigned int width, unsigned int height) {
    this->window = new sf::RenderWindow(
        sf::VideoMode(width * CELL_UNITY, height * CELL_UNITY),
        "Nibbler"
    );
    this->event = new sf::Event();
    std::cout << "SFML dynamicly charged" << std::endl;
    return;
}

Window::~Window(void) {
     this->window->close();
}

int   Window::getHooks(void) const {

    this->window->pollEvent(*this->event);
    if (event->type == sf::Event::keyPressed){
        if (event->key.code == sf::Keyboard::Escape) { return -1; }
        if (event->key.code == sf::Keyboard::Up) { return UP; }
        if (event->key.code == sf::Keyboard::Down) { return Down; }
        if (event->key.code == sf::Keyboard::Left) { return Left; }
        if (event->key.code == sf::Keyboard::Right) { return Right; }
    }
    return -2;
}

void      Window::drawFrame(std::list <IEntity *> data) const {}

Window      *createWindow(unsigned int width, unsigned int height) {
    return new Window(width, height);
}

void        deleteWindow(Window *window) {
    delete window;
}
