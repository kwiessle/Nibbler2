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
    this->initTextures();
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
        if (event.key.code == sf::Keyboard::Up && this->hook != Down) { this->hook = Up; }
        if (event.key.code == sf::Keyboard::Down && this->hook != Up) { this->hook = Down; }
        if (event.key.code == sf::Keyboard::Left && this->hook != Right) { this->hook = Left; }
        if (event.key.code == sf::Keyboard::Right && this->hook != Left) { this->hook = Right; }
    }
}

void      Window::drawFrame(std::list <IEntity *> data) const {
    sf::Color color(22,22, 24, 0);
    this->window->clear(color);
    sf::Sprite sprite;
    float size = (static_cast<float>(CELL_UNITY) / 150);
    std::list <IEntity *>::iterator iter = data.begin();

    while (iter != data.end()) {
        sprite.setPosition(sf::Vector2f((*iter)->getPosX() * 2, (*iter)->getPosY() * 2)); // position absolue
        eTexture img = (*iter)->getTexture();
        sprite.setTexture(this->_textures.find(img)->second);
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

void       Window::initTextures(void) {
     sf::Texture uHeadSurf;
      uHeadSurf.loadFromFile("./assets/u_head.bmp");
     sf::Texture dHeadSurf;
      dHeadSurf.loadFromFile("./assets/d_head.bmp");
     sf::Texture lHeadSurf;
      lHeadSurf.loadFromFile("./assets/l_head.bmp");
     sf::Texture rHeadSurf;
      rHeadSurf.loadFromFile("./assets/r_head.bmp");
     sf::Texture uHeadMiamSurf;
      uHeadMiamSurf.loadFromFile("./assets/u_head_miam.bmp");
     sf::Texture dHeadMiamSurf;
      dHeadMiamSurf.loadFromFile("./assets/d_head_miam.bmp");
     sf::Texture lHeadMiamSurf;
      lHeadMiamSurf.loadFromFile("./assets/l_head_miam.bmp");
     sf::Texture rHeadMiamSurf;
      rHeadMiamSurf.loadFromFile("./assets/r_head_miam.bmp");
     sf::Texture uQueueSurf;
      uQueueSurf.loadFromFile("./assets/u_queue.bmp");
     sf::Texture dQueueSurf;
      dQueueSurf.loadFromFile("./assets/d_queue.bmp");
     sf::Texture lQueueSurf;
      lQueueSurf.loadFromFile("./assets/l_queue.bmp");
     sf::Texture rQueueSurf;
      rQueueSurf.loadFromFile("./assets/r_queue.bmp");
     sf::Texture luCornerSurf;
      luCornerSurf.loadFromFile("./assets/lu_corner.bmp");
     sf::Texture ldCornerSurf;
      ldCornerSurf.loadFromFile("./assets/ld_corner.bmp");
     sf::Texture ruCornerSurf;
      ruCornerSurf.loadFromFile("./assets/ru_corner.bmp");
     sf::Texture rdCornerSurf;
      rdCornerSurf.loadFromFile("./assets/rd_corner.bmp");
     sf::Texture hBodySurf;
      hBodySurf.loadFromFile("./assets/h_body.bmp");
     sf::Texture vBodySurf;
      vBodySurf.loadFromFile("./assets/v_body.bmp");
    this->_textures.insert(std::make_pair(uHead, uHeadSurf));
    this->_textures.insert(std::make_pair(dHead, dHeadSurf));
    this->_textures.insert(std::make_pair(lHead, lHeadSurf));
    this->_textures.insert(std::make_pair(rHead, rHeadSurf));
    this->_textures.insert(std::make_pair(uHeadMiam, uHeadMiamSurf));
    this->_textures.insert(std::make_pair(dHeadMiam, dHeadMiamSurf));
    this->_textures.insert(std::make_pair(lHeadMiam, lHeadMiamSurf));
    this->_textures.insert(std::make_pair(rHeadMiam, rHeadMiamSurf));
    this->_textures.insert(std::make_pair(uQueue, uQueueSurf));
    this->_textures.insert(std::make_pair(dQueue, dQueueSurf));
    this->_textures.insert(std::make_pair(lQueue, lQueueSurf));
    this->_textures.insert(std::make_pair(rQueue, rQueueSurf));
    this->_textures.insert(std::make_pair(luCorner, luCornerSurf));
    this->_textures.insert(std::make_pair(ldCorner, ldCornerSurf));
    this->_textures.insert(std::make_pair(ruCorner, ruCornerSurf));
    this->_textures.insert(std::make_pair(rdCorner, rdCornerSurf));
    this->_textures.insert(std::make_pair(hBody, hBodySurf));
    this->_textures.insert(std::make_pair(vBody, vBodySurf));
    return;
}
