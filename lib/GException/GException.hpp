#ifndef GEXCEPTION_HPP
# define GEXCEPTION_HPP


# include <iostream>

# define EX_FILE 0

class GException {

    public:
        GException(void);
        GException(GException const &src);
        ~GException(void);

        GException           &operator=(GException const &rhs);

        static  GException   &Throw(int code);
        void                Display(std::string, std::exception &e) const;

        class GraphicalException : public std::exception {};

    private:
        class FileException : public GraphicalException { virtual const char * what (void) const throw () { return "Can't open file :"; } };
};

#endif
