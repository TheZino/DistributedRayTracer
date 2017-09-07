#ifndef TEXTURE_H
#define TEXTURE_H

#include <vector>
#include <glm/glm.hpp>

#include <opencv2/opencv.hpp>

using namespace cv;

class Texture {

public:
    int tcols;
    int trows;
    bool loaded = false;
    Mat image;



    Texture(const char* filename);
    Texture(const Texture& other);
    Texture(){};


};

#endif // TEXTURE_H