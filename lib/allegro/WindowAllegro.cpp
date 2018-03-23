#include "WindowAllegro.hpp"

Window::Window(void) { return; }

Window::Window(unsigned int width, unsigned int height, eHook hook) :
    wWidth(width),
    wHeight(height),
    hook(hook),
    engineChecker(false),
    engine(SFML)
{
    // al_init();
    // al_init_image_addon();
    // ALLEGRO_DISPLAY     *window = al_create_display(this->wWidth, this->wHeight);
    // ALLEGRO_EVENT_QUEUE *events = al_create_event_queue();
    // printf("w : %d  h : %d\n", this->wWidth, this->wHeight);
    // this->pWindow = window;
    // this->pQueue = events;
    // al_install_keyboard();
    //
	// al_register_event_source(events, al_get_keyboard_event_source());
	// al_register_event_source(events, al_get_display_event_source(window));
    ALLEGRO_DISPLAY *display = NULL;
    al_init();
    display = al_create_display(600,600);
    al_clear_to_color(al_map_rgb(22,22,24));
    al_flip_display();
    al_rest(10);
    al_destroy_display(display);
    return;
}

Window::~Window(void) {
    al_destroy_display(this->pWindow);
    return;
}

void    Window::drawFrame(std::list <IEntity *> data, int lives, int score) const {
    // ALLEGRO_BITMAP * bitmap = al_load_bitmap("./assets/1.bmp");
    // std::cout << bitmap <<std::endl;
    // // al_clear_to_color(al_map_rgb(22,22,24));
    //
    // al_draw_bitmap(bitmap, 20, 20, 0);
    // std::cout << "hello" <<std::endl;
	// al_flip_display();
    // al_destroy_bitmap(bitmap);

    return;
}

bool    Window::displayPause(int status) {
    return true;
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
void    Window::changeHook(eHook hook){
    this->hook = hook;
}

eEngine   Window::getEngine(void) const {
    return this->engine;
}

bool    Window::engineHasChanged(void) const{
    return this->engineChecker;
}

void   Window::setHooks(void) {

}


unsigned int    Window::getWidth(void) const {
    return this->wWidth;
}

unsigned int    Window::getHeight(void) const {
    return this->wHeight;
}
//
// void       Window::initTextures(void) {
//     eTexture texture;
//
//     for (int i = 1; i <= 22; i++) {
//         if (i == 5 || i == 6 || i == 7 || i == 8) {i++; continue;} // Delete this line when headmiam
//         std::string name = "/assets/";
//         name += std::to_string(i);
//         name += ".bmp";
//         this->_textures.insert(std::make_pair(static_cast<eTexture>(i), this->loadBMP(name.c_str())));
//     }
//     return;
// }


Window    *createWindow(unsigned int width, unsigned int height, eHook hook) {
    return new Window(width, height, hook);
}

void      deleteWindow(Window *window) {
  delete window;
}
