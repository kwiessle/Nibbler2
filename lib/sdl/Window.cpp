#include "Window.hpp"

Window::Window(void) { return; }

Window::Window(unsigned int width, unsigned int height, eHook hook) :
  wWidth(width),
  wHeight(height),
  engine(SDL),
  engineChecker(false),
  hook(hook)
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
      this->wWidth * CELL_UNITY,
      this->wHeight * CELL_UNITY + CELL_UNITY * 2,
      SDL_WINDOW_RESIZABLE
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
    SDL_RenderClear(this->pRenderer);
    std::map<eTexture, SDL_Surface *>::iterator it = this->_textures.begin();
    while (it != this->_textures.end()) {
        if (it->first >= 5 && it->first <= 8) {it++; continue;}
        SDL_FreeSurface(it->second);
        it++;
    }
    TTF_CloseFont(this->pFont);
    TTF_Quit();
    this->_textures.clear();
    SDL_DestroyRenderer(this->pRenderer);
    SDL_DestroyWindow(this->pWindow);
    SDL_Quit();
}

eHook   Window::getHooks(void) const {
    return this->hook;
}

eHook   Window::getStatus(void) const {
    return this->status;
}

void   Window::setStatus(eHook status) {
    this->status = status;
    return;
}

eEngine  Window::getEngine(void) const {
    return this->engine;
}
void    Window::changeHook(eHook hook){
    this->hook = hook;
}

bool    Window::engineHasChanged(void) const{
    return this->engineChecker;
}

void   Window::setHooks(void) {
    SDL_Event event;

    while(SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT ||
         (event.type == SDL_KEYDOWN && event.key.keysym.sym == 27))
            { this->status = Exit; }
        else if (event.type == SDL_KEYDOWN) {
            if (event.key.keysym.sym == SDLK_UP && this->hook != Down)
                { this->hook = Up; }
            else if (event.key.keysym.sym == SDLK_DOWN  && this->hook != Up)
                { this->hook = Down; }
            else if (event.key.keysym.sym == SDLK_LEFT && this->hook != Right)
                { this->hook = Left; }
            else if (event.key.keysym.sym == SDLK_RIGHT && this->hook != Left)
                { this->hook = Right; }
            else if (event.key.keysym.sym == 102 && this->engine != SDL)
                { this->engine = SDL; this->engineChecker = true; }
            else if (event.key.keysym.sym == 103 && this->engine != GL)
                { this->engine = GL; this->engineChecker = true; }
            else if (event.key.keysym.sym == SDLK_SPACE)
                {this->status = Pause;}
        }
    }
    return;
}

void      Window::drawFrame(std::list <IEntity *> data, int lives, int score) const {
    SDL_SetRenderDrawColor(this->pRenderer, 22, 22, 24, 0);
    SDL_RenderClear(this->pRenderer);
    SDL_Rect    form;
    SDL_Texture *texture = nullptr;
    std::list <IEntity *>::iterator iter = data.begin();
    while (iter != data.end()) {
      form.x = (*iter)->getPosX() * CELL_UNITY;
      form.y = (*iter)->getPosY() * CELL_UNITY;
      form.w = CELL_UNITY;
      form.h = CELL_UNITY;
      eTexture img = (*iter)->getTexture();

      texture = SDL_CreateTextureFromSurface( this->pRenderer, this->_textures.find(img)->second );
      SDL_RenderCopy( this->pRenderer, texture, nullptr, &form);
      SDL_DestroyTexture( texture );
      iter++;
    }
    this->drawMenu(lives, score);
    SDL_RenderPresent( this->pRenderer );
    return;
}

void    Window::drawMenu(int lives, int score) const {
  SDL_Rect    form;
  SDL_Surface *surface = nullptr;
  SDL_Texture *texture = nullptr;
  int x = CELL_UNITY;
  int y = this->wHeight * CELL_UNITY + CELL_UNITY;

  form.x = 0;
  form.y = this->wHeight * CELL_UNITY;
  form.w = this->wWidth * CELL_UNITY;
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
  std::string sScore = std::to_string(score);
  surface = TTF_RenderText_Blended(this->pFont, sScore.c_str(), White);
  texture = SDL_CreateTextureFromSurface(this->pRenderer, surface);
  form.x =  this->wWidth * CELL_UNITY - 140;
  form.y = this->wHeight * CELL_UNITY + CELL_UNITY / 2;
  form.w = 40;
  form.h = 30;
  SDL_RenderCopy(this->pRenderer, texture, nullptr, &form);
  SDL_DestroyTexture(texture);
  SDL_FreeSurface(surface);
  return;
}

bool            Window::displayPause(int status) {
    SDL_Rect  start;
    SDL_Rect  resume;
    SDL_Rect  exit;
    SDL_Event event;
    SDL_Color background = { 22, 22, 24, 0};

    SDL_SetRenderDrawColor(this->pRenderer, 22, 22, 24, 0);
    SDL_RenderClear(this->pRenderer);
    switch (status) {
        case 2 :
            resume = this->drawResume(background);
        case 1 :
            start = this->drawStart(background);
            exit = this->drawExit(background);
            break;
    }
    SDL_RenderPresent( this->pRenderer );
    while(SDL_PollEvent(&event)) {
        if (event.type ==  SDL_MOUSEBUTTONDOWN) {
            if ( this->checkMousePos(resume, event.button.x, event.button.y) ) {
                this->status = NoDir;
                return false;
            }
            if ( this->checkMousePos(exit, event.button.x, event.button.y) ) {
                this->status = Exit;
                return false;
            }
            if ( this->checkMousePos(start, event.button.x, event.button.y) ) {
                this->status = Start;
                return false;
            }
        }
        else if (event.type == SDL_KEYDOWN) {
            if (event.key.keysym.sym == 27) { this->status = Exit; }
            else if (event.key.keysym.sym == 102 && this->engine != SDL) {
                this->engine = SDL; this->engineChecker = true; }
            else if (event.key.keysym.sym == 103 && this->engine != GL) {
                this->engine = GL; this->engineChecker = true; }
        }
    }
    return true;
}

bool    Window::checkMousePos(SDL_Rect button, int x, int y) const {
    if (x >= button.x && x <= (button.x + button.w)
        && y >= button.y && y <= (button.y + button.h))
        return true;
    return false;
}

SDL_Rect Window::drawStart(SDL_Color color) const {
    SDL_Rect start;
    SDL_Surface *surface;
    SDL_Texture *texture;
    (void)color;
    surface = SDL_CreateRGBSurface(0, CELL_UNITY * 3, CELL_UNITY * 2, 32, 0, 0, 0, 0);
    texture = SDL_CreateTextureFromSurface(this->pRenderer, surface);
    start.x = wWidth * CELL_UNITY / 5;
    start.y = wHeight * CELL_UNITY - CELL_UNITY * 1.5;
    start.w = CELL_UNITY * 3;
    start.h = CELL_UNITY * 2;
    SDL_FillRect(surface, &start, SDL_MapRGB(surface->format, 255, 0, 0));
    SDL_RenderCopy(this->pRenderer, texture, nullptr, &start);
    SDL_DestroyTexture(texture);
    SDL_FreeSurface(surface);
    return start;
}

SDL_Rect Window::drawResume(SDL_Color color) const {
    SDL_Rect resume;
    SDL_Surface *surface;
    SDL_Texture *texture;
    (void)color;
    surface = SDL_CreateRGBSurface(0, CELL_UNITY * 3, CELL_UNITY * 2, 32, 0, 0, 0, 0);
    texture = SDL_CreateTextureFromSurface(this->pRenderer, surface);
    resume.x = (wWidth * CELL_UNITY / 5) * 2;
    resume.y = wHeight * CELL_UNITY - CELL_UNITY * 1.5;
    resume.w = CELL_UNITY * 3;
    resume.h = CELL_UNITY * 2;
    SDL_FillRect(surface, &resume, SDL_MapRGB(surface->format, 255, 0, 0));
    SDL_RenderCopy(this->pRenderer, texture, nullptr, &resume);
    SDL_DestroyTexture(texture);
    SDL_FreeSurface(surface);
    return resume;
}

SDL_Rect Window::drawExit(SDL_Color color) const {
    SDL_Rect exit;
    SDL_Surface *surface;
    SDL_Texture *texture;
    (void)color;
    surface = SDL_CreateRGBSurface(0, CELL_UNITY * 3, CELL_UNITY * 2, 32, 0, 0, 0, 0);
    texture = SDL_CreateTextureFromSurface(this->pRenderer, surface);
    exit.x = (wWidth * CELL_UNITY / 5) * 3;
    exit.y = wHeight * CELL_UNITY - CELL_UNITY * 1.5;
    exit.w = CELL_UNITY * 3;
    exit.h = CELL_UNITY * 2;
    SDL_FillRect(surface, &exit, SDL_MapRGB(surface->format, 255, 0, 0));
    SDL_RenderCopy(this->pRenderer, texture, nullptr, &exit);
    SDL_DestroyTexture(texture);
    SDL_FreeSurface(surface);
    return exit;
}

unsigned int    Window::getWidth(void) const {
    return this->wWidth;
}

unsigned int    Window::getHeight(void) const {
    return this->wHeight;
}

void       Window::initTextures(void) {
    eTexture texture;

    for (int i = 1; i <= 23; i++) {
        if (i >= 5 && i <= 8) {i++; continue;} // Delete this line when headmiam
        std::string name = "/assets/";
        name += std::to_string(i);
        name += ".bmp";
        this->_textures.insert(std::make_pair(static_cast<eTexture>(i), SDL_LoadBMP(name.c_str())));
    }
    return;
}

Window    *createWindow(unsigned int width, unsigned int height, eHook hook) {
    return new Window(width, height, hook);
}

void      deleteWindow(Window *window) {
  delete window;
}
