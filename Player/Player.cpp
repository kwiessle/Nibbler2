#include "Player.hpp"
#include "Game.hpp"

Player::Player(int life, int score) :
  _life(life),
  _score(score),
  _dead(true),
  _scoreChange(false)
 { return; }

Player::Player(std::list <IEntity *> snake, int life, int score, int speed) :
  _snake(snake),
  _life(life),
  _score(score),
  _speed(speed),
  _dead(true),
  _scoreChange(false)
{ return; }

Player::Player(Player const &src) { *this = src; }

Player::~Player(void) {
    std::list<IEntity *>::iterator it = this->_snake.begin();
    while (it != this->_snake.end()) {
        deleteEntity(*it);
        it++;
    }
    return;
}

Player    &Player::operator=(Player const &) { return *this; }

std::list <IEntity *>    Player::getSnake(void) const
  { return this->_snake; }

bool    Player::checkDeath(void) const { return this->_dead; }
int     Player::getLife(void) const { return this->_life; }
int     Player::getScore(void) const { return this->_score; }
bool    Player::getScoreChange(void) const { return this->_scoreChange; }

void  Player::initSnake(void) {
    Game &singleton = Game::singleton();

    singleton.listErase(singleton.getFreePos(), 3, 1);
    singleton.listAdd(this->_snake, createEntity(3, 1, Snake, Right, rHead));

    singleton.listErase(singleton.getFreePos(), 2, 1);
    singleton.listAdd(this->_snake, createEntity(2, 1, Snake, Right, hBody));

    singleton.listErase(singleton.getFreePos(), 1, 1);
    singleton.listAdd(this->_snake, createEntity(1, 1, Snake, Right, rQueue));
    this->_dead = false;
    return;
}

void  Player::move(eDirection direction) {
  this->_updateSnake(direction);
  return;
}

void  Player::_fillNeck(eDirection headDirection) {
    eDirection neckDirection = this->_snake.back()->getDirection();

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
    Game &singleton = Game::singleton();
    IEntity *head = this->_snake.back();
    switch(head->getDirection()) {
        case Up : {
            if (singleton.listCheck(singleton.getFood(), head->getPosX(), head->getPosY() -1) ||
            singleton.listCheck(singleton.getBonus(), head->getPosX(), head->getPosY() -1))
                head->setTexture(uHeadMiam);
            else { head->setTexture(uHead); }
            break;
        }
        case Down : {
            if (singleton.listCheck(singleton.getFood(), head->getPosX(), head->getPosY() + 1 ) ||
            singleton.listCheck(singleton.getBonus(), head->getPosX(), head->getPosY() + 1 ))
                head->setTexture(dHeadMiam);
            else { head->setTexture(dHead); }
            break;
        }
        case Left : {
            if (singleton.listCheck(singleton.getFood(), head->getPosX() - 1, head->getPosY()) ||
            singleton.listCheck(singleton.getBonus(), head->getPosX() - 1, head->getPosY()))
                head->setTexture(lHeadMiam);
            else { head->setTexture(lHead); }
            break;
        }
        case Right : {
            if (singleton.listCheck(singleton.getFood(), head->getPosX() + 1, head->getPosY()) ||
            singleton.listCheck(singleton.getBonus(), head->getPosX() + 1, head->getPosY()))
                head->setTexture(rHeadMiam);
            else { head->setTexture(rHead); }
            break;
        }
        default : break;
    }
    return;
}

void  Player::_grow(void) {
    IEntity *queue = this->_snake.front();
    IEntity *piece = nullptr;
    Game &singleton = Game::singleton();
    switch ( queue->getDirection() ) {
      case Up :
        piece = createEntity(queue->getPosX(), queue->getPosY() + 1, Snake, queue->getDirection(), queue->getTexture() );
        break;
      case Down :
        piece = createEntity(queue->getPosX(), queue->getPosY() - 1, Snake, queue->getDirection(), queue->getTexture() );
        break;
      case Left :
        piece = createEntity(queue->getPosX() + 1, queue->getPosY(), Snake, queue->getDirection(), queue->getTexture() );
        break;
      case Right :
        piece = createEntity(queue->getPosX() - 1, queue->getPosY(), Snake, queue->getDirection(), queue->getTexture() );
        break;
      default:
        break;
    }
    singleton.listAdd(this->_snake, piece);
    singleton.listErase(singleton.getFreePos(), piece->getPosX(),  piece->getPosY());
}

void  Player::_updateSnake(eDirection direction) {
    Game &singleton = Game::singleton();
    IEntity *newHead = this->_createHead(direction);
    std::list<IEntity *>::iterator iter = this->_snake.begin();
    singleton.listAdd(singleton.getFreePos(), createEntity((*iter)->getPosX(), (*iter)->getPosY(), Free, NoDir, None));
    singleton.listErase(this->_snake, (*iter)->getPosX(), (*iter)->getPosY());
    this->_scoreChange = false;
    if (singleton.listCheck(singleton.getFood(), newHead->getPosX(), newHead->getPosY())) {
        this->_score++;
        this->_scoreChange = true;
        this->_grow();
        singleton.initFood();
        singleton.coreAudio->play(Croc);
    }
    else if (singleton.listCheck(singleton.getBonus(), newHead->getPosX(), newHead->getPosY())) {
        this->_score += 5;
        this->_scoreChange = true;
        this->_grow();
        deleteEntity(singleton.getBonus().front());
        singleton.getBonus().clear();
        singleton.coreAudio->play(Croc);
    }
    else if (singleton.listCheck(this->_snake, newHead->getPosX(), newHead->getPosY())) {
        singleton.getEngine()->updateStatus(Pause);
        this->_dead = true;
        singleton.coreAudio->play(Failure);
    }
    else if (singleton.listCheck(singleton.getWalls(), newHead->getPosX(), newHead->getPosY())) {
        singleton.getEngine()->updateStatus(Pause);
        this->_dead = true;
        singleton.coreAudio->play(Damage);
        singleton.coreAudio->play(Failure);
    }
    else if (singleton.listCheck(singleton.getFire(), newHead->getPosX(), newHead->getPosY())) {
        this->_life--;
        deleteEntity(singleton.getFire().front());
        singleton.getFire().clear();
        singleton.coreAudio->play(Damage);
        if (this->_life == 0) {
            singleton.getEngine()->updateStatus(Pause);
            this->_dead = true;
            singleton.coreAudio->play(Failure);
        }
    }
    this->_fillQueue();
    this->_fillNeck(newHead->getDirection());
    this->_snake.push_back(newHead);
    singleton.listErase(singleton.getFreePos(), newHead->getPosX(), newHead->getPosY());
    this->_fillHead();
    return;
}

IEntity *   Player::_createHead(eDirection direction) {
    Game &singleton = Game::singleton();
    IEntity *neck = this->_snake.back();
    unsigned int x = 0;
    unsigned int y = 0;
    unsigned int width = singleton.getEngine()->getWidth();
    unsigned int height = singleton.getEngine()->getHeight();

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
    IEntity *newHead = createEntity(x, y, Snake, direction, rHead);
    return newHead;
}
