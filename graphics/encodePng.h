#ifndef RAY_TRACER_ENCODEPNG
#define RAY_TRACER_ENCODEPNG

#include "lodepng.h"
#include "..\SDL2mingw\x86_64-w64-mingw32\include\SDL2\SDL.h"
#include <iostream>
#include <string>

class Encoder{
public:
  void encodeOneStep(const char* filename, std::vector<unsigned char>& image, unsigned width, unsigned height)
  {
    //Encode the image
    unsigned error = lodepng::encode(filename, image, width, height);

    //if there's an error, display it
    if(error) std::cout << "encoder error " << error << ": "<< lodepng_error_text(error) << std::endl;
  }

  //saves image to filename given as argument. Warning, this overwrites the file without warning!
  int encode(int width, int height, Uint32* image, std::string filename)
  {
    std::vector<unsigned char> image_(width * height * 4);
    filename = "pictures/" + filename;
    
    for (int i = 0; i < height * width; ++i) {
      for (int byte = 0; byte < 3; ++byte) 
        image_[i * 4 + byte] = ((image[i] >> ((2 - byte) * 8)) & 255);
      image_[i * 4 + 3] = 255;
    }
    

    encodeOneStep(filename.c_str(), image_, width, height);
    return 0;
  }
};

#endif
