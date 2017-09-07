#ifndef OBJECTS_H
#define OBJECTS_H

#include <glm/vec3.hpp>
#include <vector>
#include <string>

#include "elements.h"
#include "materials.h"
#include "texture.h"

/**
* Objects drawable in the scene
* - Struct containing intersection infos
* - Obj definition
* - Sphere (Obj)
*/

class Object;

struct ObjIntersection {

	bool check;			// true if there's an intersection between ray and obj 
	glm::vec3 point;	// intersection point
	float distance;		// alpha
	Object *obj;		// object interested
	glm::vec3 norm;		// norm point surface	

	ObjIntersection(bool check_ = false, glm::vec3 point_ = glm::vec3(), float distance_ = 0, Object *obj_ = NULL, glm::vec3 norm_ = glm::vec3());

};

class Object {

public:
	material mat;
	std::string type;

	bool txt;
	Texture texture;

	bool bump;
	Texture bump_map;

	virtual ObjIntersection ray_intersect(ray r) {};
	virtual glm::vec3 get_color_txt(ray r, ObjIntersection intr) {};
	virtual glm::vec3 get_norm_bump(ray r) {};

};

class Sphere: public Object {

public:
	glm::vec3 position;
	double radius;

	Sphere(glm::vec3 pos, double rad, material m);
	Sphere(glm::vec3 pos, double rad, material m, bool txt_, Texture texture_);
	
	void load_texture(const char *filename);
	virtual glm::vec3 get_color_txt(ray r, ObjIntersection intr);

	virtual ObjIntersection ray_intersect(ray r);

};

class TriMesh: public Object {

public:
	std::vector<glm::vec3> vertex;
	glm::vec3 norm;
	std::vector<glm::vec2> txt_coord;
	std::vector<glm::vec2> bump_coord;
	std::vector<glm::vec3> tangents;
	std::vector<glm::vec3> bitangents;



	TriMesh(glm::vec3 v1, glm::vec3 v2, glm::vec3 v3, material mat_);

	TriMesh(glm::vec3 v1, glm::vec3 v2, glm::vec3 v3, material mat_, bool txt_, Texture texture_, std::vector<glm::vec2> txt_coord_,
		bool bump_, Texture bump_map_, std::vector<glm::vec2> bump_coord_);


	void load_texture(const char *filename, glm::vec2 v1, glm::vec2 v2, glm::vec2 v3);
	void load_bump_map(const char *filename, glm::vec2 v1, glm::vec2 v2, glm::vec2 v3);

	virtual ObjIntersection ray_intersect(ray r);

	virtual glm::vec3 get_color_txt(ray r, ObjIntersection intr);
	virtual glm::vec3 get_norm_bump(ray r);

};

#endif // OBJECTS_H