#ifndef Exception_HPP
# define Exception_HPP


# include <iostream>

# define EX_FILE 0
# define WIN_FAIL 1
# define USAGE 2
# define SIZE 3
# define LIB_FAIL 4

class Exception {

    public:
        Exception(void);
        Exception(Exception const &src);
        ~Exception(void);

        Exception           &operator=(Exception const &rhs);
        static  Exception   &Throw(int code);
        class GraphicalException : public std::exception {};
        class GameException : public std::exception {};
        class FileException : public GraphicalException {
                virtual const char * what (void) const throw ();
        };
        class WindowInit : public GraphicalException {
                virtual const char * what (void) const throw ();
        };
        class Usage : public GameException {
                virtual const char * what (void) const throw ();
        };
        class Size : public GameException {
                virtual const char * what (void) const throw ();
        };
        class LibFail : public GameException {
                virtual const char * what (void) const throw ();
        };
};

#endif
