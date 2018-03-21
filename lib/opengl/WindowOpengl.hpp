#ifndef WINDOWOPENGL_HPP
# define WINDOWOPENGL_HPP

# include <GL/glew.h>
# include <GLFW/glfw3.h>
# include <GLUT/glut.h>
# include <iostream>
// # include <stdio.h>
# include <map>

# include "IGraphism.hpp"
# include "IEntity.hpp"


class Window  : public IGraphism {
private:
  Window(void);

  void            drawFrame(std::list <IEntity *> data) const;
  // void            drawMenu(int lives) const;
  eHook           getHooks(void) const;
  eEngine         getEngine(void) const;
  bool            engineHasChanged(void) const;
  void            setHooks(void);
  unsigned int    getWidth(void) const;
  unsigned int    getHeight(void) const;
  void            initTextures(void);
  GLuint          loadBMP(const char * imagepath) const;
public:
  Window(unsigned int width, unsigned int height, eHook hook);
  ~Window(void);
  eHook                               hook;
  eEngine                             engine;
  bool                                engineChecker;
  unsigned int                        wWidth;
  unsigned int                        wHeight;
  GLFWwindow                         *pWindow;
  // sf::Font                            pFont;
  std::map <eTexture,  GLuint>   _textures;


};

extern "C" {
Window              *createWindow(unsigned int width, unsigned int height, eHook hook);
void                 deleteWindow(Window *window);
}

#endif
