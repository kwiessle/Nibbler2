#ifndef BMP_HPP
# define BMP_HPP

#include <vector>
#include <fstream>
#include "Exception.hpp"


typedef union PixelInfo
{
    std::uint32_t Colour;
    struct
    {
        std::uint8_t B, G, R, A;
    };
} *PPixelInfo;


class BMP
{
private:


    std::uint32_t width, height;
    std::uint16_t BitsPerPixel;
    std::vector<std::uint8_t> Pixels;

public:
    BMP(void);
    ~BMP(void);
    BMP(const char* FilePath);
    BMP(BMP const &src);
    BMP   &operator=(BMP const &rhs);
    std::vector<std::uint8_t> GetPixels() const {return this->Pixels;}
    std::uint32_t GetWidth() const {return this->width;}
    std::uint32_t GetHeight() const {return this->height;}
    bool HasAlphaChannel() {return BitsPerPixel == 32;}
};

#endif
