#ifndef RENDERER_H
#define RENDERER_H

#include <glm/vec3.hpp>

#include <opencv2/opencv.hpp>

#include "objects.h"
#include "elements.h"
#include "utils.h"
#include "scene.h"
#include "camera.h"

using namespace cv;

class Renderer {

public:

	bool aa_active;
	bool dof_active;
	float f_dist;
	float lens_r;
	Scene *scene;
	Camera *camera;

	Renderer(Scene *scene_, Camera *camera_, bool aa_active_);
	Renderer(Scene *scene_, Camera *camera_, bool aa_active_, bool dof_active_, float f_dist_, float lens_r_);

	void render();

	ray random_dof_ray(ray r,float f_dist, float lens_r);
	glm::vec3 dof_intersect(ray r);

};

#endif