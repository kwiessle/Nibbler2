#include "WindowSfml.hpp"

Window::Window(void) { return; }

Window::Window(unsigned int width, unsigned int height) :
 wWidth(width),
 wHeight(height),
 hook(Right)
{
    sf::Image icon;
    try {
        this->window = new sf::RenderWindow(
            sf::VideoMode(
                this->wWidth * CELL_UNITY,
                this->wHeight * CELL_UNITY + CELL_UNITY * 2),
            "Nibbler"
        );
    }
    catch (...) {
        std::cout << "SFML init() failed." << std::endl;
        exit(0);
    }
    this->initTextures();
    this->pFont.loadFromFile("./assets/roboto.ttf");
    icon.loadFromFile("./assets/appicon.bmp");
    this->window->setIcon(512, 512, icon.getPixelsPtr());
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
    if (event.type == sf::Event::Closed) { this->hook = Exit; return;}
    if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::Escape) { this->hook = Exit; }
        if (event.key.code == sf::Keyboard::Up && this->hook != Down) { this->hook = Up; }
        if (event.key.code == sf::Keyboard::Down && this->hook != Up) { this->hook = Down; }
        if (event.key.code == sf::Keyboard::Left && this->hook != Right) { this->hook = Left; }
        if (event.key.code == sf::Keyboard::Right && this->hook != Left) { this->hook = Right; }
        if (event.key.code == sf::Keyboard::F && this->engine != SDL) { this->hook = SDL; this->engine = SDL; }
        if (event.key.code == sf::Keyboard::G && this->engine != SFML) { this->hook = SFML; this->engine = SFML;  }

    }
}

void      Window::drawFrame(std::list <IEntity *> data,int lives, int score) const {
    sf::Color color(22,22, 24, 0);
    this->window->clear(color);
    sf::Sprite sprite;
    std::list <IEntity *>::iterator iter = data.begin();

    while (iter != data.end()) {
        sprite.setPosition(sf::Vector2f((*iter)->getPosX() * CELL_UNITY, (*iter)->getPosY() * CELL_UNITY)); // position absolue
        eTexture img = (*iter)->getTexture();
        sprite.setTexture(this->_textures.find(img)->second);
        this->window->draw(sprite);
        iter++;
    }
    this->drawMenu(lives, score);
    this->window->display();
    return;
}
void    Window::drawMenu(int lives, int score) const {
    sf::Sprite  sprite;
    int x = CELL_UNITY;
    int y = this->wHeight * CELL_UNITY + CELL_UNITY;

    sprite.setPosition(sf::Vector2f(0, this->wHeight * CELL_UNITY));
    sprite.setTexture(this->_textures.find(NoImg)->second);
    sprite.setScale(CELL_UNITY, 0.2f);
    this->window->draw(sprite);
    while (lives != 0) {
        sprite.setPosition(sf::Vector2f(x, y - CELL_UNITY /2));
        sprite.setTexture(this->_textures.find(Life)->second);
        sprite.setScale(1, 1);
        this->window->draw(sprite);
        x += CELL_UNITY + CELL_UNITY / 2;
        lives--;
    }
    sf::Text text;
    text.setFont(this->pFont);
    std::string sScore = std::to_string(score);
    text.setString(sScore.c_str());
    text.setCharacterSize(30);
    text.setFillColor(sf::Color::White);
    text.setPosition(sf::Vector2f(
        this->wWidth * CELL_UNITY - 140,
        this->wHeight * CELL_UNITY + CELL_UNITY /2
    ));
    this->window->draw(text);
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
    for (int i = 1; i <= 22; i++) {
        if (i == 5 || i == 6 || i == 7 || i == 8) {i++; continue;} // Delete this line when headmiam
        sf::Texture texture;
        std::string name = "./assets/";
        name += std::to_string(i);
        name += ".bmp";
        texture.loadFromFile(name.c_str());
        this->_textures.insert(
            std::make_pair(static_cast<eTexture>(i), texture)
        );
    }
    return;
}
