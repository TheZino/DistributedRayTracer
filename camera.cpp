#include "camera.h"

Camera::Camera(glm::vec3 position_, glm::vec3 look_at_, float f_dist_, int width_, int height_, bool ortho_) {

	ortho = ortho_;

	width = width_;
	height = height_;

	f_dist = f_dist_;
	position = position_;

	vpn = glm::normalize(position - look_at_);

	//std::cout << vpn[0] << " " << vpn[1] << " " << vpn[2] << std::endl;

	glm::vec3 up(0, 1, 0);

	u = glm::normalize(glm::cross(up, vpn));
	v = glm::normalize(glm::cross(vpn, u));

	//initialization of camera to word matrix

	glm::mat4 M;

	M[0][0] = u[0];
	M[0][1] = u[1];
	M[0][2] = u[2];

	M[0][3] = -(position[0]*u[0] + position[1]*u[1] + position[2]*u[2]);

	M[1][0] = v[0];
	M[1][1] = v[1];
	M[1][2] = v[2];


	M[1][3] = -(position[0]*v[0] + position[1]*v[1] + position[2]*v[2]);

	M[2][0] = vpn[0];
	M[2][1] = vpn[1];
	M[2][2] = vpn[2];

	M[2][3] = -(position[0]*vpn[0] + position[1]*vpn[1] + position[2]*vpn[2]);

	M[3][0] = 0;
	M[3][1] = 0;
	M[3][2] = 0;
	
	M[3][3] = 1;

	wtc = M;
	
	
/*
	std::cout << "Camera eye: " << position[0] << " " << position[1] << " " << position[2] << std::endl;	
	std::cout << "Camera u: " << u[0] << " " << u[1] << " " << u[2] << std::endl;
	std::cout << "Camera v: " << v[0] << " " << v[1] << " " << v[2] << std::endl;
	std::cout << "Camera norm: " << vpn[0] << " " << vpn[1] << " " << vpn[2] << std::endl;
*/

}

ray Camera::compute_ray(float i, float j) {

	//std::cout << i << std::endl;

	float aspect_ratio = width/height;

	float x = (((2 * (i)) / width) - 1) * aspect_ratio ;
	float y = ((2 * (j)) / height) - 1;
	float z = f_dist;

	glm::vec3 zn = -vpn;
	//std::cout << x << " " << " " << y << " " << z << std::endl;

	glm::vec3 image_point(x, y, -z);

	//glm::vec3 ray_direction = image_point - glm::vec3(0,0,0);

	glm::vec3 origin;
	glm::vec3 ray_direction;

	if(!ortho) {
		origin = glm::vec3(0,0,0);
		ray_direction = image_point - glm::vec3(0,0,0);
	}
	else {
		origin = glm::vec3((i- (width/2)),(j-(height/2)),0);
		ray_direction = zn;
	}

/*
	if(i == width/2 && j == height/2){
		std::cout << "image_point: " << image_point[0] << " " << image_point[1] << " " << image_point[2] << std::endl;
		std::cout << "ray_direction: " << ray_direction[0] << " " << ray_direction[1] << " " << ray_direction[2] << std::endl;
		
	}
*/

	//std::cout << "Aspect ratio: " << aspect_ratio << std::endl;

	return ray(origin, ray_direction);

}