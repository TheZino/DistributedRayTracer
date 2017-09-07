#ifndef UTILS_H
#define UTILS_H

#include <glm/glm.hpp>
#include <math.h>
#include <opencv2/opencv.hpp>

#include "objects.h"

glm::vec3 fix_color(glm::vec3 color);

void draw_pixel(cv::Mat *R, cv::Mat *G, cv::Mat *B, int x, int y, glm::vec3 color);

void save_image(cv::Mat R, cv::Mat G, cv::Mat B);

void show_image(cv::Mat R, cv::Mat G, cv::Mat B);

glm::vec3 Phong_illumination(ObjIntersection intr, ray r, Light l, glm::vec3 eye);


#endif