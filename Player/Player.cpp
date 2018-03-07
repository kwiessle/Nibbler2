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

void  Player::move(eHook direction) {
  this->_updateSnake(direction);
  return;
}

void  Player::_fillBody(eHook headDirection) {
    eHook neckDirection = this->_snake.back()->getDirection();

    switch ( headDirection ) {
        case Up : {
            if ( neckDirection == Right ) { this->_snake.back()->setTexture(luCorner); }
            else if ( neckDirection == Left ) { this->_snake.back()->setTexture(ruCorner); }
            else { this->_snake.back()->setTexture(vBody); }
            break;
        }
        case Down : {
            if ( neckDirection == Right ) { this->_snake.back()->setTexture(ldCorner); }
            else if ( neckDirection == Left ) { this->_snake.back()->setTexture(rdCorner); }
            else { this->_snake.back()->setTexture(vBody); }
            break;
        }
        case Left : {
            if ( neckDirection == Up ) { this->_snake.back()->setTexture(ldCorner);}
            else if ( neckDirection == Down ) { this->_snake.back()->setTexture(luCorner);}
            else { this->_snake.back()->setTexture(hBody); }
            break;
        }
        case Right : {
            if ( neckDirection == Up ) { this->_snake.back()->setTexture(rdCorner); }
            else if ( neckDirection == Down ) { this->_snake.back()->setTexture(ruCorner); }
            else { this->_snake.back()->setTexture(hBody); }
            break;
        }
        default: break;
    }
    return;
}

void    Player::_fillQueue() {
    std::list <IEntity *>::iterator iter = std::next(this->_snake.begin());
    IEntity *ass = *iter;

    switch ( ass->getDirection() ) {
        case Up: this->_snake.front()->setTexture(uQueue); break;
        case Down: this->_snake.front()->setTexture(dQueue); break;
        case Left: this->_snake.front()->setTexture(lQueue); break;
        case Right: this->_snake.front()->setTexture(rQueue); break;
        default: break;
    }
    return;
}

void  Player::_fillHead(void) {
    IEntity *head = this->_snake.back();
    switch(head->getDirection()) {
        case Up : head->setTexture(uHead); break;
        case Down : head->setTexture(dHead); break;
        case Left : head->setTexture(lHead); break;
        case Right : head->setTexture(rHead); break;
        default : break;
    }
    return;
}

void  Player::_updateSnake(eHook direction) {
    std::list <IEntity *>::iterator iter = this->_snake.begin();
    this->_snake.pop_front();
    deleteEntity(*iter);

    IEntity *newHead;
    IEntity *neck = this->_snake.back();
    unsigned int x = 0;
    unsigned int y = 0;
    unsigned int width = Game::singleton().getEngine()->getWidth();
    unsigned int height = Game::singleton().getEngine()->getHeight();
    switch(direction) {
        case Up :
            x = neck->getPosX();
            y = neck->getPosY() <= 0 ? height - CELL_UNITY : neck->getPosY() - CELL_UNITY;
            break;
        case Down :
            x = neck->getPosX() % width;
            y = (neck->getPosY() + CELL_UNITY) % height;
            break;
        case Left :
            x = neck->getPosX() <= 0 ? width - CELL_UNITY : neck->getPosX() - CELL_UNITY;
            y = neck->getPosY();
            break;
        case Right :
            x = (neck->getPosX() + CELL_UNITY ) % width;
            y = neck->getPosY() % height;
            break;
        default: break;

    }
    newHead = createEntity(x, y, Snake, direction, rHead );
    this->_fillBody(newHead->getDirection());
    this->_snake.push_back(newHead);
    return;
}
