#include <gtest/gtest.h>
#include <fstream>
#include <utils/Image.h>

TEST(ImageTest, ConstructionValid) {
    Image img(640, 480, 3);
    EXPECT_EQ(img.width(), 640);
    EXPECT_EQ(img.height(), 480);
    EXPECT_EQ(img.channels(), 3);
    EXPECT_EQ(img.dataSize(), 640u * 480 * 3);
}

TEST(ImageTest, ConstructionInvalidDimensions) {
    EXPECT_THROW(Image(0, 100, 3), std::invalid_argument);
    EXPECT_THROW(Image(100, -1, 3), std::invalid_argument);
}

TEST(ImageTest, ConstructionInvalidChannels) {
    EXPECT_THROW(Image(100, 100, 0), std::invalid_argument);
    EXPECT_THROW(Image(100, 100, 5), std::invalid_argument);
}

TEST(ImageTest, DefaultPixelsAreBlack) {
    Image img(10, 10, 3);
    unsigned char r, g, b;
    img.getPixel(0, 0, r, g, b);
    EXPECT_EQ(r, 0);
    EXPECT_EQ(g, 0);
    EXPECT_EQ(b, 0);
}

TEST(ImageTest, SetAndGetPixelRGB) {
    Image img(100, 100, 3);
    img.setPixel(50, 50, 255, 128, 64);
    unsigned char r, g, b;
    img.getPixel(50, 50, r, g, b);
    EXPECT_EQ(r, 255);
    EXPECT_EQ(g, 128);
    EXPECT_EQ(b, 64);
}

TEST(ImageTest, SetAndGetPixelRGBA) {
    Image img(100, 100, 4);
    img.setPixel(10, 20, 100, 150, 200, 255);
    unsigned char r, g, b, a;
    img.getPixel(10, 20, r, g, b, a);
    EXPECT_EQ(r, 100);
    EXPECT_EQ(g, 150);
    EXPECT_EQ(b, 200);
    EXPECT_EQ(a, 255);
}

TEST(ImageTest, SetPixelWrongChannelsThrows) {
    Image img(10, 10, 1);
    EXPECT_THROW(img.setPixel(0, 0, 255, 0, 0), std::runtime_error);
}

TEST(ImageTest, SaveToPNG) {
    Image img(16, 16, 3);
    // Create a simple gradient pattern
    for (int y = 0; y < 16; y++) {
        for (int x = 0; x < 16; x++) {
            unsigned char r = static_cast<unsigned char>((x * 16) % 256);
            unsigned char g = static_cast<unsigned char>((y * 16) % 256);
            unsigned char b = 128;
            img.setPixel(x, y, r, g, b);
        }
    }

    std::string filename = "test_output.png";
    EXPECT_TRUE(img.save(filename));

    // Verify the file exists and has content
    std::ifstream file(filename, std::ios::binary | std::ios::ate);
    ASSERT_TRUE(file.good());
    EXPECT_GT(file.tellg(), 0);
    file.close();

    // Cleanup
    std::remove(filename.c_str());
}

TEST(ImageTest, MultipleChannels) {
    Image img1(5, 5, 1);
    EXPECT_EQ(img1.channels(), 1);
    EXPECT_EQ(img1.dataSize(), 25u);

    Image img4(5, 5, 4);
    EXPECT_EQ(img4.channels(), 4);
    EXPECT_EQ(img4.dataSize(), 100u);
}

TEST(ImageTest, DataPointer) {
    Image img(4, 4, 3);
    EXPECT_NE(img.data(), nullptr);
    EXPECT_EQ(img.dataSize(), 48u);
}
