#include "WindowSfml.hpp"

Window::Window(void) { return; }

Window::Window(unsigned int width, unsigned int height) {
    try {
        this->window = new sf::RenderWindow(
            sf::VideoMode(
                width * CELL_UNITY, height * CELL_UNITY,
                sf::VideoMode::getDesktopMode().bitsPerPixel
            ),
            "Nibbler"
        );
    }
    catch (...) {
        std::cout << "SFML init() failed." << std::endl;
        exit(0);
    }
    std::cout << "SFML dynamicly charged" << std::endl;
    return;
}

Window::~Window(void) {
     this->window->close();
}

int   Window::getHooks(void) const {
    sf::Event   event;
    this->window->pollEvent(event);
    if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::Escape) { return -1; }
        if (event.key.code == sf::Keyboard::Up) { return Up; }
        if (event.key.code == sf::Keyboard::Down) { return Down; }
        if (event.key.code == sf::Keyboard::Left) { return Left; }
        if (event.key.code == sf::Keyboard::Right) { return Right; }
    }
    return -2;
}

void      Window::drawFrame(std::list <IEntity *> data) const {
    sf::Color color(22,22, 24, 0);
    this->window->clear(color);
    sf::Texture texture;
    sf::Sprite sprite;
    float size = (static_cast<float>(CELL_UNITY) / 300);
    std::list <IEntity *>::iterator iter = data.begin();
    while (iter != data.end()) {
        sprite.setPosition(sf::Vector2f((*iter)->getPosX(), (*iter)->getPosY())); // position absolue
        texture.loadFromFile("./assets/r_head.bmp");
        texture.setSmooth(true);
        sprite.setTexture(texture);
        sprite.setScale(size, size);
        this->window->draw(sprite);
        iter++;
    }
    this->window->display();
    return;
}

Window      *createWindow(unsigned int width, unsigned int height) {
    return new Window(width, height);
}

void        deleteWindow(Window *window) {
    delete window;
}
