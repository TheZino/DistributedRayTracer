#include <stdio.h>
#include <stdlib.h>
#include <iostream>

#include <glm/vec3.hpp>

#include <opencv2/opencv.hpp>

#include "renderer.h"
#include "objects.h"
#include "elements.h"
#include "materials.h"
#include "utils.h"
#include "scene.h"
#include "camera.h"

using namespace cv;


int main(int argc, char *argv[]) {

	// Output image dimensions
	int width = 1024;
	int height = 768;

	// Light

	Light light1(glm::vec3(100, 200, 500), glm::vec3(255, 255, 255), 1, 7);
	Light light2(glm::vec3(-100, 200, -100), glm::vec3(255, 255, 255), 0.5, 7);

	// Defining models
	Sphere origin = Sphere(glm::vec3(0,0,0), 100, glossy_mirror);

	Sphere s = Sphere(glm::vec3(0, 200, 100), 100, glossy_mirror_yellow);

	//s.load_texture("./textures/wall.png");

	Sphere sdiff = Sphere(glm::vec3(0, -300, 0), 100, mirror);
	Sphere ss = Sphere(glm::vec3(-200, 0, -100), 50, mirror);
	Sphere st = Sphere(glm::vec3(100, 0, 0), 70, mirror);
	Sphere sd = Sphere(glm::vec3(-200,-75,0), 100, white_glass);

	Sphere l_b = Sphere(light1.position, 20, light_bulb);

	TriMesh mir(glm::vec3(-400,-400,-100), glm::vec3(0,-400,-100), glm::vec3(-200,0,-100), mirror);

	TriMesh cube1(glm::vec3(-200,-400,100), glm::vec3(-50,-400,-50), glm::vec3(-50,0,-50), medium_gray);
	TriMesh cube2(glm::vec3(-50,0,-50), glm::vec3(-200,0,100), glm::vec3(-200,-400,100), medium_gray);

	TriMesh cube3(glm::vec3(-300,-400,-50), glm::vec3(-200,-400,100), glm::vec3(-200, 0, 100), medium_gray);
	TriMesh cube4(glm::vec3(-200, 0, 100), glm::vec3(-300, 0, -50), glm::vec3(-300,-400,-50), medium_gray);

	TriMesh cube5(glm::vec3(-200,0,100), glm::vec3(-50,0,-50), glm::vec3(-150,0,-200), medium_gray);
	TriMesh cube6(glm::vec3(-150,0,-200), glm::vec3(-300,0,-50), glm::vec3(-200,0,100), medium_gray);

	TriMesh cube7(glm::vec3(-150,-400,-200), glm::vec3(-50,-400,-50), glm::vec3(-50, 0, -50), medium_gray);
	TriMesh cube8(glm::vec3(-50, 0, -50), glm::vec3(-150, 0, -200), glm::vec3(-150,-400,-200), medium_gray);

	TriMesh cube9(glm::vec3(-300,-400,-50), glm::vec3(-150,-400,-200), glm::vec3(-150, 0, -200), medium_gray);
	TriMesh cube10(glm::vec3(-150, 0, -200), glm::vec3(-300, 0, -50), glm::vec3(-300,-400,-50), medium_gray);

	TriMesh cube11(glm::vec3(-200,-400,100), glm::vec3(-50,-400,-50), glm::vec3(-150,-400, -200), medium_gray);
	TriMesh cube12(glm::vec3(-150,-400,-200), glm::vec3(-300,-400,-50), glm::vec3(-200,-400,100), medium_gray);




	TriMesh wall_1( glm::vec3(100,-100,0), glm::vec3(-100,100,-30),glm::vec3(-100,-100,0), Red);
	TriMesh wall_2(glm::vec3(-100,100,-30), glm::vec3(100,-100,-0), glm::vec3(100,100,-30), Red);
	wall_1.load_texture("./textures/wall.png", glm::vec2(0,1), glm::vec2(0,0), glm::vec2(1,0));
	wall_2.load_texture("./textures/wall.png", glm::vec2(1,0), glm::vec2(1,1), glm::vec2(0,1));



/*  NOT WORKING

	TriMesh bwall_1(glm::vec3(-100,-100,150), glm::vec3(100,-100,-150), glm::vec3(-100,100,150), Orange);
	TriMesh bwall_2(glm::vec3(100,100,-150), glm::vec3(-100,100,150), glm::vec3(100,-100,-150), Orange);
	bwall_1.load_bump_map("./textures/bump.png", glm::vec2(0,1), glm::vec2(1,1), glm::vec2(1,0));
	bwall_2.load_bump_map("./textures/bump.png", glm::vec2(1,0), glm::vec2(0,0), glm::vec2(0,1));
**/

	// Cornell Box

	//front
	TriMesh f1(glm::vec3(400,-400,2000), glm::vec3(-400,-400,2000), glm::vec3(400,400,2000), White);
	TriMesh f2(glm::vec3(400,400,2000), glm::vec3(-400,-400,2000), glm::vec3(-400,400,2000), White);

	//back
	TriMesh c1(glm::vec3(-400,-400,-300), glm::vec3(400,-400,-300), glm::vec3(-400,400,-300), White);
	TriMesh c2(glm::vec3(-400,400,-300), glm::vec3(400,-400,-300), glm::vec3(400,400,-300), White);

	//top
	TriMesh t1(glm::vec3(-450,400,-300), glm::vec3(450,400,-300), glm::vec3(-450,400,2000), White);
	TriMesh t2(glm::vec3(-450,400,2000), glm::vec3(450,400,-300), glm::vec3(450,400,2000), White);

	//bottom
	TriMesh b1(glm::vec3(-450,-400,-300), glm::vec3(-450,-400,2000), glm::vec3(450,-400,-300), White);
	TriMesh b2(glm::vec3(450,-400,-300), glm::vec3(-450,-400,2000), glm::vec3(450,-400,2000), White);

	//left
	TriMesh l1(glm::vec3(-400,-400,2000), glm::vec3(-400,-400,-300), glm::vec3(-400,400,-300), Red);
	TriMesh l2(glm::vec3(-400,400,-300), glm::vec3(-400,400,2000), glm::vec3(-400,-400,2000), Red);

	//right
	TriMesh r1(glm::vec3(400,-400,-300), glm::vec3(400,-400,2000), glm::vec3(400,400,2000), Green);
	TriMesh r2(glm::vec3(400,400,-300), glm::vec3(400,-400,-300), glm::vec3(400,400,2000), Green);

	// Defining Scene
	Scene scene(false);

	// lights
	scene.add_light(&light1);
	//scene.add_light(&light2);

	// objects
	//scene.add(dynamic_cast<Object*>(&s));

	scene.add(dynamic_cast<Object*>(&sdiff));
	scene.add(dynamic_cast<Object*>(&ss));
	scene.add(dynamic_cast<Object*>(&st));
	//scene.add(dynamic_cast<Object*>(&sd));


	/*
	scene.add(dynamic_cast<Object*>(&cube1));
	scene.add(dynamic_cast<Object*>(&cube2));
	scene.add(dynamic_cast<Object*>(&cube3));
	scene.add(dynamic_cast<Object*>(&cube4));
	scene.add(dynamic_cast<Object*>(&cube5));
	scene.add(dynamic_cast<Object*>(&cube6));
	scene.add(dynamic_cast<Object*>(&cube7));
	scene.add(dynamic_cast<Object*>(&cube8));
	scene.add(dynamic_cast<Object*>(&cube9));
	scene.add(dynamic_cast<Object*>(&cube10));
	scene.add(dynamic_cast<Object*>(&cube11));
	scene.add(dynamic_cast<Object*>(&cube12));
	*/

	scene.add(dynamic_cast<Object*>(&mir));

	//scene.add(dynamic_cast<Object*>(&wall_1));
	//scene.add(dynamic_cast<Object*>(&wall_2));

	// NOT WORKING
	//scene.add(dynamic_cast<Object*>(&bwall_1));
	//scene.add(dynamic_cast<Object*>(&bwall_2));

	// origin
	//scene.add(dynamic_cast<Object*>(&origin));


	// light bulb
	//scene.add(dynamic_cast<Object*>(&l_b));

	// cornell box
	scene.add(dynamic_cast<Object*>(&f1));
	scene.add(dynamic_cast<Object*>(&f2));
	scene.add(dynamic_cast<Object*>(&c1));
	scene.add(dynamic_cast<Object*>(&c2));
	scene.add(dynamic_cast<Object*>(&t1));
	scene.add(dynamic_cast<Object*>(&t2));
	scene.add(dynamic_cast<Object*>(&b1));
	scene.add(dynamic_cast<Object*>(&b2));
	scene.add(dynamic_cast<Object*>(&l1));
	scene.add(dynamic_cast<Object*>(&l2));
	scene.add(dynamic_cast<Object*>(&r1));
	scene.add(dynamic_cast<Object*>(&r2));


	// Output image initialization
	cv::Mat R = Mat::zeros(height, width, CV_32FC1); // R
	cv::Mat G = Mat::zeros(height, width, CV_32FC1); // G
	cv::Mat B = Mat::zeros(height, width, CV_32FC1); // B

	// Cameras
	// After width and height: ortho
	Camera cam1(glm::vec3(200,0,200), glm::vec3(0,-100,0), 2, width, height, false);
	//Camera cam1(glm::vec3(0,0,100), glm::vec3(-200, -300,0), 2, width, height, false);

	// Changing scene in camera system
	// Soft shadows
	Scene scene_camera(false);
	scene_camera = scene.world_to_camera(cam1.wtc);


	// after camera: Antialiasing, DOF values
	Renderer renderer(&scene_camera, &cam1, false);//, true, 1400, 50);

	renderer.render();

	return 0;
}
