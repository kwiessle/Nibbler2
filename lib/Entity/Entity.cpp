#include "Entity.hpp"

Entity::Entity(void) { return; }

Entity::Entity(unsigned int x, unsigned int y, eType type, eHook direction, eTexture texture) :
  _posX(x),
  _posY(y),
  _type(type),
  _direction(direction),
  _texture(texture)
  { return; }

Entity::~Entity(void) { return; }


// GETTERS & SETTERS

unsigned int    Entity::getPosX(void) const
                  { return this->_posX; }

unsigned int    Entity::getPosY(void) const
                  { return this->_posY; }

eType           Entity::getType(void) const
                  { return this->_type; }

eHook      Entity::getDirection(void) const
                  { return this->_direction; }

eTexture        Entity::getTexture(void) const
                  { return this->_texture; }

void            Entity::setPosX(unsigned int x)
                  { this->_posX = x; return; }

void            Entity::setPosY(unsigned int y)
                  { this->_posY = y; return; }

void            Entity::setType(eType type)
                  { this->_type = type; return; }

void            Entity::setDirection(eHook direction)
                  { this->_direction = direction; return; }

void            Entity::setTexture(eTexture texture)
                  { this->_texture = texture; return; }


// MEMBER FUNCTS

void            Entity::randomizePosition(void) { return; }

// EXTERNAL FUNCS

Entity          *createEntity(unsigned int x, unsigned int y, eType type, eHook direction, eTexture texture) {
  return new Entity(x, y, type, direction, texture);
}

void            deleteEntity(Entity *entity) {
  delete entity;
  return;
}
