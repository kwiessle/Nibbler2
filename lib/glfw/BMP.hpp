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
    std::vector<std::uint8_t> GetPixels() const {return this->Pixels;}
    std::uint32_t GetWidth() const {return this->width;}
    std::uint32_t GetHeight() const {return this->height;}
    bool HasAlphaChannel() {return BitsPerPixel == 32;}
};

#endif


// int main()
// {
//     BMP info = BMP("C:/Users/....../Desktop/SomeBmp.bmp");
//
//     GLuint texture = 0;
//     glGenTextures(1, &texture);
//     glBindTexture(GL_TEXTURE_2D, texture);
//     glTexImage2D(GL_TEXTURE_2D, 0, info.HasAlphaChannel() ? GL_RGBA : GL_RGB, info.GetWidth(), info.GetWidth(), 0, info.HasAlphaChannel() ? GL_BGRA : GL_BGR, GL_UNSIGNED_BYTE, info.GetPixels().data());
// }
