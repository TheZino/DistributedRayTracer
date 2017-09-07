#ifndef SCENE_H
#define SCENE_H

#include <opencv2/opencv.hpp>
#include <vector>
#include <glm/glm.hpp>
#include <typeinfo>
#include <math.h>
#include <random>
#include <cmath>
#include <chrono>

#include "objects.h"
#include "elements.h"
#include "utils.h"

class Scene {

public:

	std::vector<Object*> objs;
	std::vector<Light*> lights;
	bool soft_shadows;

	Scene(bool soft_shadows_): soft_shadows(soft_shadows_){};

	void add(Object *obj);
	void add_light(Light *l);
	int objs_number();



	Scene world_to_camera(glm::mat4 Mwc);

	ObjIntersection intersect(ray r);

	glm::vec3 trace(ray r, glm::vec3 eye);

	glm::vec3 shade(ObjIntersection intr, ray r, glm::vec3 eye, int recursionDepth, double n1);

	glm::vec3 reflection(ObjIntersection intr, ray r, int recursionDepth, double n1);

	glm::vec3 refraction(ObjIntersection intr, ray r, int recursionDepth, double n1);

	ray random_shadow_ray(glm::vec3 s_position, Light l);

	ray random_glossy_ray(glm::vec3 s_position, glm::vec3 ref_dir, float density);

};


#endif