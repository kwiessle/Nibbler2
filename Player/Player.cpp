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
  printf("%p\n", BINARY_LIB);
  IEntity *head = createEntity(90, 0, Snake, Right, rHead);
  IEntity *body = createEntity(60, 0, Snake, Right, hBody);
  IEntity *queue = createEntity(30, 0, Snake, Right, rHead);

  this->_snake.push_front(head);
  this->_snake.push_front(body);
  this->_snake.push_front(queue);
  return;
}
