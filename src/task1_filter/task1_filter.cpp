// Task 1 - Load a 512x512 image lena.raw
//        - Apply specified per-pixel transformation to each pixel
//        - Save as result.raw
#include <fstream>
#include <iostream>
#include "../../ppgso/image.h"
#include "../../ppgso/image_raw.h"
#include "../../ppgso/image_raw.cpp"
#include "../../ppgso/image.cpp"

// Size of the framebuffer
const unsigned int SIZE = 512;

//// A simple RGB struct will represent a pixel in the framebuffer
//struct Pixel {
//  uint8_t r,g,b;
//};

void grayScaleImage(ppgso::Image& image) {
    for (ppgso::Image::Pixel& px : image.getFramebuffer()) {
        auto magic = static_cast<uint8_t>((px.b * 0.11) + (0.59 * px.g) + (0.3 * px.r));
        ppgso::Image::updatePixelColor(px,magic,magic,magic);
    }
}

void invertImage(ppgso::Image& image) {
    for (ppgso::Image::Pixel& px : image.getFramebuffer()) {
        ppgso::Image::updatePixelColor(px,abs(px.r - UINT8_MAX),abs(px.g - UINT8_MAX),abs(px.b - UINT8_MAX));
    }
}

int main()
{
    // TODO: Open file lena.raw (this is 512x512 RAW GRB format)
    ppgso::Image img = ppgso::image::loadRAW("lena.raw",SIZE,SIZE);

    //grayScaleImage(img);

    invertImage(img);


    std::cout << "Generating result.raw file ..." << std::endl;

    ppgso::image::saveRAW(img,"result.raw");

  std::cout << "Done." << std::endl;
  return EXIT_SUCCESS;
}
