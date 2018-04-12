#ifndef GEXCEPTION_HPP
# define GEXCEPTION_HPP


# include <iostream>

# define EX_FILE 0
# define WIN_FAIL 1

class GException {

    public:
        GException(void);
        GException(GException const &src);
        ~GException(void);

        GException           &operator=(GException const &rhs);
        static  GException   &Throw(int code);
        class GraphicalException : public std::exception {};
        class FileException : public GraphicalException {
                virtual const char * what (void) const throw () {
                    return "Can't open file";
                }
        };
        class WindowInit : public GraphicalException {
                virtual const char * what (void) const throw () {
                    return "Can't init graphical window";
                }
        };
};

#endif
