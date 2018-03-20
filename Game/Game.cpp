#include "Game.hpp"

Game::Game(void) {
  this->_player = new Player(4, 0);
  return;
}

Game::~Game(void) {
  delete this->_player;
}


Game   &Game::singleton(void) {
  static Game game;
  return game;
}


// GETTERS & SETTERS


IGraphism    *Game::getEngine() const
  { return this->_engine; }

void   Game::setEngine(IGraphism  *engine)
{
  this->_engine = engine;
  return;
}

std::list <IEntity *>  &Game::getFood(void) { return this->_food; }
std::list <IEntity *>  &Game::getFreePos(void) { return this->_freePos; }
std::list <IEntity *>  &Game::getWalls(void) { return this->_walls; }
std::list <IEntity *>  &Game::getFire(void) { return this->_fire; }

std::list <IEntity *>  Game::mergeEntities(void) const {
    std::list<IEntity *> tmp;
    tmp = this->_player->getSnake();
    tmp.insert(tmp.end(), this->_food.begin(), this->_food.end());
    tmp.insert(tmp.end(), this->_walls.begin(), this->_walls.end());
    tmp.insert(tmp.end(), this->_fire.begin(), this->_fire.end());
  return tmp;
}

void  Game::initFood(void) {
    std::list<IEntity *>::iterator it =
        Game::singleton().getFreePos().begin();
    std::random_device seed;
    std::mt19937 engine(seed());
    std::uniform_int_distribution<int> choose(
        0,
        static_cast<int>(Game::singleton().getFreePos().size() - 1)
    );
    std::advance(it, choose(engine));
    IEntity *food = createEntity((*it)->getPosX(), (*it)->getPosY(), Food, NoDir, tFood );
    if (this->_food.size()) {
        deleteEntity(this->_food.front());
        this->_food.pop_back();
    }
    this->listAdd(this->_food, food);
    this->listErase(this->_freePos, (*it)->getPosX(), (*it)->getPosY());
    return;
}

void  Game::initFire(void) {
    std::list<IEntity *>::iterator it =
        Game::singleton().getFreePos().begin();
    std::random_device seed;
    std::mt19937 engine(seed());
    std::uniform_int_distribution<int> choose(
        0,
        static_cast<int>(Game::singleton().getFreePos().size() - 1)
    );
    std::advance(it, choose(engine));
    IEntity *fire = createEntity((*it)->getPosX(), (*it)->getPosY(), Fire, NoDir, tFire );
    if (this->_fire.size()) {
        deleteEntity(this->_fire.front());
        this->_fire.pop_back();
    }
    this->listAdd(this->_fire, fire);
    this->listErase(this->_freePos, (*it)->getPosX(), (*it)->getPosY());
    return;
}

void  Game::initMap(unsigned int width, unsigned int height) {
    for(unsigned int x = 0; x < width; x++) {
        for (unsigned int y = 0; y < height; y++) {
            IEntity *tmp = createEntity(x, y, Free, NoDir, None);
            this->listAdd(this->_freePos, tmp);
        }
    }
    return;
}

void  Game::start(unsigned int width, unsigned int height, int mode) {
    int   tmp = 0;
    Timer frame(33);
    Timer hooks(1);
    Timer speed(200);
    Timer fire(4000);
    this->_engine = createEngine(width, height, Right);
    this->initMap(width, height);
    this->initMode(mode);
    this->_player->initSnake();
    this->initFood();
    while (1) {
      if (fire.update()) { this->initFire(); }
      if (frame.update()) { this->_engine->setHooks(); this->refresh(); }
      if (speed.update()) {
        switch(tmp = this->_engine->getHooks()) {
          case Exit : return;
          case Up : this->_player->move(Up); break;
          case Down : this->_player->move(Down); break;
          case Left : this->_player->move(Left); break;
          case Right : this->_player->move(Right); break;
          default : break;
        }
        switch(tmp = this->_engine->getHooksEngine()) {
          case SDL : switchEngine(SDL, this->_engine->getHooks()); break;
          case SFML : switchEngine(SFML, this->_engine->getHooks()); break;
          default : break;
        }
      }
    }
    return;
}

void  Game::refresh(void) {
  this->_engine->drawFrame(this->mergeEntities(), this->_player->getLife(), this->_player->getScore());
  return;
}

void Game::initMode(int mode) {
    switch(mode) {
        case 0 : break;
        case 1 : {
            for (unsigned int x = 0; x < this->_engine->getWidth(); x++) {
                this->listAdd(this->_walls, createEntity(x, 0, Wall, NoDir, tWall));
                this->listErase(this->_freePos, x, 0);
                this->listAdd(this->_walls, createEntity(x, this->_engine->getWidth() - 1, Wall, NoDir, tWall));
                this->listErase(this->_freePos, x, this->_engine->getWidth() - 1);

            }
            for (unsigned int y = 0; y < this->_engine->getHeight(); y++) {
                this->listAdd(this->_walls, createEntity(0, y, Wall, NoDir, tWall));
                this->listErase(this->_freePos, 0, y);
                this->listAdd(this->_walls, createEntity(this->_engine->getHeight() - 1, y, Wall, NoDir, tWall));
                this->listErase(this->_freePos, this->_engine->getHeight() - 1, y);
            }
        }
        default: break;
    }
    return;
}

void    Game::switchEngine(eHook engine, eHook hook) {
    unsigned int tmpWidth = this->_engine->getWidth();
    unsigned int tmpHeight = this->_engine->getHeight();
    std::string path;

    switch(engine) {
        case SDL :
            path = "lib/sdl/sdl.so";
            openBinaryLib(const_cast<char*>(path.c_str()));
            deleteEngine(this->_engine);
            this->_engine = createEngine(tmpWidth, tmpHeight, hook);
            std::cout << "SDL : " << BINARY_LIB << std::endl;
            return;
        case SFML :
            path = "lib/sfml/sfml.so";
            openBinaryLib(const_cast<char*>(path.c_str()));
            deleteEngine(this->_engine);
            this->_engine = createEngine(tmpWidth, tmpHeight, hook);
            std::cout << "SFML : " << BINARY_LIB << std::endl;
            return;
        default : return;
    }
    return;
}

void    Game::listErase(std::list <IEntity *> &list, unsigned int x, unsigned int y) {
    std::list<IEntity *>::iterator check = list.begin();
    while (check != list.end()) {
        if ((*check)->getPosX() == x && (*check)->getPosY() == y) {
            list.erase(check);
            delete *check;
            return;
        }
        check++;
    }
    return;
}

void    Game::listAdd(std::list <IEntity *> &list, IEntity *entity) {
    list.push_front(entity);
    return;
}

bool    Game::listCheck(std::list <IEntity *> &list, unsigned int x, unsigned int y) {
    std::list<IEntity *>::iterator check = list.begin();
    while (check != list.end()) {
        if ((*check)->getPosX() == x && (*check)->getPosY() == y) {
            return true;
        }
        check++;
    }
    return false;
}
// EXTERNAL FUNCTS
