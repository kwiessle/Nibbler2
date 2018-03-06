#ifndef IGRAPHISM_HPP
# define IGRAPHISM_HPP

#define CELL_UNITY 30



class IGraphism {
  public:
    virtual ~IGraphism(void) {}

      // virtual void      drawFrame(std::list <Entity *> data) = 0;
    virtual int      loop(void) const = 0;
};

#endif
