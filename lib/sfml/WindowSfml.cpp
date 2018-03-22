#include "WindowSfml.hpp"

Window::Window(void) { return; }

Window::Window(unsigned int width, unsigned int height, eHook hook) :
 wWidth(width),
 wHeight(height),
 engine(SFML),
 engineChecker(false),
 hook(hook)
{
    sf::Image icon;
    this->window = new sf::RenderWindow(
        sf::VideoMode(
            this->wWidth * CELL_UNITY,
            this->wHeight * CELL_UNITY + CELL_UNITY * 2),
        "Nibbler"
    );
    this->initTextures();
    this->pFont.loadFromFile("./assets/roboto.ttf");
    icon.loadFromFile("./assets/appicon.bmp");
    this->window->setIcon(512, 512, icon.getPixelsPtr());
    return;
}

Window::~Window(void) {
    this->window->close();
    // delete this->window;
}

eHook   Window::getHooks(void) const {
    return this->hook;
}

eHook   Window::getStatus(void) const {
    return this->status;
}
void   Window::setStatus(eHook status)  {
    this->status = status;
    return;
}

eEngine  Window::getEngine(void) const {
    return this->engine;
}

bool    Window::engineHasChanged(void) const{
    return this->engineChecker;
}

void   Window::setHooks(void) {
    sf::Event   event;
    this->window->pollEvent(event);

    if (event.type == sf::Event::Closed) { this->status = Exit;}
    else if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::Escape) { this->status = Exit; }
        else if (event.key.code == sf::Keyboard::Space)
            { this->status = Pause; }
        else if (event.key.code == sf::Keyboard::Up && this->hook != Down)
            { this->hook = Up; }
        else if (event.key.code ==sf::Keyboard::Down  && this->hook != Up)
            { this->hook = Down; }
        else if (event.key.code == sf::Keyboard::Left && this->hook != Right)
            { this->hook = Left; }
        else if (event.key.code == sf::Keyboard::Right && this->hook != Left)
            { this->hook = Right; }
        else if (event.key.code == sf::Keyboard::F && this->engine != SDL)
            {  this->engine = SDL; this->engineChecker = true; }
        else if (event.key.code == sf::Keyboard::G && this->engine != SFML)
            { this->engine = SFML; this->engineChecker = true;}
    }
    return;
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
        sprite.setPosition(sf::Vector2f(x, y - CELL_UNITY / 2));
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

bool            Window::displayPause(int status)  {
    sf::Color color(22,22, 24, 0);
    sf::Event event;
    sf::Texture img;
    sf::Sprite background;
    sf::RectangleShape  start;
    sf::RectangleShape  resume;
    sf::RectangleShape  exit;

    background.setPosition(sf::Vector2f(0, 0));
    img.loadFromFile("./assets/appicon.bmp");
    background.setTexture(img);
    background.setScale(CELL_UNITY * wWidth / 512, CELL_UNITY * wHeight / 512);
    this->window->clear(color);
    this->window->draw(background);
    switch (status) {
        case 2 :
            resume = this->drawResume(color);
        case 1 :
            start = this->drawStart(color);
            exit = this->drawExit(color);
            break;
    }
    this->window->display();
    this->window->pollEvent(event);
    if (event.type == sf::Event::MouseButtonPressed) {
        sf::Vector2i mousePos = sf::Mouse::getPosition( *this->window );
        sf::Vector2f mousePosF( static_cast<float>( mousePos.x ), static_cast<float>( mousePos.y ) );
        if ( resume.getGlobalBounds().contains( mousePosF ) ) {
            this->status = NoDir;
            return false;
        }
        if ( exit.getGlobalBounds().contains( mousePosF ) ) {
            this->status = Exit;
            return false;
        }
        if ( start.getGlobalBounds().contains( mousePosF ) ) {
             this->status = Start;
            return false;
        }
    }
    else if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::Escape) { this->status = Exit; }
        else if (event.key.code == sf::Keyboard::F && this->engine != SDL)
            { this->engine = SDL; this->engineChecker = true; }
        else if (event.key.code == sf::Keyboard::G && this->engine != SFML)
            { this->engine = SFML; this->engineChecker = true; }
    }
    return true;
}

sf::RectangleShape            Window::drawStart(sf::Color color) const {
    sf::RectangleShape start;
    start.setSize(sf::Vector2f(CELL_UNITY * 3, CELL_UNITY * 2));
    start.setOutlineColor(sf::Color::Red);
    start.setOutlineThickness(5);
    start.setPosition(wWidth * CELL_UNITY / 4 , wHeight * CELL_UNITY / 2 - CELL_UNITY);
    start.setFillColor(color);
    this->window->draw(start);
    return start;
}

sf::RectangleShape            Window::drawResume(sf::Color color) const {
    sf::RectangleShape resume;
    resume.setSize(sf::Vector2f(CELL_UNITY * 3, CELL_UNITY * 2));
    resume.setOutlineColor(sf::Color::Red);
    resume.setOutlineThickness(5);
    resume.setPosition((wWidth * CELL_UNITY / 4) * 2 , wHeight * CELL_UNITY / 2 - CELL_UNITY);
    resume.setFillColor(color);
    this->window->draw(resume);
    return resume;
}
sf::RectangleShape            Window::drawExit(sf::Color color) const {
    sf::RectangleShape exit;
    exit.setSize(sf::Vector2f(CELL_UNITY * 3, CELL_UNITY * 2));
    exit.setOutlineColor(sf::Color::Red);
    exit.setOutlineThickness(5);
    exit.setPosition((wWidth * CELL_UNITY /4) * 3, wHeight * CELL_UNITY / 2 - CELL_UNITY);
    exit.setFillColor(color);
    this->window->draw(exit);
    return exit;
}
unsigned int    Window::getWidth(void) const {
    return this->wWidth;
}

unsigned int    Window::getHeight(void) const {
    return this->wHeight;
}

Window      *createWindow(unsigned int width, unsigned int height, eHook hook) {
    return new Window(width, height, hook);
}

void        deleteWindow(Window *window) {
    delete window;
}

void       Window::initTextures(void) {
    for (int i = 1; i <= 23; i++) {
        if (i >= 5 && i <= 8) {i++; continue;} // Delete this line when headmiam
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
