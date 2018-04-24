#include "Window.hpp"
#include "Exception.hpp"

Window::Window(void) { return; }
Window::Window(Window const &src) { *this = src; }

Window  &Window::operator=(Window const &) { return *this; }

Window::Window(unsigned int width, unsigned int height, eDirection direction) :
  direction(direction),
  status(Pause),
  engine(SDL),
  engineChecker(false),
  wWidth(width),
  wHeight(height)
 {
  if (SDL_Init(SDL_INIT_VIDEO) != 0 || TTF_Init() != 0) {
    std::cout << "SDL init() failed." << std::endl;
    throw Exception::Throw(WIN_FAIL);
  }
  else {
    SDL_Window    *pWindow = nullptr;
    pWindow = SDL_CreateWindow(
      "Nibbler SDL",
      SDL_WINDOWPOS_UNDEFINED,
      SDL_WINDOWPOS_UNDEFINED,
      this->wWidth * CELL_UNITY,
      this->wHeight * CELL_UNITY + CELL_UNITY * 2,
      SDL_WINDOW_SHOWN
  );
  if (pWindow == NULL) {
      throw Exception::Throw(WIN_FAIL);
  }
    this->pWindow = pWindow;
    SDL_SetWindowResizable(this->pWindow, SDL_FALSE);
    this->pRenderer = SDL_CreateRenderer(pWindow, -1, SDL_RENDERER_SOFTWARE);
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
        SDL_FreeSurface(it->second);
        it++;
    }
    TTF_CloseFont(this->pFont);
    TTF_Quit();
    this->_textures.clear();
    SDL_DestroyRenderer(this->pRenderer);
    SDL_DestroyWindow(this->pWindow);
    // SDL_Quit();
    return;
}

void        Window::handleEvent(int milliseconds) {
    SDL_Event event;
    (void)milliseconds;
    while (SDL_PollEvent(&event)){
        this->setEngine(event);
        if (!this->engineChecker){
            this->setStatus(event);
            if (this->status == Play)
                this->setDirection(event);
            else if (this->status == Pause)
                this->handlePauseEvent(event);
        }
    }
}

eDirection   Window::getDirection(void) const {
    return this->direction;
}

void    Window::handlePauseEvent(SDL_Event event) {
    if (event.type == SDL_KEYDOWN) {
        if (event.key.keysym.sym == SDLK_r)
            { this->status = Play; return; }
        else if (event.key.keysym.sym == SDLK_s)
            { this->status = Start; return; }
    }
    return;
}
void    Window::setDirection(SDL_Event event) {
    if (event.type == SDL_KEYDOWN) {
        if (event.key.keysym.sym == SDLK_UP && this->direction != Down && this->direction != Up)
            { this->directionChecker = true; this->direction = Up; return; }
        else if (event.key.keysym.sym == SDLK_DOWN  && this->direction != Up && this->direction != Down)
            { this->directionChecker = true; this->direction = Down; return; }
        else if (event.key.keysym.sym == SDLK_LEFT && this->direction != Right && this->direction != Left)
            { this->directionChecker = true; this->direction = Left; return; }
        else if (event.key.keysym.sym == SDLK_RIGHT && this->direction != Left && this->direction != Right)
            { this->directionChecker = true; this->direction = Right; return; }
    }
    return;
}

void    Window::updateDirection(eDirection direction){
    this->direction = direction;
}

bool   Window::directionHasChanged(void) const {
    return this->directionChecker;
}

void    Window::reverseDirectionChecker(void) {
    this->directionChecker = false;
}

eStatus   Window::getStatus(void) const {
    return this->status;
}

void    Window::setStatus(SDL_Event event) {
    if (event.type == SDL_QUIT ||
     (event.type == SDL_KEYDOWN && event.key.keysym.sym == 27)) {
        this->status = Exit;
        SDL_DestroyWindow(this->pWindow);
    }
    else if (event.key.keysym.sym == SDLK_SPACE && event.type == SDL_KEYDOWN)
        { this->status = Pause; }
    return;
}

void    Window::updateStatus(eStatus status) {
    this->status = status;
    return;
}

void    Window::setEngine(SDL_Event event) {
    if (event.type == SDL_KEYDOWN) {
        if (event.key.keysym.sym == 102 && this->engine != GL) {
            this->engine = GL;
            this->engineChecker = true;
            SDL_DestroyWindow(this->pWindow);
        }
        else if (event.key.keysym.sym == 103 && this->engine != SFML) {
            this->engine = SFML;
            this->engineChecker = true;
            SDL_DestroyWindow(this->pWindow);
        }
    }
    return;
}

eEngine  Window::getEngine(void) const {
    return this->engine;
}

bool    Window::engineHasChanged(void) const{
    return this->engineChecker;
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
  SDL_Rect    form = {0, static_cast<int>(this->wHeight * CELL_UNITY), static_cast<int>(this->wWidth * CELL_UNITY), CELL_UNITY * 2};
  SDL_Surface *surface = nullptr;
  SDL_Texture *texture = nullptr;
  int x = CELL_UNITY;
  int y = this->wHeight * CELL_UNITY + CELL_UNITY;

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
  std::string sScore = "Score : ";
  sScore += std::to_string(score);
  surface = TTF_RenderText_Blended(this->pFont, sScore.c_str(), White);
  texture = SDL_CreateTextureFromSurface(this->pRenderer, surface);
  form.x =  this->wWidth * CELL_UNITY - 140;
  form.y = this->wHeight * CELL_UNITY + CELL_UNITY / 2;
  form.w = 80;
  form.h = 24;
  SDL_RenderCopy(this->pRenderer, texture, nullptr, &form);
  SDL_DestroyTexture(texture);
  SDL_FreeSurface(surface);
  return;
}

bool            Window::displayPause(int score, int bestScore) {
    SDL_Rect  background = {0, 0, static_cast<int>(this->wWidth * CELL_UNITY), static_cast<int>(this->wHeight * CELL_UNITY) };
    SDL_Surface *img = SDL_LoadBMP("/assets/menu.bmp");
    SDL_Texture *texture = SDL_CreateTextureFromSurface(this->pRenderer, img);
    SDL_FreeSurface(img);
    SDL_SetRenderDrawColor(this->pRenderer, 22, 22, 24, 0);
    SDL_RenderClear(this->pRenderer);
    SDL_RenderCopy(this->pRenderer, texture, nullptr, &background);
    SDL_DestroyTexture(texture);
    if(score >=0) {
        SDL_Surface *surface = nullptr;
        SDL_Texture *texture = nullptr;
        SDL_Rect form;
        SDL_Color White = {255, 255, 255, 0};
        std::string sScore = "You lose... Your score was: ";
        sScore += std::to_string(score);
        sScore +=  " Your best score is: ";
        sScore += std::to_string(bestScore);
        surface = TTF_RenderText_Blended(this->pFont, sScore.c_str(), White);
        texture = SDL_CreateTextureFromSurface(this->pRenderer, surface);
        form.x =  CELL_UNITY;
        form.y = this->wHeight * CELL_UNITY + CELL_UNITY / 2;
        form.w = this->wHeight * CELL_UNITY / 2;
        form.h = 20;
        SDL_RenderCopy(this->pRenderer, texture, nullptr, &form);
        SDL_DestroyTexture(texture);
        SDL_FreeSurface(surface);
    }
    SDL_RenderPresent( this->pRenderer );
    return true;
}

unsigned int    Window::getWidth(void) const {
    return this->wWidth;
}

unsigned int    Window::getHeight(void) const {
    return this->wHeight;
}

void       Window::initTextures(void) {
    for (int i = 1; i <= 24; i++) {
        std::string name = "/assets/";
        name += std::to_string(i);
        name += ".bmp";
        this->_textures.insert(std::make_pair(static_cast<eTexture>(i), SDL_LoadBMP(name.c_str())));
    }
    return;
}

Window    *createWindow(unsigned int width, unsigned int height, eDirection direction) {
    return new Window(width, height, direction);
}

void      deleteWindow(Window *window) {
  delete window;
}
