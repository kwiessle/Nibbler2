#include "Window.hpp"

Window::Window(void) { return; }

Window::Window(unsigned int width, unsigned int height) {
  if (SDL_Init(SDL_INIT_VIDEO) != 0) {
    std::cout << "SDL init() failed." << std::endl;
    exit(0);
  }
  else {
    SDL_Window    *pWindow = nullptr;
    pWindow = pWindow = SDL_CreateWindow(
      "Nibbler",
      SDL_WINDOWPOS_UNDEFINED,
      SDL_WINDOWPOS_UNDEFINED,
      width * CELL_UNITY,
      height * CELL_UNITY,
      SDL_WINDOW_SHOWN
    );

    this->pWindow = pWindow;
    this->pRenderer = SDL_CreateRenderer(pWindow, -1, SDL_RENDERER_ACCELERATED);
    std::cout << "SDL dynamicly charged" << std::endl;
  }
  return;
}

Window::~Window(void) {
  SDL_Quit();
}

int   Window::getHooks(void) const {
  SDL_Event event;
  SDL_PollEvent(&event);

  if (event.type == SDL_QUIT || event.key.keysym.sym == 27) { return -1; }
  else if (event.type == SDL_KEYDOWN) {
    if (event.key.keysym.sym == 1073741906) { return Up; }
    else if (event.key.keysym.sym == 1073741905) {  return Down; }
    else if (event.key.keysym.sym == 1073741904) {  return Left; }
    else if (event.key.keysym.sym == 1073741903) {  return Right; }
  }
  return -2;
}

void      Window::drawFrame(std::list <IEntity *> data) const {
    SDL_SetRenderDrawColor(this->pRenderer, 22, 22, 24, 0);
    SDL_RenderClear(this->pRenderer);
    SDL_Rect    form;
    SDL_Texture *texture = nullptr;
    SDL_Surface *surface = nullptr;
    IEntity *piece = nullptr;
    std::list <IEntity *>::iterator iter = data.begin();

    while (iter != data.end()) {
      piece = *iter;
      form.x = piece->getPosX();
      form.y = piece->getPosY();
      form.w = CELL_UNITY;
      form.h = CELL_UNITY;
      surface = SDL_LoadBMP( "/assets/r_head.bmp" );
      texture = SDL_CreateTextureFromSurface( this->pRenderer, surface);
      SDL_RenderCopy( this->pRenderer, texture, nullptr, &form);
      SDL_DestroyTexture( texture );
      SDL_FreeSurface( surface );
      iter++;
    }
    SDL_RenderPresent( this->pRenderer );
    return;
}

Window    *createWindow(unsigned int width, unsigned int height) {
    return new Window(width, height);
}

void      deleteWindow(Window *window) {
  delete window;
}
