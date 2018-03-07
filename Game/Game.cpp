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
    Timer hooks(30);
    Timer speed(80);
    int   tmp = 0;
    this->_engine = createEngine(width, height);

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
