#include "Game.hpp"

Game::Game(void) { return; }

Game::Game(IGraphism const *engine, void *binaryLib) :
  _engine(engine),
  _binaryLib(binaryLib)
{
  this->_player = new Player();
  this->initFood();
  this->_player->initSnake();


}

Game::~Game(void) {
  delete this->_player;
}

Game   &Game::operator=(Game const &rhs) {
  if (this != &rhs)
    this->_engine = rhs.getEngine();
    this->_binaryLib = rhs.getBinaryLib();
  return (*this);
}

Game   &Game::singleton(void) {
  static Game game;
  // game.setBinaryLib(BINARY_LIB);
  // game.setEngine(ENGINE);
  return game;
}


// GETTERS & SETTERS

void    *Game::getBinaryLib(void) const
  { return this->_binaryLib; }

void    Game::setBinaryLib(void *binaryLib)
 {
   this->_binaryLib = binaryLib;
   // BINARY_LIB = this->_binaryLib;
   return;
 }

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
  IEntity *food = createEntity(this->_binaryLib, 20, 20, Food, None, tFood );
  std::list <IEntity *> foodList;
  foodList.push_front(food);
  std::cout << "FOOD INITIATE" << std::endl;
  this->_food = foodList;
  return;
}

void  Game::play(void) const {
    this->_engine->loop();
    std::cout << "food-x :" << this->_food.front()->getPosX() << std::endl;
    return;
}


// EXTERNAL FUNCTS
