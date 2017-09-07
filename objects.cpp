#include <math.h>

#include "objects.h"
#include "elements.h"
#include "utils.h"


#include <glm/vec3.hpp>
#include <glm/glm.hpp>


#define PI 3.14159265

//////////////////////////// OBJ INTERSECTION //////////////////////////////////////

ObjIntersection::ObjIntersection(bool check_, glm::vec3 point_, float distance_, Object *obj_, glm::vec3 norm_){
	check = check_;
	point = point_;
	distance = distance_;
	obj = obj_;
	norm = norm_;

};


//////////////////////////// SPHERE ////////////////////////////////////////////////

Sphere::Sphere(glm::vec3 pos_, double rad_, material m_) {
	position = pos_;
	radius = rad_;
	mat = m_;
	type = "sphere";
	txt = false;
	bump = false;
};

Sphere::Sphere(glm::vec3 pos, double rad, material m, bool txt_, Texture texture_) {

	position = pos;
	radius = rad;
	mat = m;
	txt = txt_;
	texture = texture_;

}

ObjIntersection Sphere::ray_intersect(ray r) {

	glm::vec3 T = r.o - position;

	float A = glm::dot(r.d, r.d);
	float B = 2.0f * glm::dot(r.d,T);
	float C = glm::dot(T, T) - radius * radius;
	float delta = B*B -4*A*C;

	if(delta < 0) {
		return ObjIntersection();
	}

	float s = sqrt(delta);
	float t0 = (-B - s)/(2*A);
	float t1 = (-B + s)/(2*A);

	float t;
	if(t0 > 0 && t1 > 0){
		t = std::min(t0,t1);
	}
	else if (t0 < 0 && t1 > 0){
		t = t1;
	}
	else if (t0 > 0 && t1 < 0){
		t = t0;
	}
	else {
		return ObjIntersection();
	}

	if(t < 0) {
		return ObjIntersection();
	}

	glm::vec3 point = r.o + (t * r.d); 

	glm::vec3 vec = point - r.o;

	float dist = sqrt( pow(vec[0],2) + pow(vec[1],2) + pow(vec[2],2) );

	return ObjIntersection(true, point, dist, dynamic_cast<Object*>(this), glm::normalize(point - position));;
};

glm::vec3 Sphere::get_color_txt(ray r, ObjIntersection intr) {

	glm::vec3 d = glm::normalize(position - intr.point);

	//std::cout << std::endl << d.x << " " << d.y << " " << d.z << std::endl;

	float u = - 0.5 * ( atan2(d.z, d.x) /(PI + 1) );
	float v = 0.5 - asin(d.y) / PI;

	int xt = floor(v*(texture.tcols-1)) + 1;
	int yt = texture.trows - floor(u*(texture.trows-1));

	Mat bgr[3];

	//std::cout << std::endl << u << " " << v << std::endl;
	//std::cout << std::endl << xt << " " << yt << std::endl;

	split(texture.image,bgr);

	return glm::vec3(bgr[2].at<unsigned char>(xt,yt), bgr[1].at<unsigned char>(xt,yt), bgr[0].at<unsigned char>(xt,yt));

}	

void Sphere::load_texture(const char *filename) {

	std::cout << "Loading texture: " << filename << std::endl;

	txt = true;

	texture = Texture(filename);

	mat = material_neutral;

}



//////////////////////////////// TRIMESH ////////////////////////////////////////////

TriMesh::TriMesh(glm::vec3 v1, glm::vec3 v2, glm::vec3 v3, material mat_) {
	vertex.push_back(v1);
	vertex.push_back(v2);
	vertex.push_back(v3);

	norm = glm::cross((v2 - v1), (v3 - v1));

	mat = mat_;

	txt = false;
	bump = false;

	type = "trimesh";

};

TriMesh::TriMesh(glm::vec3 v1, glm::vec3 v2, glm::vec3 v3, material mat_, bool txt_, Texture texture_, std::vector<glm::vec2> txt_coord_,
	bool bump_, Texture bump_map_, std::vector<glm::vec2> bump_coord_) {
	
	vertex.push_back(v1);
	vertex.push_back(v2);
	vertex.push_back(v3);

	norm = glm::cross((v2 - v1), (v3 - v1));

	mat = mat_;

	txt = txt_;
	texture = Texture(texture_);
	txt_coord = txt_coord_;

	bump = bump_;
	bump_map = bump_map_;
	bump_coord = bump_coord_;

	type = "trimesh";

};


ObjIntersection TriMesh::ray_intersect(ray r) {

	float den = glm::dot(r.d, norm);

	if(den == 0) {
		return ObjIntersection();
	}

	glm::vec3 p0l0 = (vertex[0] - r.o);
	float num = glm::dot(p0l0, this->norm);

	float alpha = num / den;

	if(alpha < 0) {
		return ObjIntersection();
	}
	
	glm::vec3 point = r.o + (alpha * r.d); 

	// check if is internal

	float c1 = glm::dot(glm::cross((vertex[1] - vertex[0]), (point - vertex[0])), norm);
	float c2 = glm::dot(glm::cross((vertex[2] - vertex[1]), (point - vertex[1])), norm);
	float c3 = glm::dot(glm::cross((vertex[0] - vertex[2]), (point - vertex[2])), norm);

	if(c1 >= 0 && c2 >= 0 && c3 >= 0) {
		
		glm::vec3 vec = point - r.o;

		float dist = sqrt( pow(vec[0],2) + pow(vec[1],2) + pow(vec[2],2) );

		return ObjIntersection(true, point, dist, dynamic_cast<Object*>(this), norm);
	};


	return ObjIntersection();
};

glm::vec3 TriMesh::get_color_txt(ray r, ObjIntersection intr) {

	float den = glm::dot(r.d, norm);

	if(den == 0) {
		return glm::vec3(0,1,0);
	}

	glm::vec3 p0l0 = (vertex[0] - r.o);
	float num = glm::dot(p0l0, this->norm);

	float alpha = num / den;

	if(alpha < 0) {
		return glm::vec3(0,1,0);
	}
	
	glm::vec3 point = r.o + (alpha * r.d); 

	// check if is internal

	float c1 = glm::dot(glm::cross((vertex[1] - vertex[0]), (point - vertex[0])), norm);
	float c2 = glm::dot(glm::cross((vertex[2] - vertex[1]), (point - vertex[1])), norm);
	float c3 = glm::dot(glm::cross((vertex[0] - vertex[2]), (point - vertex[2])), norm);

	if(c1 >= 0 && c2 >= 0 && c3 >= 0) {



		float z1 = 1/vertex[0][2];
    	float z2 = 1/vertex[1][2];
    	float z3 = 1/vertex[2][2];		

		float a = c1+c2+c3;

		float a1 = c1/a;
		float a2 = c2/a;
		float a3 = c3/a;


		glm::vec2 tcoord = a1*txt_coord[0]*z1 + a2*txt_coord[1]*z2 + a3*txt_coord[2]*z3;

		tcoord = tcoord / (a1*z1 + a2*z2 + a3*z3);

		int xt = floor(tcoord[0]*(texture.tcols-1)) + 1;
		int yt = texture.trows - floor(tcoord[1]*(texture.trows-1));
		
		Mat bgr[3];

		//bgr[0] = Mat::zeros(texture.image.rows, texture.image.cols, CV_8UC1);
		//bgr[1] = Mat::zeros(texture.image.rows, texture.image.cols, CV_8UC1);
		//bgr[2] = Mat::zeros(texture.image.rows, texture.image.cols, CV_8UC1);

		split(texture.image,bgr);

		return glm::vec3(bgr[2].at<unsigned char>(xt,yt), bgr[1].at<unsigned char>(xt,yt), bgr[0].at<unsigned char>(xt,yt));
	}
}	

void TriMesh::load_texture(const char *filename, glm::vec2 v1, glm::vec2 v2, glm::vec2 v3) {

	std::cout << "Loading texture: " << filename << std::endl;

	txt = true;

	texture = Texture(filename);

	txt_coord.push_back(v1);
	txt_coord.push_back(v2);
	txt_coord.push_back(v3);

	mat = material_neutral;

}

glm::vec3 TriMesh::get_norm_bump(ray r) {

	float den = glm::dot(r.d, norm);

	if(den == 0) {
		return glm::vec3(0,1,0);
	}

	glm::vec3 p0l0 = (vertex[0] - r.o);
	float num = glm::dot(p0l0, this->norm);

	float alpha = num / den;

	if(alpha < 0) {
		return glm::vec3(0,1,0);
	}
	
	glm::vec3 point = r.o + (alpha * r.d); 

	// check if is internal

	float c1 = glm::dot(glm::cross((vertex[1] - vertex[0]), (point - vertex[0])), norm);
	float c2 = glm::dot(glm::cross((vertex[2] - vertex[1]), (point - vertex[1])), norm);
	float c3 = glm::dot(glm::cross((vertex[0] - vertex[2]), (point - vertex[2])), norm);


	if(c1 >= 0 && c2 >= 0 && c3 >= 0) {






		float z1 = 1/vertex[0][2];
    	float z2 = 1/vertex[1][2];
    	float z3 = 1/vertex[2][2];		

		float a = c1+c2+c3;

		float a1 = c1/a;
		float a2 = c2/a;
		float a3 = c3/a;


		glm::vec2 tcoord = a1*bump_coord[0]*z1 + a2*bump_coord[1]*z2 + a3*bump_coord[2]*z3;

		tcoord = tcoord / (a1*z1 + a2*z2 + a3*z3);
	
		int xt = floor(tcoord[0]*(bump_map.tcols-1)) + 1;
		int yt = bump_map.trows - floor(tcoord[1]*(bump_map.trows-1));
	
		Mat bgr[3];

		split(bump_map.image,bgr);

		return glm::vec3(bgr[2].at<unsigned char>(xt,yt), bgr[1].at<unsigned char>(xt,yt), bgr[0].at<unsigned char>(xt,yt));
	}
}	

void TriMesh::load_bump_map(const char *filename, glm::vec2 v1, glm::vec2 v2, glm::vec2 v3) {

	std::cout << "Loading Bump Map: " << filename << std::endl;

	bump = true;

	bump_map = Texture(filename);

	bump_coord.push_back(v1);
	bump_coord.push_back(v2);
	bump_coord.push_back(v3);

}