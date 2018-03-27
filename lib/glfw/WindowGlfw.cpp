#include "WindowGlfw.hpp"

Window::Window(void) { return; }

Window::Window(unsigned int width, unsigned int height, eDirection direction) :
    wWidth(width),
    wHeight(height),
    direction(direction),
    engineChecker(false),
    engine(GL)
{
    if (!glfwInit()) {
        std::cout << "OpenGL init failed" << std::endl;
        glfwTerminate();
        exit(0);
    }
    glfwWindowHint(GLFW_SAMPLES, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    this->pWindow = glfwCreateWindow(
        this->wWidth * CELL_UNITY,
        this->wHeight * CELL_UNITY + CELL_UNITY * 2,
        "Nibbler",
        NULL,
        NULL
    );
    glfwMakeContextCurrent(this->pWindow);
    glOrtho(0.0, this->wWidth * CELL_UNITY, 0.0, this->wHeight * CELL_UNITY + CELL_UNITY * 2, -1.0, 1.0);
    glfwSetInputMode(this->pWindow, GLFW_STICKY_KEYS, GL_TRUE);
    glEnable(GL_TEXTURE_2D);
    this->initTextures();
    return;
}

Window::~Window(void) {
    glfwDestroyWindow(this->pWindow);
    glfwTerminate();
    return;
}

void    Window::handleEvent(void) {
    glfwPollEvents();

    this->setDirection();
    this->setEngine();
    this->setStatus();
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
    if (glfwWindowShouldClose(this->pWindow) != 0) { this->status =Exit; }
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
    glEnable(GL_TEXTURE_2D);
    std::list <IEntity *>::iterator iter = data.begin();

    while ( iter != data.end()) {
        eTexture img = (*iter)->getTexture();
        glBindTexture(GL_TEXTURE_2D, this->_textures.find(img)->second);
        glBegin(GL_QUADS);
        glTexCoord2f(0, 0); glVertex3f(0, 0, 0);
        glEnd();
        glDisable(GL_TEXTURE_2D);
        glPopMatrix();
        glMatrixMode(GL_PROJECTION);
        glPopMatrix();
        iter++;
    }
    glLoadIdentity();
    glfwSwapBuffers(this->pWindow);

    std::cout << "drawFrame" << std::endl;
    return;
}

bool   Window::displayPause(int status) {
    glClearColor(22/255.0, 22/255.0, 24/255.0, 0.0);
    glClear(GL_COLOR_BUFFER_BIT);
    glBegin(GL_QUADS);
        glColor3f(1,1,1);
        glVertex2f(10, 50);
        glColor3f(1,0,0);
        glVertex2f(100, 50);
        glColor3f(1,1,1);
        glVertex2f(100, 100);
        glColor3f(0,1,1);
        glVertex2f(10, 50);
    glEnd();
    glfwSwapBuffers(this->pWindow);
    glfwWaitEvents();
    this->setStatus();
    this->setEngine();
    return true;
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
        std::string name = "./assets/";
        name += std::to_string(i);
        name += ".bmp";
        this->_textures.insert(std::make_pair(static_cast<eTexture>(i), this->loadBMP(name.c_str())));
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
    int width, height;
    unsigned char * data;
    FILE * file;

    file = fopen( filename, "rb" );

    if ( file == NULL ) return 0;
    width = CELL_UNITY;
    height = CELL_UNITY;
    data = (unsigned char *)malloc( width * height * 3 );
    fread( data, width * height * 3, 1, file );
    fclose( file );

    for (int i = 0; i < width * height ; ++i)
    {
      int index = i*3;
      unsigned char B,R;
      B = data[index];
      R = data[index+2];

      data[index] = R;
      data[index+2] = B;

   }

   glGenTextures(1, &texture);
   glBindTexture(GL_TEXTURE_2D, texture);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 30, 30, 0, GL_RGB, GL_UNSIGNED_BYTE, data);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

// texture_data is the source data of your texture, in this case
// its size is sizeof(unsigned char) * texture_width * texture_height * 4

    // glGenerateMipmap(GL_TEXTURE_2D); // Unavailable in OpenGL 2.1, use gluBuild2DMipmaps() insteads.

    // glBindTexture(GL_TEXTURE_2D, 0);
   return texture;

}
