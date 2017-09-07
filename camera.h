#ifndef CAMERA_H
#define CAMERA_H

#include <glm/glm.hpp>

#include "elements.h"

class Camera {
public:
	glm::vec3 position;
	float f_dist;
	glm::vec3 vpn;	
	glm::vec3 v;
	glm::vec3 u;
	glm::vec3 look_at;
	float width;
	float height;
	bool ortho;

	glm::mat4 wtc;

	Camera(glm::vec3 position_, glm::vec3 look_at_, float f_dist_, int width, int height, bool ortho_);

	ray compute_ray(float i, float j);

};


#endif