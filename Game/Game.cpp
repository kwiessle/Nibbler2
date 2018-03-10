#include "Game.hpp"

Game::Game(void) {
  this->_player = new Player();
  this->initFood();
  this->_player->initSnake();
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

std::list <IEntity *>  Game::getFood(void) const { return this->_food; }

std::list <IEntity *>  Game::mergeEntities(void) const {
    std::list<IEntity *> tmp;
    tmp = this->_player->getSnake();
    tmp.insert(tmp.end(), this->_food.begin(), this->_food.end());
    tmp.insert(tmp.end(), this->_walls.begin(), this->_walls.end());

  return tmp;
}

void  Game::initFood(void) {
  IEntity *food = createEntity(CELL_UNITY, CELL_UNITY, Food, NoDir, tFood );
  std::list <IEntity *> foodList;

  foodList.push_front(food);
  this->_food = foodList;
  return;
}

void  Game::start(unsigned int width, unsigned int height, int mode) {

    Timer frame(33);
    Timer hooks(1);
    Timer speed(100);
    int   tmp = 0;
    this->_engine = createEngine(width, height);
    this->initMode(mode);

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
  this->_engine->drawFrame(this->mergeEntities());
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


// EXTERNAL FUNCTS
