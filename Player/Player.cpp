#include "Player.hpp"
#include "Game.hpp"



Player::Player(void) { return; }

Player::Player(std::list <IEntity *> snake, int life, int score, int speed) :
  _snake(snake),
  _life(life),
  _score(score),
  _speed(speed)
{ return; }

Player::~Player(void) { return; }

std::list <IEntity *>    Player::getSnake(void) const
  { return this->_snake; }

void  Player::initSnake(void) {
  IEntity *head = createEntity(90, 0, Snake, Right, rHead);
  IEntity *body = createEntity(60, 0, Snake, Right, hBody);
  IEntity *queue = createEntity(30, 0, Snake, Right, rHead);

  this->_snake.push_front(head);
  this->_snake.push_front(body);
  this->_snake.push_front(queue);
  return;
}

void  Player::move(eDirection direction) {
  //Do someting to avoid back movements; /!\ -> <-
  this->_updateSnake(direction);
  return;
}

void  Player::_updateSnake(eDirection direction) {
    (void)direction;
    // std::list <IEntity *>::iterator iter = this->_snake.begin();
    // this->_snake.pop_front();
    // deleteEntity(*iter);
    //
    // IEntity *newHead;
    // IEntity *neck = this->_snake.back();
    // unsigned int x = 0;
    // unsigned int y = 0;
    // unsigned int width = Game::singleton().getEngine().wWidth;
    // unsigned int height = Game::singleton().getEngine().wHeight;
    // switch(direction) {
    //   case Up :
    //     x = neck->x == 0 ? 720 : neck->x;
    //     y = neck->y <= 0 ? 690 : neck->y - 30;
    //     break;
    //   case Down :
    //     x = abs( neck->x % 720 );
    //     y = abs( (neck->y + 30) % 720 );
    //     break;
    //   case Left :
    //     x = neck->x <= 0 ? 690 : neck->x - 30;
    //     y = neck->y == 0 ? 720 : neck->y;
    //     break;
    //   case Right :
    //     x = abs( (neck->x + 30 ) % 720);
    //     y = abs( neck->y % 720 );
    //     break;

    // }
}
