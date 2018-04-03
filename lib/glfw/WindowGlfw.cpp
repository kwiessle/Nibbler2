#include "WindowGlfw.hpp"

Window::Window(void) { return; }

Window::Window(unsigned int width, unsigned int height, eDirection direction) :
    wWidth(width),
    wHeight(height),
    direction(direction),
    engineChecker(false),
    status(Pause),
    engine(GL)
{
    if (!glfwInit()) {
        std::cout << "OpenGL init failed" << std::endl;
        glfwTerminate();
        exit(0);
    }
    this->pWindow = glfwCreateWindow(
        this->wWidth * CELL_UNITY,
        this->wHeight * CELL_UNITY + CELL_UNITY * 2,
        "Nibbler",
        NULL,
        NULL
    );
    glfwMakeContextCurrent(this->pWindow);
    // glfwSetWindowIcon(this->pWindow, 1, icons);
    glOrtho(0.0f, this->wWidth * CELL_UNITY, this->wHeight * CELL_UNITY + CELL_UNITY * 2, 0.0f, 1.0f, -1.0f);
    this->initTextures();
    return;
}

Window::~Window(void) {
    glfwTerminate();
    return;
}

void    Window::handleEvent(void) {
    if (!glfwWindowShouldClose(this->pWindow)) {
        glfwPollEvents();

        this->setDirection();
        this->setEngine();
        this->setStatus();
    }
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
    if (glfwWindowShouldClose(this->pWindow) != 0) { this->status = Exit; }
    if (glfwGetKey(this->pWindow, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        { this->status = Exit; }
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
        this->engine != SFML)
        { this->engine = SFML; this->engineChecker = true; }
    else if (glfwGetKey(this->pWindow, GLFW_KEY_G) == GLFW_PRESS &&
        this->engine != SDL)
        { this->engine = SDL; this->engineChecker = true; }
    return;
}

eEngine  Window::getEngine(void) const {
    return this->engine;
}

bool    Window::engineHasChanged(void) const{
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
    if ((*iter)->getTexture() == 3 || (*iter)->getTexture() == 4 || (*iter)->getTexture() == 15 || (*iter)->getTexture() == 16) {
        glTexCoord2f(0,0);
        glVertex2f(x, y);
        glTexCoord2f(0,1);
        glVertex2f(x, y + CELL_UNITY);
        glTexCoord2f(1,1);
        glVertex2f(x+CELL_UNITY, y+CELL_UNITY);
        glTexCoord2f(1,0);
        glVertex2f(x+ CELL_UNITY,y);
    }
    else if ((*iter)->getTexture() == 9 || (*iter)->getTexture() == 12) {
        glTexCoord2f(0,1);
        glVertex2f(x, y);
        glTexCoord2f(1,1);
        glVertex2f(x, y + CELL_UNITY);
        glTexCoord2f(1,0);
        glVertex2f(x+CELL_UNITY, y+CELL_UNITY);
        glTexCoord2f(0, 0);
        glVertex2f(x+ CELL_UNITY,y);
    }
    else if ((*iter)->getTexture() == 10 || (*iter)->getTexture() == 11) {
        glTexCoord2f(1,0);
        glVertex2f(x, y);
        glTexCoord2f(0,0);
        glVertex2f(x, y + CELL_UNITY);
        glTexCoord2f(0,1);
        glVertex2f(x+CELL_UNITY, y+CELL_UNITY);
        glTexCoord2f(1,1);
        glVertex2f(x+ CELL_UNITY,y);
    }
    else {
        glTexCoord2f(1,1);
        glVertex2f(x, y);
        glTexCoord2f(1,0);
        glVertex2f(x, y + CELL_UNITY);
        glTexCoord2f(0,0);
        glVertex2f(x+CELL_UNITY, y+CELL_UNITY);
        glTexCoord2f(0,1);
        glVertex2f(x+ CELL_UNITY,y);
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
    std::string sScore = std::to_string(score);
    const char *tmp = sScore.c_str();
    for( int i = 0; i < sScore.length(); i++)
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, tmp[i]);
}

bool   Window::displayPause(int status) {
    glClearColor(22/255.0, 22/255.0, 24/255.0, 0.0);
    glClear(GL_COLOR_BUFFER_BIT);
    switch(status) {
        case 2 :
            this->drawResume();
        case 1 :
            this->drawStart();
            this->drawExit();
            break;
    }
    glColor3f(1, 1, 1);
    glfwSwapBuffers(this->pWindow);
    glfwWaitEvents();
    if ( glfwGetMouseButton(this->pWindow, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {
        double xpos;
        double ypos;
        float ycheck = wHeight * CELL_UNITY - CELL_UNITY * 1.5;
        glfwGetCursorPos(this->pWindow, &xpos, &ypos);
        if ( this->checkMousePos(xpos, ypos, (wWidth * CELL_UNITY / 3) - ((CELL_UNITY * 3) / 2), ycheck)) {
            this->status = Start;
            return false;
        }
        if ( status == 2 && this->checkMousePos(xpos, ypos, (wWidth * CELL_UNITY / 3) - ((CELL_UNITY * 3) / 2) + (CELL_UNITY * 3 + wWidth), ycheck )) {
            this->status = Play;
            return false;
        }
        if ( this->checkMousePos(xpos, ypos, (wWidth * CELL_UNITY / 3) - ((CELL_UNITY * 3) / 2) + (CELL_UNITY * 3 + wWidth) * 2, ycheck)) {
            this->status = Exit;
            return false;
        }
    }
    this->setStatus();
    this->setEngine();
    return true;
}

bool    Window::checkMousePos(double x, double y, float xcheck, float ycheck) const {
    if (x >= xcheck && x <= xcheck + CELL_UNITY * 3
        && y >= ycheck && y <= ycheck + CELL_UNITY * 2)
        return true;
    return false;
}

void      Window::drawStart(void) const {
    float x = (wWidth * CELL_UNITY / 3) - ((CELL_UNITY * 3) / 2);
    float y = wHeight * CELL_UNITY - CELL_UNITY * 1.5;
    glBegin(GL_QUADS);
    glColor3f(0,1,0);
    glVertex2f(x, y);
    glVertex2f(x + CELL_UNITY * 3, y);
    glVertex2f(x + CELL_UNITY * 3, y + CELL_UNITY * 2);
    glVertex2f(x, y + CELL_UNITY * 2);
    glEnd();
}

void      Window::drawResume(void) const {
    float x = (wWidth * CELL_UNITY / 3) - ((CELL_UNITY * 3) / 2) + (CELL_UNITY * 3 + wWidth);
    float y = wHeight * CELL_UNITY - CELL_UNITY * 1.5;
    glBegin(GL_QUADS);
    glColor3f(0, 0, 1);
    glVertex2f(x, y);
    glVertex2f(x + CELL_UNITY * 3, y);
    glVertex2f(x + CELL_UNITY * 3, y + CELL_UNITY * 2);
    glVertex2f(x, y + CELL_UNITY * 2);
    glEnd();
}

void      Window::drawExit(void) const {
    float x = (wWidth * CELL_UNITY / 3) - ((CELL_UNITY * 3) / 2) + (CELL_UNITY * 3 + wWidth) * 2;
    float y = wHeight * CELL_UNITY - CELL_UNITY * 1.5;
    glBegin(GL_QUADS);
    glColor3f(1, 0, 0);
    glVertex2f(x, y);
    glVertex2f(x + CELL_UNITY * 3, y);
    glVertex2f(x+ CELL_UNITY * 3, y + CELL_UNITY * 2);
    glVertex2f(x , y + CELL_UNITY * 2);
    glEnd();
}

unsigned int    Window::getWidth(void) const {
    return this->wWidth;
}

unsigned int    Window::getHeight(void) const {
    return this->wHeight;
}

void       Window::initTextures(void) {
    glGenTextures(23, this->_textures);

    for (int i = 1; i <= 23; i++) {
        if (i == 5 || i == 6 || i == 7 || i == 8) {i++; continue;} // Delete this line when headmiam
        std::string name = "./assets/";
        name += std::to_string(i);
        name += ".bmp";
        glBindTexture(GL_TEXTURE_2D, this->_textures[i]);
        this->loadBMP(name.c_str());
    }
    return;
}

Window    *createWindow(unsigned int width, unsigned int height, eDirection direction) {
    return new Window(width, height, direction);
}

void      deleteWindow(Window *window) {
  delete window;
}

GLuint Window::loadBMP(const char *filename) const {
    GLuint texture;
    // Data read from the header of the BMP file
    unsigned char header[54]; // Each BMP file begins by a 54-bytes header
    unsigned int dataPos;     // Position in the file where the actual data begins
    unsigned int width;
    unsigned int height;
    unsigned int imageSize;
    unsigned char * data;

    FILE * file = fopen(filename,"rb");
    if (!file) {
        std::cout << "Image could not be opened" << std::endl;
        exit(0);
    }
    if ( fread(header, 1, 54, file) != 54 ){ // If not 54 bytes read : problem
        std::cout << "Not a correct BMP file" << std::endl;
        exit(0);
    }
    if ( header[0] != 'B' || header[1] != 'M' ){
        std::cout << "Not a correct BMP file" << std::endl;
        exit(0);
    }
    dataPos    = *(int*)&(header[0x0A]);
    imageSize  = *(int*)&(header[0x22]);
    width      = *(int*)&(header[0x12]);
    height     = *(int*)&(header[0x16]);

    if (imageSize == 0)
        imageSize = width * height * 3;
    if (dataPos == 0)
        dataPos = 54;
    data = (unsigned char *)malloc( width * height * 3 );
    fread( data, width * height * 3, 1, file );
    fclose(file);

    glTexImage2D(GL_TEXTURE_2D, 0,GL_RGB, width, height, 0, GL_BGR, GL_UNSIGNED_BYTE, data);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);    free(data);

   return texture;

}
