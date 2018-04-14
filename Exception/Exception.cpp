#include "Exception.hpp"


Exception::Exception(void) { return; }

Exception::Exception(Exception const &src) { *this = src; }

Exception::~Exception(void) { return; }

Exception      &Exception::operator=(Exception const &) { return *this; }

Exception      &Exception::Throw(int code) {
    static Exception   shared;

    switch (code) {
        case -1 : break;
        case EX_FILE : throw Exception::FileException(); break;
        case WIN_FAIL : throw Exception::WindowInit(); break;
        case USAGE : throw Exception::Usage(); break;
        case SIZE : throw Exception::Size(); break;
        case LIB_FAIL : throw Exception::LibFail(); break;
        default : throw std::exception();
    }
    return shared;
}
//
// GREEN = '\033[1;32m'
// BLUE = '\033[1;36m'
// RED = '\033[1;31m'


const char *Exception::FileException::what (void) const throw () {
    return "Can't open file";
};

const char * Exception::WindowInit::what (void) const throw () {
    return "Can't init graphical window";
};

const char * Exception::Usage::what (void) const throw () {
    return "\033[33;5m[1] usage:\033[0m  ./Nibbler \033[38;5;32mwidth height\033[0m path/to/dynamic_library\033[38;5;204m [--hardcore]\n\033[33;5m[2] param:\033[0m  \033[38;5;32mwidth\033[0m  [15-55]\n            \033[38;5;32mheight\033[0m [15-30]";
};

const char * Exception::Size::what (void) const throw () {
    return "error: 15 <= width <= 55 & 15 <= heigth <= 30";
};

const char * Exception::LibFail::what (void) const throw () {
    return "Binary Call failed\n\nusage: ./Nibbler width height path/to/dynamic_library [--hardcore]\n      15 <= width <= 55 & 15 <= heigth <= 30";

};
