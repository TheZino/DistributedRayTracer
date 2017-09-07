#include <iostream>
#include <stdio.h>
#include <cmath>
#include <stdexcept>

#include "texture.h"

Texture::Texture(const char *filename) {

    image = imread(filename, CV_LOAD_IMAGE_COLOR );

    tcols = image.cols;
    trows = image.rows;

    loaded = true;

}

Texture::Texture(const Texture& other) {
    image = other.image;

    tcols = other.tcols;
    trows = other.trows;
    loaded = other.loaded;
}
