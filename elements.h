#ifndef ELEMENTS_H
#define ELEMENTS_H

#include <stdio.h>
#include <stdlib.h>
#include <iostream>

#include <glm/vec3.hpp>	

struct Light {
	glm::vec3 position;
	glm::vec3 color;
	float inten; // value between 0 and 1
	float radius;

	Light();
	Light(glm::vec3 position_, glm::vec3 color_, float inten_, float radius_): position(position_), color(color_), inten(inten_), radius(radius_) {};
};

struct ray {
	glm::vec3 o; //Ray origin
	glm::vec3 d; //Ray direction

	ray(){};
	ray(glm::vec3 o_, glm::vec3 d_): o(o_), d(d_) {};
};

#endif