#ifndef IGRAPHISM_HPP
# define IGRAPHISM_HPP

# define CELL_UNITY 30

# include <list>
# include "IEntity.hpp"

class IGraphism {
  public:
    virtual ~IGraphism(void) {}

    virtual void      drawFrame(std::list <IEntity *> data) const = 0;
    virtual int       getHooks(void) const = 0;
};

#endif
