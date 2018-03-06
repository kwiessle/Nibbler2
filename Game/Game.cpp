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


IGraphism const   *Game::getEngine() const
  { return this->_engine; }

void   Game::setEngine(IGraphism const *engine)
{
  this->_engine = engine;
  return;
}

std::list <IEntity *>  Game::mergeEntities(void) const {
  return this->_player->getSnake();
}

void  Game::initFood(void) {
  IEntity *food = createEntity(20, 20, Food, NoDir, tFood );
  std::list <IEntity *> foodList;

  foodList.push_front(food);
  this->_food = foodList;
  return;
}

void  Game::start(unsigned int width, unsigned int height) {

    Timer frame(33);
    Timer hooks(50);

    this->_engine = createEngine(width, height);

    while (1) {
      if (frame.update()) { this->refresh(); }
      if (hooks.update()) {
        switch(this->_engine->getHooks()) {
          case -1 : return;
          case Up : printf("Up\n"); break;
          case Down : printf("Down\n"); break;
          case Left : printf("Left\n"); break;
          case Right : printf("Right\n"); break;
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


// EXTERNAL FUNCTS
