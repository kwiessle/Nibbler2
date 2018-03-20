#include "Player.hpp"
#include "Game.hpp"

Player::Player(int life, int score) :
  _life(life),
  _score(score)
 { return; }

Player::Player(std::list <IEntity *> snake, int life, int score, int speed) :
  _snake(snake),
  _life(life),
  _score(score),
  _speed(speed)
{ return; }

Player::~Player(void) { return; }

std::list <IEntity *>    Player::getSnake(void) const
  { return this->_snake; }

int Player::getLife(void) const { return this->_life; }
int Player::getScore(void) const { return this->_score; }

void  Player::initSnake(void) {
  Game::singleton().listErase(Game::singleton().getFreePos(), 6, 1);
  Game::singleton().listAdd(this->_snake, createEntity(6, 1, Snake, Right, rHead));

  Game::singleton().listErase(Game::singleton().getFreePos(), 5, 1);
  Game::singleton().listAdd(this->_snake, createEntity(5, 1, Snake, Right, hBody));

  Game::singleton().listErase(Game::singleton().getFreePos(), 4, 1);
  Game::singleton().listAdd(this->_snake, createEntity(4, 1, Snake, Right, hBody));

  Game::singleton().listErase(Game::singleton().getFreePos(), 3, 1);
  Game::singleton().listAdd(this->_snake, createEntity(3, 1, Snake, Right, hBody));

  Game::singleton().listErase(Game::singleton().getFreePos(), 2, 1);
  Game::singleton().listAdd(this->_snake, createEntity(2, 1, Snake, Right, hBody));

  Game::singleton().listErase(Game::singleton().getFreePos(), 1, 1);
  Game::singleton().listAdd(this->_snake, createEntity(1, 1, Snake, Right, rHead));

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

    switch ( queue->getDirection() ) {
      case Up :
        piece = createEntity( queue->getPosX(), queue->getPosY() + 1, Snake, queue->getDirection(), queue->getTexture() );
        break;
      case Down :
        piece = createEntity( queue->getPosX(), queue->getPosY() - 1, Snake, queue->getDirection(), queue->getTexture() );
        break;
      case Left :
        piece = createEntity( queue->getPosX() + 1, queue->getPosY(), Snake, queue->getDirection(), queue->getTexture() );
         break;
      case Right :
        piece = createEntity( queue->getPosX() - 1, queue->getPosY(), Snake, queue->getDirection(), queue->getTexture() );
        break;
      default:
        break;
    }
    Game::singleton().listAdd(this->_snake, piece);
    Game::singleton().listErase(Game::singleton().getFreePos(), piece->getPosX(),  piece->getPosY());

}

void  Player::_updateSnake(eHook direction) {
    std::list<IEntity *>::iterator iter = this->_snake.begin();
    Game::singleton().listAdd(Game::singleton().getFreePos(), createEntity((*iter)->getPosX(), (*iter)->getPosY(), Free, NoDir, None));
    Game::singleton().listErase(this->_snake, (*iter)->getPosX(), (*iter)->getPosY());

    IEntity *newHead = this->_createHead(direction);
    if (Game::singleton().listCheck(Game::singleton().getFood(), newHead->getPosX(), newHead->getPosY())) {
        this->_score++;
        this->_grow();
        Game::singleton().initFood();
    }
    if (Game::singleton().listCheck(this->_snake, newHead->getPosX(), newHead->getPosY())) {
        exit(0);
    }
    if (Game::singleton().listCheck(Game::singleton().getWalls(), newHead->getPosX(), newHead->getPosY())) {
        exit(0);
    }
    if (Game::singleton().listCheck(Game::singleton().getFire(), newHead->getPosX(), newHead->getPosY())) {
        this->_life--;
        deleteEntity(Game::singleton().getFire().front());
        Game::singleton().getFire().clear();
        if (this->_life == 0) {
            exit(0);
        }
    }
    this->_fillQueue();
    this->_fillNeck(newHead->getDirection());
    this->_snake.push_back(newHead);
    Game::singleton().listErase(Game::singleton().getFreePos(), newHead->getPosX(), newHead->getPosY());
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
            y = neck->getPosY() <= 0 ? height - 1 : neck->getPosY() - 1;
            break;
        case Down :
            x = neck->getPosX() % width;
            y = (neck->getPosY() + 1) % height;
            break;
        case Left :
            x = neck->getPosX() <= 0 ? width - 1 : neck->getPosX() - 1;
            y = neck->getPosY();
            break;
        case Right :
            x = (neck->getPosX() + 1 ) % width;
            y = neck->getPosY() % height;
            break;
        default: break;
    }
    newHead = createEntity(x, y, Snake, direction, rHead );
    return newHead;
}
