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

std::list <IEntity *>  Game::mergeEntities(void) const {
    std::list<IEntity *> tmp;
    tmp = this->_player->getSnake();
    tmp.insert(tmp.end(), this->_food.begin(), this->_food.end());
    tmp.insert(tmp.end(), this->_walls.begin(), this->_walls.end());

  return tmp;
}

void  Game::initFood(unsigned int x, unsigned int y) {
    IEntity *food = createEntity(x, y, Food, NoDir, tFood );
    if (this->_food.size()) {
        deleteEntity(this->_food.front());
        this->_food.pop_back();
    }
    this->listAdd(this->_food, food);
    this->listErase(this->_freePos, x, y);
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

void  Game::start(unsigned int width, unsigned int height) {
    int   tmp = 0;
    Timer frame(33);
    Timer hooks(1);
    Timer speed(100);
    this->_engine = createEngine(width, height);
    this->initMode(mode);
    this->initMap(width, height);
    this->_player->initSnake();
    this->initFood(1, 1);
    while (1) {
      if (frame.update()) { this->refresh(); }
      if (hooks.update()) { this->_engine->setHooks(); }
      if (speed.update()) {
        switch(tmp = this->_engine->getHooks()) {
          case Exit : return;
          case Up : this->_player->move(Up); break;
          case Down : this->_player->move(Down); break;
          case Left : this->_player->move(Left); break;
          case Right : this->_player->move(Right); break;
          case SDL : switchEngine(SDL); break;
          case SFML : switchEngine(SFML); break;
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
            for (unsigned int x = 0; x < this->_engine->getWidth(); x += CELL_UNITY) {
                this->_walls.push_back(createEntity(x, 0, Wall, NoDir, tWall));
                this->_walls.push_back(createEntity(x, this->_engine->getHeight() - CELL_UNITY, Wall, NoDir, tWall));
            }
            for (unsigned int y = 0; y < this->_engine->getHeight(); y += CELL_UNITY) {
                this->_walls.push_back(createEntity(0, y, Wall, NoDir, tWall));
                this->_walls.push_back(createEntity(this->_engine->getHeight() - CELL_UNITY, y, Wall, NoDir, tWall));
            }
        }
        default: break;
    }
    return;
}

void    Game::switchEngine(eHook engine) {
    unsigned int tmpWidth = this->_engine->getWidth() / CELL_UNITY;
    unsigned int tmpHeight = this->_engine->getHeight() / CELL_UNITY;
    std::string path;

    deleteEngine(this->_engine);
    switch(engine) {
        case SDL :
            path = "lib/sdl/sdl.so";
            openBinaryLib(const_cast<char*>(path.c_str()));
            this->_engine = createEngine(tmpWidth, tmpHeight);
            std::cout << "SDL : " << BINARY_LIB << std::endl;
            return;
        case SFML :
            path = "lib/sfml/sfml.so";
            openBinaryLib(const_cast<char*>(path.c_str()));
            this->_engine = createEngine(tmpWidth, tmpHeight);
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
