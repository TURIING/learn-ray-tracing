#define STB_IMAGE_WRITE_IMPLEMENTATION
#include <stb_image_write.h>

#include "Image.h"
#include <stdexcept>

Image::Image(int width, int height, int channels)
    : m_width(width)
    , m_height(height)
    , m_channels(channels)
{
    if (width <= 0 || height <= 0) {
        throw std::invalid_argument("Image dimensions must be positive");
    }
    if (channels < 1 || channels > 4) {
        throw std::invalid_argument("Channels must be between 1 and 4");
    }
    m_data.resize(static_cast<size_t>(width) * height * channels, 0);
}

size_t Image::pixelIndex(int x, int y) const
{
    return (static_cast<size_t>(y) * m_width + x) * m_channels;
}

void Image::setPixel(int x, int y, unsigned char r, unsigned char g, unsigned char b)
{
    if (m_channels < 3) {
        throw std::runtime_error("Image does not have RGB channels");
    }
    size_t idx = pixelIndex(x, y);
    m_data[idx] = r;
    m_data[idx + 1] = g;
    m_data[idx + 2] = b;
}

void Image::setPixel(int x, int y, unsigned char r, unsigned char g, unsigned char b, unsigned char a)
{
    if (m_channels < 4) {
        throw std::runtime_error("Image does not have RGBA channels");
    }
    size_t idx = pixelIndex(x, y);
    m_data[idx] = r;
    m_data[idx + 1] = g;
    m_data[idx + 2] = b;
    m_data[idx + 3] = a;
}

void Image::getPixel(int x, int y, unsigned char& r, unsigned char& g, unsigned char& b) const
{
    size_t idx = pixelIndex(x, y);
    r = m_data[idx];
    g = m_data[idx + 1];
    b = m_data[idx + 2];
}

void Image::getPixel(int x, int y, unsigned char& r, unsigned char& g, unsigned char& b, unsigned char& a) const
{
    size_t idx = pixelIndex(x, y);
    r = m_data[idx];
    g = m_data[idx + 1];
    b = m_data[idx + 2];
    a = m_data[idx + 3];
}

bool Image::save(const std::string& filename) const
{
    int result = 0;
    if (m_channels == 1 || m_channels == 2) {
        result = stbi_write_png(filename.c_str(), m_width, m_height, m_channels, m_data.data(), m_width * m_channels);
    } else {
        result = stbi_write_png(filename.c_str(), m_width, m_height, m_channels, m_data.data(), m_width * m_channels);
    }
    return result != 0;
}
