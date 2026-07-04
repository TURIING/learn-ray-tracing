#pragma once

#include <string>
#include <vector>

class Image {
public:
    Image(int width, int height, int channels = 3);

    void setPixel(int x, int y, unsigned char r, unsigned char g, unsigned char b);
    void setPixel(int x, int y, unsigned char r, unsigned char g, unsigned char b, unsigned char a);

    void getPixel(int x, int y, unsigned char& r, unsigned char& g, unsigned char& b) const;
    void getPixel(int x, int y, unsigned char& r, unsigned char& g, unsigned char& b, unsigned char& a) const;

    bool save(const std::string& filename) const;

    int width() const { return m_width; }
    int height() const { return m_height; }
    int channels() const { return m_channels; }

    const unsigned char* data() const { return m_data.data(); }
    size_t dataSize() const { return m_data.size(); }

private:
    int m_width;
    int m_height;
    int m_channels;
    std::vector<unsigned char> m_data;

    size_t pixelIndex(int x, int y) const;
};
