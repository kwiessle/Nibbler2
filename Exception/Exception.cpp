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


// class FileException : public GraphicalException {
const char *Exception::FileException::what (void) const throw () {
    return "Can't open file";
};

const char * Exception::WindowInit::what (void) const throw () {
    return "Can't init graphical window";
};

const char * Exception::Usage::what (void) const throw () {
    return "usage: ./Nibbler width height path/to/dynamic_library [--hardcore]\n      15 <= width <= 55 & 15 <= heigth <= 30";
};

const char * Exception::Size::what (void) const throw () {
    return "error: 15 <= width <= 55 & 15 <= heigth <= 30";
};

const char * Exception::LibFail::what (void) const throw () {
    return "Binary Call failed\n\nusage: ./Nibbler width height path/to/dynamic_library [--hardcore]\n      15 <= width <= 55 & 15 <= heigth <= 30";

};
