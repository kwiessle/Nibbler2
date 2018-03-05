#include "Player.hpp"
#include "Game.hpp"

Player::Player(void) { return; }

Player::Player(std::list <IEntity *> snake, int life, int score, int speed) :
  _snake(snake),
  _life(life),
  _score(score),
  _speed(speed)
{ return; }        //Use this constructor for load a saved game.

Player::~Player(void) { return; }

std::list <IEntity *>    Player::getSnake(void) const
  { return this->_snake; }

void  Player::initSnake(void) {
  printf("%p\n", Game::singleton().getBinaryLib());
  IEntity *head = createEntity(Game::singleton().getBinaryLib(), 0, 90, Snake, Right, rHead);
  this->_snake.push_front(head);
}
