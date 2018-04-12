#include "GException.hpp"


GException::GException(void) { return; }

GException::GException(GException const &src) { *this = src; }

GException::~GException(void) { return; }

GException      &GException::operator=(GException const &) { return *this; }

GException      &GException::Throw(int code) {
    static GException   shared;

    switch (code) {
        case -1 : break;
        case EX_FILE : throw GException::FileException(); break;
        case WIN_FAIL : throw GException::WindowInit(); break;
        default : throw std::exception();
    }
    return shared;
}
