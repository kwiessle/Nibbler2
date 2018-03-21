#include "WindowOpengl.hpp"

Window::Window(void) { return; }

Window::Window(unsigned int width, unsigned int height) :
    wWidth(width),
    wHeight(height),
    hook(hook),
    engineChecker(false),
    engine(SFML)
{
    if (!glfwInit()) { std::cout << "OpenGL init failed" << std::endl; exit(0);}
    else {
        glfwWindowHint(GLFW_SAMPLES, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        // glewExperimental = true;
        this->pWindow = glfwCreateWindow(
            this->wWidth,
            this->wHeight,
            "Nibbler",
            NULL,
            NULL
        );
        glfwMakeContextCurrent(this->pWindow);
        glfwSetInputMode(this->pWindow, GLFW_STICKY_KEYS, GL_TRUE);
        glEnable(GL_TEXTURE_2D);
        this->initTextures();
    }
    return;
}

Window::~Window(void) {
    glfwDestroyWindow(this->pWindow);
    glfwTerminate();
    return;
}

void    Window::drawFrame(std::list <IEntity *> data) const {
    // std::cout << "OpenGl ha to paint" << std::endl;
    return;
}

eHook   Window::getHooks(void) const {
    return this->hook;
}
eEngine  Window::getEngine(void) const {
    return this->engine;
}

bool    Window::engineHasChanged(void) const{
    return this->engineChecker;
}

void   Window::setHooks(void) {
    // sf::Event   event;
    glfwPollEvents();
    // if (event.type == sf::Event::Closed) { this->hook = Exit; return;}
    // if (event.type == sf::Event::KeyPressed) {
        if (glfwGetKey(this->pWindow, GLFW_KEY_ESCAPE) ) { this->hook = Exit; }
    //     if (glfwGetKey(this->pWindow, GLF_KEY_UP) && this->hook != Down) { this->hook = Up; }
    //     if (glfwGetKey(this->pWindow, GLF_KEY_DOWN) && this->hook != Up) { this->hook = Down; }
    //     if (glfwGetKey(this->pWindow, GLF_KEY_LEFT) && this->hook != Right) { this->hook = Left; }
    //     if (glfwGetKey(this->pWindow, GLF_KEY_RIGHT) && this->hook != Left) { this->hook = Right; }
    //     if (glfwGetKey(this->pWindow, GLF_KEY_F) && this->engine != SDL) { this->hook = SDL; this->engine = SDL; }
    //     if (glfwGetKey(this->pWindow, GLF_KEY_G) && this->engine != SFML) { this->hook = SFML; this->engine = SFML;  }
    //
    // }
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
        // std::cout << this->_textures[static_cast<eTexture>(i)] << std::endl;
    }
    return;
}


Window    *createWindow(unsigned int width, unsigned int height, eHook hook) {
    return new Window(width, height, hook);
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

    for(int i = 0; i < width * height ; ++i)
   {
      int index = i*3;
      unsigned char B,R;
      B = data[index];
      R = data[index+2];

      data[index] = R;
      data[index+2] = B;

   }


   glGenTextures( 1, &texture );
   glBindTexture( GL_TEXTURE_2D, texture );
   glTexEnvf( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE,GL_MODULATE );
   glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,GL_LINEAR_MIPMAP_NEAREST );


   glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,GL_LINEAR );
   glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S,GL_REPEAT );
   glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T,GL_REPEAT );
   gluBuild2DMipmaps( GL_TEXTURE_2D, 3, width, height,GL_RGB, GL_UNSIGNED_BYTE, data );
   free( data );
   std::cout << texture << std::endl;
   return texture;

}
