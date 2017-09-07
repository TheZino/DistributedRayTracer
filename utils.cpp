#include "utils.h"


glm::vec3 fix_color(glm::vec3 color) {

	for(int i=0; i<color.length();++i) {
		
	//	std::cout << color[i] << std::endl;
		color[i] = round(color[i]);
		color[i] = color[i]<0 ? 0 : color[i];
		color[i] = color[i]>255 ? 255 : color[i];
	}
 
	return color;
};

void draw_pixel(cv::Mat *R, cv::Mat *G, cv::Mat *B, int x, int y, glm::vec3 color) {

	//std::cout << "x: " << x << "y: "<< y << std::endl;
	
	R->at<float>(y,x) = color[0];
	G->at<float>(y,x) = color[1];
	B->at<float>(y,x) = color[2];
};

void save_image(cv::Mat R, cv::Mat G, cv::Mat B) {

	cv::Mat image;
	std::vector<cv::Mat> img;

	img.push_back(B);
	img.push_back(G);
	img.push_back(R);

	cv::merge(img, image);
	cv::imwrite("Render.png", image);
};

void show_image(cv::Mat R, cv::Mat G, cv::Mat B) {
	cv::Mat image;
	std::vector<cv::Mat> img;
	cv::Mat image_char;

	img.push_back(B);
	img.push_back(G);
	img.push_back(R);

	cv::merge(img, image);
	
	cv::namedWindow("Rendering", cv::WINDOW_AUTOSIZE);
	image.convertTo(image_char, CV_8UC1); 
	cv::imshow("Rendering", image_char);
	
	cv::waitKey(0);
};


glm::vec3 Phong_illumination(ObjIntersection intr, ray r, Light l, glm::vec3 eye) {

	glm::vec3 normal = intr.norm;

	if(intr.obj->type.compare("trimesh") == 0) {
		
		//std::cout << std::endl <<intr.obj->texture.loaded << std::endl;

		if(intr.obj->bump) {
			normal = intr.obj->get_norm_bump(r);
		}
	}

	// diffusive component
	glm::vec3 Nn = glm::normalize( normal ); 
	glm::vec3 Ln = glm::normalize( l.position - intr.point );

	float cos_theta = std::max(0.0f,glm::dot(Nn,Ln));

	glm::vec3 Id =  l.color * (intr.obj->mat.kd * cos_theta);

	// specular component
	glm::vec3 Vn = glm::normalize(eye - intr.point);
	glm::vec3 Rn = glm::normalize((2*glm::dot(Ln,Nn)) * Nn- Ln);

	float cos_alpha = std::pow(std::max(0.0f,glm::dot(Rn,Vn)), intr.obj->mat.sh);

	glm::vec3 Is = 	l.color * intr.obj->mat.ks * cos_alpha;

	glm::vec3 color;
	color =	l.inten * (Id + Is);

	return color;
}
