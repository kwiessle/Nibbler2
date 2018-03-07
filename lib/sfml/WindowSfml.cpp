#include "WindowSfml.hpp"

Window::Window(void) { return; }

Window::Window(unsigned int width, unsigned int height) :
 wWidth(width * CELL_UNITY),
 wHeight(height * CELL_UNITY),
 hook(Right)
{
    try {
        this->window = new sf::RenderWindow(
            sf::VideoMode(
                width * CELL_UNITY * 2, height * CELL_UNITY * 2,
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

eHook   Window::getHooks(void) const {
    return this->hook;
}

void   Window::setHooks(void) {
    sf::Event   event;
    this->window->pollEvent(event);
    if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::Escape) { this->hook = Exit; }
        if (event.key.code == sf::Keyboard::Up) { this->hook = Up; }
        if (event.key.code == sf::Keyboard::Down) { this->hook = Down; }
        if (event.key.code == sf::Keyboard::Left) { this->hook = Left; }
        if (event.key.code == sf::Keyboard::Right) { this->hook = Right; }
    }
}

void      Window::drawFrame(std::list <IEntity *> data) const {
    sf::Color color(22,22, 24, 0);
    this->window->clear(color);
    sf::Texture texture;
    sf::Sprite sprite;
    float size = (static_cast<float>(CELL_UNITY) / 150);
    std::list <IEntity *>::iterator iter = data.begin();

    while (iter != data.end()) {
        sprite.setPosition(sf::Vector2f((*iter)->getPosX() * 2, (*iter)->getPosY() * 2)); // position absolue
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

unsigned int    Window::getWidth(void) const {
    return this->wWidth;
}

unsigned int    Window::getHeight(void) const {
    return this->wHeight;
}

Window      *createWindow(unsigned int width, unsigned int height) {
    return new Window(width, height);
}

void        deleteWindow(Window *window) {
    delete window;
}
