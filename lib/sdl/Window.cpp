#include "Window.hpp"

Window::Window(void) { return; }

Window::Window(unsigned int width, unsigned int height) :
  wWidth(width * CELL_UNITY),
  wHeight(height * CELL_UNITY),
  hook(Right),
  engine(SDL)
 {
  if (SDL_Init(SDL_INIT_VIDEO) != 0 || TTF_Init() != 0) {
    std::cout << "SDL init() failed." << std::endl;
    exit(0);
  }
  else {
    SDL_Window    *pWindow = nullptr;
    pWindow = SDL_CreateWindow(
      "Nibbler",
      SDL_WINDOWPOS_UNDEFINED,
      SDL_WINDOWPOS_UNDEFINED,
      this->wWidth,
      this->wHeight + CELL_UNITY * 2,
      SDL_WINDOW_SHOWN
    );
    this->pWindow = pWindow;
    this->pRenderer = SDL_CreateRenderer(pWindow, -1, SDL_RENDERER_ACCELERATED);
    SDL_Surface *icon = SDL_LoadBMP("/assets/appicon.bmp");
    SDL_SetWindowIcon(pWindow, icon);
    SDL_FreeSurface(icon);
    this->initTextures();
    this->pFont = TTF_OpenFont("/assets/roboto.ttf", 35);
  }
  return;
}

Window::~Window(void) {
  SDL_Quit();
}

eHook   Window::getHooks(void) const {
    return this->hook;
}

void   Window::setHooks(void) {
  SDL_Event event;
  SDL_PollEvent(&event);

  if (event.type == SDL_QUIT || event.key.keysym.sym == 27) { this->hook = Exit; }
  else if (event.type == SDL_KEYDOWN) {
    if (event.key.keysym.sym == 1073741906 && this->hook != Down) { this->hook = Up; }
    else if (event.key.keysym.sym == 1073741905  && this->hook != Up) { this->hook = Down; }
    else if (event.key.keysym.sym == 1073741904 && this->hook != Right) { this->hook = Left; }
    else if (event.key.keysym.sym == 1073741903 && this->hook != Left) { this->hook = Right; }
    else if (event.key.keysym.sym == 102 && this->engine != SDL) { this->hook = SDL; this->engine = SDL;}
    else if (event.key.keysym.sym == 103 && this->engine != SFML) { this->hook = SFML; this->engine = SFML;}

  }
}

void      Window::drawFrame(std::list <IEntity *> data) const {
    SDL_SetRenderDrawColor(this->pRenderer, 22, 22, 24, 0);
    SDL_RenderClear(this->pRenderer);
    SDL_Rect    form;
    SDL_Texture *texture = nullptr;
    std::list <IEntity *>::iterator iter = data.begin();

    while (iter != data.end()) {
      form.x = (*iter)->getPosX();
      form.y = (*iter)->getPosY();
      form.w = CELL_UNITY;
      form.h = CELL_UNITY;
      eTexture img = (*iter)->getTexture();

      texture = SDL_CreateTextureFromSurface( this->pRenderer, this->_textures.find(img)->second );
      SDL_RenderCopy( this->pRenderer, texture, nullptr, &form);
      SDL_DestroyTexture( texture );
      iter++;
    }
    this->drawMenu(3);
    SDL_RenderPresent( this->pRenderer );
    return;
}

void    Window::drawMenu(int lives) const {
  SDL_Rect    form;
  SDL_Surface *surface = nullptr;
  SDL_Texture *texture = nullptr;
  int x = CELL_UNITY;
  int y = this->wHeight + CELL_UNITY;

  form.x = 0;
  form.y = this->wHeight;
  form.w = this->wWidth;
  form.h = CELL_UNITY * 2;
  texture = SDL_CreateTextureFromSurface(this->pRenderer, this->_textures.find(NoImg)->second);
  SDL_RenderCopy(this->pRenderer, texture, nullptr, &form);
  SDL_DestroyTexture(texture);

  while (lives != 0) {
    form.x = x;
    form.y = y - CELL_UNITY / 2;
    form.w = 30;
    form.h = 30;
    texture = SDL_CreateTextureFromSurface( this->pRenderer, this->_textures.find(Life)->second );
    SDL_RenderCopy(this->pRenderer, texture, nullptr, &form);
    SDL_DestroyTexture(texture);
    lives--;
    x += CELL_UNITY + CELL_UNITY / 2;
  }

  SDL_Color White = {255, 255, 255, 0};
  surface = TTF_RenderText_Blended(this->pFont, "666", White);
  texture = SDL_CreateTextureFromSurface(this->pRenderer, surface);
  form.x =  this->wWidth - 140;
  form.y = this->wHeight + CELL_UNITY / 2;
  form.w = 40;
  form.h = 30;
  SDL_RenderCopy(this->pRenderer, texture, nullptr, &form);
  SDL_FreeSurface(surface);
  return;
}

unsigned int    Window::getWidth(void) const {
    return this->wWidth;
}

unsigned int    Window::getHeight(void) const {
    return this->wHeight;
}

void       Window::initTextures(void) {
    eTexture texture;

    for (int i = 1; i <= 22; i++) {
        if (i == 5 || i == 6 || i == 7 || i == 8) {i++; continue;} // Delete this line when headmiam
        std::string name = "/assets/";
        name += std::to_string(i);
        name += ".bmp";
        this->_textures.insert(std::make_pair(static_cast<eTexture>(i), SDL_LoadBMP(name.c_str())));
    }
    return;
}

Window    *createWindow(unsigned int width, unsigned int height) {
    return new Window(width, height);
}

void      deleteWindow(Window *window) {
  delete window;
}
