#include "Window.hpp"

Window::Window(void) { return; }

Window::Window(unsigned int width, unsigned int height) :
  wWidth(width * CELL_UNITY),
  wHeight(height * CELL_UNITY),
  hook(Right)
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
      this->wHeight + CELL_UNITY,
      SDL_WINDOW_SHOWN
    );
    this->pWindow = pWindow;
    this->pRenderer = SDL_CreateRenderer(pWindow, -1, SDL_RENDERER_ACCELERATED);
    SDL_Surface *icon = SDL_LoadBMP("/assets/appicon.bmp");
    SDL_SetWindowIcon(pWindow, icon);
    SDL_FreeSurface(icon);
    this->initTextures();
    this->pFont = TTF_OpenFont("/assets/roboto.ttf",35);
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
  int y = this->wHeight;

  form.x = 0;
  form.y = this->wHeight - CELL_UNITY;
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
  surface = TTF_RenderText_Blended(this->pFont, "754", White);
  texture = SDL_CreateTextureFromSurface(this->pRenderer, surface);
  form.x =  this->wWidth - 140;
  form.y = this->wHeight - 15;
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

Window    *createWindow(unsigned int width, unsigned int height) {
    return new Window(width, height);
}

void      deleteWindow(Window *window) {
  delete window;
}

void       Window::initTextures(void) {
    SDL_Surface *uHeadSurf = SDL_LoadBMP("/assets/u_head30.bmp");
    SDL_Surface *dHeadSurf = SDL_LoadBMP("/assets/d_head30.bmp");
    SDL_Surface *lHeadSurf = SDL_LoadBMP("/assets/l_head30.bmp");
    SDL_Surface *rHeadSurf = SDL_LoadBMP("/assets/r_head30.bmp");
    SDL_Surface *uHeadMiamSurf = SDL_LoadBMP("/assets/u_head_miam.bmp");
    SDL_Surface *dHeadMiamSurf = SDL_LoadBMP("/assets/d_head_miam.bmp");
    SDL_Surface *lHeadMiamSurf = SDL_LoadBMP("/assets/l_head_miam.bmp");
    SDL_Surface *rHeadMiamSurf = SDL_LoadBMP("/assets/r_head_miam.bmp");
    SDL_Surface *uQueueSurf = SDL_LoadBMP("/assets/u_queue30.bmp");
    SDL_Surface *dQueueSurf = SDL_LoadBMP("/assets/d_queue30.bmp");
    SDL_Surface *lQueueSurf = SDL_LoadBMP("/assets/l_queue30.bmp");
    SDL_Surface *rQueueSurf = SDL_LoadBMP("/assets/r_queue30.bmp");
    SDL_Surface *luCornerSurf = SDL_LoadBMP("/assets/lu_corner30.bmp");
    SDL_Surface *ldCornerSurf = SDL_LoadBMP("/assets/ld_corner30.bmp");
    SDL_Surface *ruCornerSurf = SDL_LoadBMP("/assets/ru_corner30.bmp");
    SDL_Surface *rdCornerSurf = SDL_LoadBMP("/assets/rd_corner30.bmp");
    SDL_Surface *hBodySurf = SDL_LoadBMP("/assets/h_body30.bmp");
    SDL_Surface *vBodySurf = SDL_LoadBMP("/assets/v_body30.bmp");
    SDL_Surface *NoneSurf = SDL_LoadBMP("/assets/none.bmp");
    SDL_Surface *LifeSurf = SDL_LoadBMP("/assets/life.bmp");
    this->_textures.insert(std::make_pair(uHead, uHeadSurf));
    this->_textures.insert(std::make_pair(dHead, dHeadSurf));
    this->_textures.insert(std::make_pair(lHead, lHeadSurf));
    this->_textures.insert(std::make_pair(rHead, rHeadSurf));
    this->_textures.insert(std::make_pair(uHeadMiam, uHeadMiamSurf));
    this->_textures.insert(std::make_pair(dHeadMiam, dHeadMiamSurf));
    this->_textures.insert(std::make_pair(lHeadMiam, lHeadMiamSurf));
    this->_textures.insert(std::make_pair(rHeadMiam, rHeadMiamSurf));
    this->_textures.insert(std::make_pair(uQueue, uQueueSurf));
    this->_textures.insert(std::make_pair(dQueue, dQueueSurf));
    this->_textures.insert(std::make_pair(lQueue, lQueueSurf));
    this->_textures.insert(std::make_pair(rQueue, rQueueSurf));
    this->_textures.insert(std::make_pair(luCorner, luCornerSurf));
    this->_textures.insert(std::make_pair(ldCorner, ldCornerSurf));
    this->_textures.insert(std::make_pair(ruCorner, ruCornerSurf));
    this->_textures.insert(std::make_pair(rdCorner, rdCornerSurf));
    this->_textures.insert(std::make_pair(hBody, hBodySurf));
    this->_textures.insert(std::make_pair(vBody, vBodySurf));
    this->_textures.insert(std::make_pair(NoImg, NoneSurf));
    this->_textures.insert(std::make_pair(Life, LifeSurf));
    return;
}
