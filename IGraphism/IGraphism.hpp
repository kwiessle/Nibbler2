#ifndef IGRAPHISM_HPP
# define IGRAPHISM_HPP

class IGraphism {
  public:
    virtual ~IGraphism(void) { return }

      virtual void      drawFrame(std::list <Entity *> data) = 0;
};

#endif
