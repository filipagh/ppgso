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

void changeBrightnessImage(ppgso::Image& image, float percent) {
    for (ppgso::Image::Pixel& px : image.getFramebuffer()) {
        ppgso::Image::updatePixelColor(px,px.r*percent,px.g*percent,px.b*percent);
    }
}

void changeContrastImage(ppgso::Image& image, float percent) {
    for (ppgso::Image::Pixel& px : image.getFramebuffer()) {
        auto magic = static_cast<uint8_t>((px.b * 0.11) + (0.59 * px.g) + (0.3 * px.r));
        ppgso::Image::updatePixelColor(px,px.r+(magic*percent),px.g+(magic*percent),px.b+(magic*percent));
    }
}

ppgso::Image::Pixel getPixel(ppgso::Image& image ,int x, int y) {
    if (x < 0 || x >= image.width || y < 0 || y >= image.height) {
        ppgso::Image::Pixel px{0,0,0};
        return px;
    }
    return image.getPixel(x,y);
}

uint8_t roundToUint8(int number) {
    if (number < 0) {
        number = 0;
    }
    if (number > UINT8_MAX) {
        number = UINT8_MAX;
    }
    return static_cast<uint8_t>(number);
}

ppgso::Image::Pixel createDetectEdgePixel(ppgso::Image& source, int xSurPix, int ySurPix) {
    short int r,g,b;
    r=g=b=0;
int debug = 0;
    for (int x = xSurPix - 1; x <= xSurPix + 1; ++x) {
        for (int y = ySurPix-1; y <= ySurPix+1; ++y) {
            debug++;
            if (x == xSurPix && y == ySurPix) {
                if(getPixel(source,x,y).r != 0) {
                    int a = 0;
                }
                r += getPixel(source,x,y).r * 8;
                g += getPixel(source,x,y).g * 8;
                b += getPixel(source,x,y).b * 8;
            } else {
                r -= getPixel(source,x,y).r;
                g -= getPixel(source,x,y).g;
                b -= getPixel(source,x,y).b;
            }
        }

    }

    r = roundToUint8(r);
    g = roundToUint8(g);
    b = roundToUint8(b);

     if (r+g+b < 150)
    {r=g=b= 0;}

    int arr [3] = {abs(r-g), abs(r-b), abs(g-b)};
    int* max = std::max_element(arr,arr+3);
    if ((*max) > 80) {
        r=g=b= (static_cast<short>(*max));
    }

    ppgso::Image::Pixel finalPixel{static_cast<uint8_t>(r),static_cast<uint8_t>(g),static_cast<uint8_t>(b)};
    return finalPixel;
}

ppgso::Image detectEdges(ppgso::Image& sourceImg) {
    ppgso::Image img{sourceImg.width,sourceImg.height};
int debug=0;
    for (int x = 0; x < img.width; ++x) {
        for (int y = 0; y < img.width; ++y) {
            debug++;
            if (debug ==560) {
                int a = 0;
            }
            img.setPixel(x,y,createDetectEdgePixel(sourceImg,x,y));
        }
    }
    return img;

}


int main()
{
    // TODO: Open file lena.raw (this is 512x512 RAW GRB format)
    ppgso::Image img = ppgso::image::loadRAW("lena.raw",SIZE,SIZE);

//    grayScaleImage(img);

//    invertImage(img);

//    changeBrightnessImage(img,0.5);
//    changeContrastImage(img,0.5);
       
    img = detectEdges(img);


    std::cout << "Generating result.raw file ..." << std::endl;

    ppgso::image::saveRAW(img,"result.raw");

  std::cout << "Done." << std::endl;
  return EXIT_SUCCESS;
}
