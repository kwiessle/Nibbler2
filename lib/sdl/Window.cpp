#include "Window.hpp"

Window::Window(void) { return; }

Window::Window(unsigned int width, unsigned int height) {
  if (SDL_Init(SDL_INIT_VIDEO) != 0) {
    std::cout << "SDL init() failed." << std::endl;
    exit(0);
  }
  else {
    SDL_Window    *pWindow = nullptr;
    pWindow = pWindow = SDL_CreateWindow("Nibbler",
                                         SDL_WINDOWPOS_UNDEFINED,
                                         SDL_WINDOWPOS_UNDEFINED,
                                         width * CELL_UNITY,
                                         height * CELL_UNITY,
                                         SDL_WINDOW_SHOWN);
    this->pWindow = pWindow;
    this->pRenderer = SDL_CreateRenderer(pWindow, -1, SDL_RENDERER_ACCELERATED);
    std::cout << "SDL dynamicly charged" << std::endl;
  }
  return;
}

Window::~Window(void) {
  SDL_Quit();
}

int       Window::loop(void) {
  SDL_Event event;
  while (1) {
    SDL_PollEvent(&event);
    if (event.type == SDL_QUIT || event.key.keysym.sym == 27) { return -1; }
  }
  return 0;
}

Window    *createWindow(unsigned int width, unsigned int height) {
    return new Window(width, height);
}

void      deleteWindow(Window *window) {
  delete window;
}
