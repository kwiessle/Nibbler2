#include "Game.hpp"

// Game::Game(void) { return; }


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
  // game.setBinaryLib(BINARY_LIB);
  // game.setEngine(ENGINE);
  return game;
}


// GETTERS & SETTERS


IGraphism const   *Game::getEngine() const
  { return this->_engine; }

void   Game::setEngine(IGraphism const *engine)
{
  this->_engine = engine;
  // ENGINE = this->_engine;
  return;
}

std::list <IEntity *>  Game::mergeEntities(void) const {
  return this->_player->getSnake();
}

void  Game::initFood(void) {
  IEntity *food = createEntity(BINARY_LIB, 20, 20, Food, NoDir, tFood );
  std::list <IEntity *> foodList;
  foodList.push_front(food);
  std::cout << "FOOD INITIATE" << std::endl;
  this->_food = foodList;
  return;
}

void  Game::start(unsigned int width, unsigned int height) {
    printf("%p\n", BINARY_LIB);
    this->_engine = createEngine(BINARY_LIB, width, height);
    this->_engine->loop();
    std::cout << "food-x :" << this->_food.front()->getPosX() << std::endl;
    return;
}


// EXTERNAL FUNCTS
