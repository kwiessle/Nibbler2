#include "WindowGlfw.hpp"


Window::Window(void) { return; }

Window::Window(Window const &src) { *this = src; }

Window  &Window::operator=(Window const &) { return *this; }

Window::Window(unsigned int width, unsigned int height, eDirection direction) :
  direction(direction),
  status(Pause),
  engine(GL),
  engineChecker(false),
  wWidth(width),
  wHeight(height)
{
    if (!glfwInit()) {
        std::cout << "OpenGL init failed" << std::endl;
        glfwTerminate();
        throw Exception::Throw(WIN_FAIL);
    }
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
    this->pWindow = glfwCreateWindow(
        this->wWidth * CELL_UNITY,
        this->wHeight * CELL_UNITY + CELL_UNITY * 2,
        "Nibbler GLFW",
        NULL,
        NULL
    );
    glfwMakeContextCurrent(this->pWindow);
    glOrtho(0.0f, this->wWidth * CELL_UNITY, this->wHeight * CELL_UNITY + CELL_UNITY * 2, 0.0f, 1.0f, -1.0f);
    this->initTextures();
    return;
}

Window::~Window(void) {
    glDeleteTextures(23, this->_textures);
    glfwTerminate();
}

void    Window::handleEvent(int milliseconds) {
    (void)milliseconds;
    if (!glfwWindowShouldClose(this->pWindow)) {
        glfwPollEvents();
        this->setEngine();
        if (!this->engineChecker) {
            this->setStatus();
            if (this->status == Play)
                this->setDirection();
            else if ( this->status == Pause)
                this->handlePauseEvent();
        }
    }
}

void       Window::handlePauseEvent() {
    if (glfwGetKey(this->pWindow, GLFW_KEY_R) == GLFW_PRESS)
        { this->status = Play; return; }
    else if (glfwGetKey(this->pWindow, GLFW_KEY_S) == GLFW_PRESS)
        { this->status = Start; return; }
    return;
}
eDirection   Window::getDirection(void) const {
    return this->direction;
}

void    Window::setDirection(void) {
    if (glfwGetKey(this->pWindow, GLFW_KEY_UP) == GLFW_PRESS &&
        this->direction != Down)
        { this->direction = Up; }
    else if (glfwGetKey(this->pWindow, GLFW_KEY_DOWN) == GLFW_PRESS &&
        this->direction != Up)
        { this->direction = Down; }
    else if (glfwGetKey(this->pWindow, GLFW_KEY_LEFT) == GLFW_PRESS &&
        this->direction != Right)
        { this->direction = Left; }
    else if (glfwGetKey(this->pWindow, GLFW_KEY_RIGHT) == GLFW_PRESS &&
        this->direction != Left)
        { this->direction = Right; }

}

void    Window::updateDirection(eDirection direction){
    this->direction = direction;
}

bool    Window::directionHasChanged(void) const {
    return this->directionChecker;
}

void    Window::reverseDirectionChecker(void) {
    this->directionChecker = false;
}

eStatus Window::getStatus(void) const {
    return this->status;
}

void    Window::setStatus(void) {
    if (glfwWindowShouldClose(this->pWindow) != 0) { this->status = Exit;glfwSetWindowShouldClose(this->pWindow, true); }
    else if (glfwGetKey(this->pWindow, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        { this->status = Exit;glfwSetWindowShouldClose(this->pWindow, true);}
    else if (glfwGetKey(this->pWindow, GLFW_KEY_SPACE) == GLFW_PRESS)
        { this->status = Pause; }
    return;
}

void    Window::updateStatus(eStatus status)  {
    this->status = status;
    return;
}

void    Window::setEngine(void) {
    if (glfwGetKey(this->pWindow, GLFW_KEY_F) == GLFW_PRESS &&
        this->engine != SFML) {
            this->engine = SFML;
            this->engineChecker = true;
            glfwSetWindowShouldClose(this->pWindow, true);
        }
    else if (glfwGetKey(this->pWindow, GLFW_KEY_G) == GLFW_PRESS &&
        this->engine != SDL) {
             this->engine = SDL;
             this->engineChecker = true;
             glfwSetWindowShouldClose(this->pWindow, true);
        }
    return;
}

eEngine  Window::getEngine(void) const {
    return this->engine;
}

bool    Window::engineHasChanged(void) const {
    return this->engineChecker;
}

void    Window::drawFrame(std::list <IEntity *> data, int lives, int score) const {
    glClearColor(22/255.0, 22/255.0, 24/255.0, 0.0);
    glClear(GL_COLOR_BUFFER_BIT);
    std::list <IEntity *>::iterator iter = data.begin();
    glEnable(GL_TEXTURE_2D);
    while (iter != data.end()) {
        this->displayTextures(iter);
        iter++;
    }
    glDisable(GL_TEXTURE_2D);
    this->drawMenu(lives, score);
    glfwSwapBuffers(this->pWindow);
    return;
}

void    Window::displayTextures(std::list <IEntity *>::iterator iter) const {
    GLfloat x = (*iter)->getPosX() * CELL_UNITY;
    GLfloat y = (*iter)->getPosY() * CELL_UNITY;
    glBindTexture(GL_TEXTURE_2D, this->_textures[((*iter)->getTexture())]);
    glBegin(GL_QUADS);
    switch((*iter)->getTexture()) {
        case 3 :
        case 4 :
        case 8 :
        case 7 :
        case 15 :
        case 16 :
            glTexCoord2f(0,0);
            glVertex2f(x, y);
            glTexCoord2f(0,1);
            glVertex2f(x, y + CELL_UNITY);
            glTexCoord2f(1,1);
            glVertex2f(x+CELL_UNITY, y+CELL_UNITY);
            glTexCoord2f(1,0);
            glVertex2f(x+ CELL_UNITY,y);
            break;
        case 9 :
        case 12 :
            glTexCoord2f(0,1);
            glVertex2f(x, y);
            glTexCoord2f(1,1);
            glVertex2f(x, y + CELL_UNITY);
            glTexCoord2f(1,0);
            glVertex2f(x+CELL_UNITY, y+CELL_UNITY);
            glTexCoord2f(0, 0);
            glVertex2f(x+ CELL_UNITY,y);
            break;
        case 10 :
        case 11 :
            glTexCoord2f(1,0);
            glVertex2f(x, y);
            glTexCoord2f(0,0);
            glVertex2f(x, y + CELL_UNITY);
            glTexCoord2f(0,1);
            glVertex2f(x+CELL_UNITY, y+CELL_UNITY);
            glTexCoord2f(1,1);
            glVertex2f(x+ CELL_UNITY,y);
            break;
        case 19 :
        case 23 :
        case 24 :
            glTexCoord2f(0,1);
            glVertex2f(x, y);
            glTexCoord2f(0,0);
            glVertex2f(x, y + CELL_UNITY);
            glTexCoord2f(1,0);
            glVertex2f(x + CELL_UNITY, y+CELL_UNITY);
            glTexCoord2f(1,1);
            glVertex2f(x+ CELL_UNITY,y);
            break;
        default :
            glTexCoord2f(1,1);
            glVertex2f(x, y);
            glTexCoord2f(1,0);
            glVertex2f(x, y + CELL_UNITY);
            glTexCoord2f(0,0);
            glVertex2f(x+CELL_UNITY, y+CELL_UNITY);
            glTexCoord2f(0,1);
            glVertex2f(x+ CELL_UNITY,y);
            break;

    }
    glEnd();
}
void    Window::drawMenu(int lives, int score) const {
    int x = CELL_UNITY;
    int y = this->wHeight * CELL_UNITY + CELL_UNITY;
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, this->_textures[21]);
    glBegin(GL_QUADS);
    glTexCoord2f(0,0);
    glVertex2f(0, this->wHeight * CELL_UNITY);
    glTexCoord2f(0,1);
    glVertex2f(0, this->wHeight * CELL_UNITY + CELL_UNITY * 2);
    glTexCoord2f(1,1);
    glVertex2f(this->wWidth * CELL_UNITY, this->wHeight * CELL_UNITY + CELL_UNITY * 2);
    glTexCoord2f(1,0);
    glVertex2f(this->wWidth * CELL_UNITY, this->wHeight * CELL_UNITY);
    glEnd();
    glDisable(GL_TEXTURE_2D);
    while (lives != 0) {
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, this->_textures[22]);
        glBegin(GL_QUADS);
        glTexCoord2f(1,1);
        glVertex2f(x, y - CELL_UNITY / 2);
        glTexCoord2f(1,0);
        glVertex2f(x,y - CELL_UNITY / 2 + CELL_UNITY);
        glTexCoord2f(0,0);
        glVertex2f(x + CELL_UNITY,y - CELL_UNITY / 2 + CELL_UNITY);
        glTexCoord2f(0,1);
        glVertex2f(x + CELL_UNITY, y - CELL_UNITY / 2);
        glEnd();
        glDisable(GL_TEXTURE_2D);
        x += CELL_UNITY + CELL_UNITY / 2;
        lives--;
    }
    glRasterPos2i(this->wWidth * CELL_UNITY - 140,
    this->wHeight * CELL_UNITY + CELL_UNITY / 2);
    glColor3f(1.0f, 1.0f, 1.0f);
    std::string sScore = "Score : ";
    sScore += std::to_string(score);
    const char *tmp = sScore.c_str();
    for( unsigned int i = 0; i < sScore.length(); i++)
    glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, tmp[i]);
}

bool   Window::displayPause(int score, int bestScore) {
    glClearColor(22/255.0, 22/255.0, 24/255.0, 0.0);
    glClear(GL_COLOR_BUFFER_BIT);
    GLuint background;
    glGenTextures(1, &background);
    glBindTexture(GL_TEXTURE_2D, background);
    BMP image =  BMP("./assets/menu.bmp");
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_SWIZZLE_RGBA, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, image.HasAlphaChannel() ? GL_RGBA : GL_RGB, image.GetWidth(), image.GetWidth(), 0, image.HasAlphaChannel() ? GL_BGRA : GL_BGR, GL_UNSIGNED_BYTE, image.GetPixels().data());
    glEnable(GL_TEXTURE_2D);
    glBegin(GL_QUADS);
    glTexCoord2f(0,1);
    glVertex2f(0, 0);
    glTexCoord2f(1,1);
    glVertex2f(this->wWidth * CELL_UNITY, 0);
    glTexCoord2f(1,0);
    glVertex2f(this->wWidth * CELL_UNITY, this->wHeight * CELL_UNITY);
    glTexCoord2f(0,0);
    glVertex2f(0, this->wHeight * CELL_UNITY);
    glEnd();
    glDisable(GL_TEXTURE_2D);
    if (score >= 0) {
        glRasterPos2i(CELL_UNITY,
        this->wHeight * CELL_UNITY + CELL_UNITY / 2);
        glColor3f(1.0f, 1.0f, 1.0f);
        std::string sScore = "You lose... Your score was: ";
        sScore += std::to_string(score);
        sScore +=  " Your best score is: ";
        sScore += std::to_string(bestScore);
        const char *tmp = sScore.c_str();
        for( unsigned int i = 0; i < sScore.length(); i++)
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, tmp[i]);
    }
    glColor3f(1, 1, 1);
    glfwSwapBuffers(this->pWindow);
    return true;
}


unsigned int    Window::getWidth(void) const {
    return this->wWidth;
}

unsigned int    Window::getHeight(void) const {
    return this->wHeight;
}

void       Window::initTextures(void) {
    glGenTextures(24, this->_textures);

    for (int i = 1; i <= 24; i++) {
        std::string name = "./assets/";
        name += std::to_string(i);
        name += ".bmp";
        BMP image = BMP(name.c_str());

        glBindTexture(GL_TEXTURE_2D, this->_textures[i]);
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_LINEAR);
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_LINEAR);
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_SWIZZLE_RGBA, GL_LINEAR);
        glTexImage2D(GL_TEXTURE_2D, 0, image.HasAlphaChannel() ? GL_RGBA : GL_RGB, image.GetWidth(), image.GetWidth(), 0, image.HasAlphaChannel() ? GL_BGRA : GL_BGR, GL_UNSIGNED_BYTE, image.GetPixels().data());
    }
    return;
}

Window    *createWindow(unsigned int width, unsigned int height, eDirection direction) {
    return new Window(width, height, direction);
}

void      deleteWindow(Window *window) {
    delete window;
}
