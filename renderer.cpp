#include "renderer.h"

Renderer::Renderer(Scene *scene_, Camera *camera_, bool aa_active_) {
	scene = scene_;
	camera = camera_;
	aa_active = aa_active_;
	dof_active = false;
	f_dist = 0.0;

}

Renderer::Renderer(Scene *scene_, Camera *camera_, bool aa_active_, bool dof_active_, float f_dist_, float lens_r_) {
	scene = scene_;
	camera = camera_;
	aa_active = aa_active_;
	dof_active = dof_active_;
	f_dist = f_dist_;
	lens_r = lens_r_;

}

void Renderer::render() {

	//std::cout << "Renderer::render" << std::endl;

	int width = camera->width;
	int height = camera->height; 

	float dof_ray_number = 100.0f;

	std::cout << "=== Rendering "<< width << "x" <<height << " image ===" << std::endl;

	// Output image initialization
	Mat R = Mat::zeros(height, width, CV_32FC1); // R
	Mat G = Mat::zeros(height, width, CV_32FC1); // G
	Mat B = Mat::zeros(height, width, CV_32FC1); // B

	// Ray definition
	ray r;

	//Ray casting for each pixel
	for(int y = 0; y < height; y++) {
		for(int x = 0; x < width; x++) {

			std::cout << "\r\t\t\t"; 
			std::cout << "\rx: " << x+1 << "\t y:" << y+1;	

			glm::vec3 color(0,0,0);

			if(aa_active) {


				if(dof_active) {

					for(float ay = 1; ay <= 3; ay++) {
						for(float ax = 1; ax <= 3; ax++) {
						// computing 9 ray from the camera
						r = camera->compute_ray(x+(ax/3), y + (ay/3));

						glm::vec3 color_dof(0,0,0);
						for(int k = 0; k < dof_ray_number; k++) {

							ray dof_r = random_dof_ray(r, f_dist, lens_r);

							color_dof += scene->trace(dof_r, camera->position);

						}

						color_dof = color_dof / dof_ray_number;

						color += color_dof;

						//std::cout << "color: " << color[0] << ", " << color[1] << ", " << color[2] <<std::endl;
						}
					}
					
					color = color /9.0f;

				}

				else {

					for(float ay = 1; ay <= 3; ay++) {
						for(float ax = 1; ax <= 3; ax++) {
						// computing 9 ray from the camera
						r = camera->compute_ray(x+(ax/3), y + (ay/3));	

						color += scene->trace(r, camera->position);
						//std::cout << "color: " << color[0] << ", " << color[1] << ", " << color[2] <<std::endl;
						}
					}
					
					color = color /9.0f;
				}
			}
			else {
			
				// computing the first ray from the camera
				r = camera->compute_ray(x, y);	

				if(dof_active) {

					for(int k = 0; k < dof_ray_number; k++) {

						ray dof_r = random_dof_ray(r, f_dist, lens_r);

						color += scene->trace(dof_r, camera->position);

					}

					color = color / dof_ray_number;

				}
				else {
					color = scene->trace(r, camera->position);
				}



			}

			//std::cout << "color: " << color_n[0] << ", " << color_n[1] << ", " << color_n[2] <<std::endl;

			draw_pixel(&R, &G, &B, x, (height-1)-y, color);
			
		}
		

	};

	std::cout << std::endl << "=== Rendering complete: Render.png ===" << std::endl;

	// Visualization and image save

	show_image(R, G, B);
	save_image(R, G, B);

	std::cout << "=== Render.png saved ===" << std::endl;
}


ray Renderer::random_dof_ray(ray r, float f_dist, float lens_r) {

	unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
	std::mt19937 generator (seed);
	std::uniform_real_distribution<double> uniform01(0.0, 1.0);

	double theta = 2 * M_PI * uniform01(generator);
	double phi = M_PI * uniform01(generator);

	glm::vec3 f_point = dof_intersect(r);

	//std::cout << f_point[0] << " " << f_point[1] << " " << f_point[2] << std::endl;


	float R = lens_r;

	float x = -R/2 + uniform01(generator)*R; 
	float y = -R/2 + uniform01(generator)*R;
	float z = r.d[2];


	return ray(glm::vec3(x,y,z), glm::normalize(f_point - glm::vec3(x,y,z)));

}

glm::vec3 Renderer::dof_intersect(ray r){

	glm::vec3 norm = camera->vpn;

	float den = glm::dot(r.d, norm);

	if(den == 0) {
		return glm::vec3(0,0,0);
	}

	glm::vec3 p0l0 = (r.o - glm::vec3(0,0,f_dist));
	float num = glm::dot(p0l0, norm);

	float alpha = num / den;

	if(alpha < 0) {
		return glm::vec3(0,0,0);
	}
	
	glm::vec3 point = r.o + (alpha * r.d);
	
	glm::vec3 vec = point - r.o;

	return point;
}