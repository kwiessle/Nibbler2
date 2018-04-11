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
        default : throw std::exception();
    }
    return shared;
}

void            GException::Display(std::string context, std::exception &e) const {

    std::cout << "\033[31m Graphical Exception : " << "\033[34m";
    std::cout << e.what() << " " << context;
    return;
}
