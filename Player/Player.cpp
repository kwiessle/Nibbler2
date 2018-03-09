#include "Player.hpp"
#include "Game.hpp"
#include <random>

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
  IEntity *head = createEntity(150, 0, Snake, Right, rHead);
  IEntity *body = createEntity(120, 0, Snake, Right, hBody);
  IEntity *body2 = createEntity(90, 0, Snake, Right, hBody);
  IEntity *body3 = createEntity(60, 0, Snake, Right, hBody);
  IEntity *body4 = createEntity(30, 0, Snake, Right, hBody);
  IEntity *queue = createEntity(0, 0, Snake, Right, rHead);
  std::list<IEntity *>::iterator check = Game::singleton()._map.begin();
  while (check != Game::singleton()._map.end()) {
      if ((*check)->getPosX() == 0 && (*check)->getPosY() == 0) {
          Game::singleton()._map.erase(check);
      }
      if ((*check)->getPosX() == 30 && (*check)->getPosY() == 0) {
          Game::singleton()._map.erase(check);
      }
      if ((*check)->getPosX() == 60 && (*check)->getPosY() == 0) {
          Game::singleton()._map.erase(check);
      }
      if ((*check)->getPosX() == 90 && (*check)->getPosY() == 0) {
          Game::singleton()._map.erase(check);
      }
      if ((*check)->getPosX() == 120 && (*check)->getPosY() == 0) {
          Game::singleton()._map.erase(check);
      }
      if ((*check)->getPosX() == 150 && (*check)->getPosY() == 0) {
          Game::singleton()._map.erase(check);
      }
      check++;
  }
  this->_snake.push_front(head);
  this->_snake.push_front(body);
  this->_snake.push_front(body2);
  this->_snake.push_front(body3);
  this->_snake.push_front(body4);
  this->_snake.push_front(queue);
  return;
}

void  Player::move(eHook direction) {
  this->_updateSnake(direction);
  return;
}

void  Player::_fillNeck(eHook headDirection) {
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

void  Player::_grow(void) {
    IEntity *queue = this->_snake.front();
    IEntity *piece = nullptr;
    std::list<IEntity *>::iterator check = Game::singleton()._map.begin();
    switch ( queue->getDirection() ) {
      case Up :
        piece = createEntity( queue->getPosX(), queue->getPosY() + 30, Snake, queue->getDirection(), queue->getTexture() );
        while (check != Game::singleton()._map.end()) {
            if ((*check)->getPosX() == queue->getPosX() && (*check)->getPosY() == queue->getPosY() + 30) {
                Game::singleton()._map.erase(check);
            }
            check++;
        }
        break;
      case Down :
        piece = createEntity( queue->getPosX(), queue->getPosY() - 30, Snake, queue->getDirection(), queue->getTexture() );

        while (check != Game::singleton()._map.end()) {
            if ((*check)->getPosX() == queue->getPosX() && (*check)->getPosY() == queue->getPosY() - 30) {
                Game::singleton()._map.erase(check);
            }
            check++;
        }
        break;
      case Left :
        piece = createEntity( queue->getPosX() + 30, queue->getPosY(), Snake, queue->getDirection(), queue->getTexture() );

        while (check != Game::singleton()._map.end()) {
            if ((*check)->getPosX() == queue->getPosX() + 30 && (*check)->getPosY() == queue->getPosY()) {
                Game::singleton()._map.erase(check);
            }
            check++;
        }
         break;
      case Right :
        piece = createEntity( queue->getPosX() - 30, queue->getPosY(), Snake, queue->getDirection(), queue->getTexture() );

        while (check != Game::singleton()._map.end()) {
            if ((*check)->getPosX() == queue->getPosX() - 30 && (*check)->getPosY() == queue->getPosY()) {
                Game::singleton()._map.erase(check);
            }
            check++;
        }
         break;
      default:
        break;
    }
    this->_snake.push_front( piece );
}

void  Player::_updateSnake(eHook direction) {
    std::list<IEntity *>::iterator iter = this->_snake.begin();
    Game::singleton()._map.push_front(createEntity((*iter)->getPosX(), (*iter)->getPosY(), Free, NoDir, None));
    this->_snake.pop_front();
    deleteEntity(*iter);
    IEntity *newHead = this->_createHead(direction);
    if (newHead->getPosX() == Game::singleton().getFood().front()->getPosX() &&
        newHead->getPosY() == Game::singleton().getFood().front()->getPosY()) {
        this->_score++;
        this->_grow();
        std::list<IEntity *>::iterator it = Game::singleton()._map.begin();
        std::random_device seed;
        std::mt19937 engine(seed());
        std::uniform_int_distribution<int> choose(0, static_cast<int>(Game::singleton()._map.size() - 1));
        std::advance(it, choose(engine));
        Game::singleton().initFood((*it)->getPosX() / CELL_UNITY
        , (*it)->getPosY() / CELL_UNITY
        );
    }
    this->_fillQueue();
    this->_fillNeck(newHead->getDirection());
    this->_snake.push_back(newHead);
    this->_fillHead();
    return;
}

IEntity *   Player::_createHead(eHook direction) {
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
    std::list<IEntity *>::iterator check = Game::singleton()._map.begin();
    while (check != Game::singleton()._map.end()) {
        if ((*check)->getPosX() == x && (*check)->getPosY() == y) {
            Game::singleton()._map.erase(check);
        }
        check++;
    }
    return newHead;
}
