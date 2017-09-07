#include "scene.h"

void Scene::add (Object *obj) {
	objs.push_back(obj);
};

void Scene::add_light(Light *l) {
		lights.push_back(l);
}

int Scene::objs_number() {
	return objs.size();
};

Scene Scene::world_to_camera(glm::mat4 Mwc) {

	long n_obj = objs.size();
	long n_light = lights.size();
	Scene scene_camera(soft_shadows);

	/*
	std::cout << "Mwc: " << Mwc[0][0] << " " << Mwc[0][1] << " "<< Mwc[0][2] << " " << Mwc[0][3] << std::endl;
	std::cout << "Mwc: " << Mwc[1][0] << " " << Mwc[1][1] << " "<< Mwc[1][2] << " " << Mwc[1][3] << std::endl;
	std::cout << "Mwc: " << Mwc[2][0] << " " << Mwc[2][1] << " "<< Mwc[2][2] << " " << Mwc[2][3] << std::endl;
	std::cout << "Mwc: " << Mwc[3][0] << " " << Mwc[3][1] << " "<< Mwc[3][2] << " " << Mwc[3][3] << std::endl;
	*/

	// transform each object into camera coordinates

	for (int i=0; i < n_obj; i++) {

		//std::cout << objs[i]->type << std::endl;
		
		// if the obj is a sphere change only the point position

		if (objs[i]->type.compare("sphere") == 0) {
			glm::vec4 spos_h;
			spos_h[0] = dynamic_cast<Sphere*>(objs[i])->position[0];
			spos_h[1] = dynamic_cast<Sphere*>(objs[i])->position[1];
			spos_h[2] = dynamic_cast<Sphere*>(objs[i])->position[2];
			spos_h[3] = 1;

			glm::vec4 scpos_h = spos_h * Mwc;

			glm::vec3 scpos( scpos_h[0]/scpos_h[3], scpos_h[1]/scpos_h[3], scpos_h[2]/scpos_h[3] );

			Sphere *s =  new Sphere(scpos, dynamic_cast<Sphere*>(objs[i])->radius, objs[i]->mat);

			//std::cout << "Position:" << scpos[0] << " " << scpos[1] << " " << scpos[2] << std::endl;

			scene_camera.add(dynamic_cast<Object*>(new Sphere(scpos, dynamic_cast<Sphere*>(objs[i])->radius, objs[i]->mat, objs[i]->txt, objs[i]->texture )));
		}

		// else if the obj is a trimesh it changes the vertices

		else if (objs[i]->type.compare("trimesh") == 0) {

			TriMesh t = *dynamic_cast<TriMesh*>(objs[i]);

			// Vertex 1
			glm::vec4 v1_h;
			v1_h[0] = t.vertex[0][0];
			v1_h[1] = t.vertex[0][1];
			v1_h[2] = t.vertex[0][2];
			v1_h[3] = 1;

			glm::vec4 v1c_h = v1_h * Mwc;

			glm::vec3 v1c(v1c_h[0]/v1c_h[3], v1c_h[1]/v1c_h[3], v1c_h[2]/v1c_h[3]);

			// Vertex 2
			glm::vec4 v2_h;
			v2_h[0] = t.vertex[1][0];
			v2_h[1] = t.vertex[1][1];
			v2_h[2] = t.vertex[1][2];
			v2_h[3] = 1;

			glm::vec4 v2c_h = v2_h * Mwc;

			glm::vec3 v2c(v2c_h[0]/v2c_h[3], v2c_h[1]/v2c_h[3], v2c_h[2]/v2c_h[3]);

			// Vertex 3
			glm::vec4 v3_h;
			v3_h[0] = t.vertex[2][0];
			v3_h[1] = t.vertex[2][1];
			v3_h[2] = t.vertex[2][2];
			v3_h[3] = 1;

			glm::vec4 v3c_h =  v3_h * Mwc;

			glm::vec3 v3c(v3c_h[0]/v3c_h[3], v3c_h[1]/v3c_h[3], v3c_h[2]/v3c_h[3]);

			// New trimesh
			/*
			std::cout << "Position v1:" << v1c[0] << " " << v1c[1] << " " << v1c[2] << std::endl;
			std::cout << "Position v2:" << v2c[0] << " " << v2c[1] << " " << v2c[2] << std::endl;
			std::cout << "Position v3:" << v3c[0] << " " << v3c[1] << " " << v3c[2] << std::endl;
			*/

			scene_camera.add(dynamic_cast<Object*>(new TriMesh(v1c, v2c, v3c, t.mat, t.txt, t.texture, t.txt_coord, t.bump, t.bump_map, t.bump_coord)));
		}
	}

	for (int i=0; i < n_light; i++) {
		Light l = *lights[i];

		glm::vec4 pos_h;
		pos_h[0] = l.position[0];
		pos_h[1] = l.position[1];
		pos_h[2] = l.position[2];
		pos_h[3] = 1;

		glm::vec4 pos_cam_h = pos_h * Mwc;

		glm::vec3 pos_cam(pos_cam_h[0]/pos_cam_h[3], pos_cam_h[1]/pos_cam_h[3], pos_cam_h[2]/pos_cam_h[3]);

		scene_camera.add_light(new Light(pos_cam, l.color, l.inten, l.radius));
	}

	return scene_camera;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////

ObjIntersection Scene::intersect(ray r) {

	long n_obj = objs.size();

	ObjIntersection obj_int = ObjIntersection();
	ObjIntersection intr = ObjIntersection();

	for (int i=0; i < n_obj; i++) {

		//std::cout << objs[i]->type << std::endl;
		obj_int = objs[i]->ray_intersect(r);

		if(obj_int.check) { // if the ray intersect an obj

			//std::cout << obj_int.obj->type << " distance:" << obj_int.distance << std::endl; 
			if(!intr.check) { // if previusly there's no intersection set the new intersection as the intr
				intr = obj_int;
			}
			else if(obj_int.distance < intr.distance) {	// else check the distace.
				intr = obj_int;
			}
		}
	}

	return intr;
};

glm::vec3 Scene::trace(ray r, glm::vec3 eye) {


	//std::cout << "Scene::trace" << std::endl;

	// Intersection check
	ObjIntersection obj_int;

	// Intersection between obj in camera scene and ray
	obj_int = intersect(r); // check intersection for each element in the scene

	// if intersection exsist
	if(obj_int.check) { 

		return shade(obj_int, r, eye, 0, 1);

	}

	//if there's no intersection return background color (Black)
	return glm::vec3(0,0,0);
}



glm::vec3 Scene::shade(ObjIntersection intr, ray r, glm::vec3 eye, int recursionDepth, double n1) {

	int max_reflection = 50;

	float shadow_ray_number = 100.0f;

	//std::cout << "Scene::shade" << std::endl;

	//std::cout << intr.obj->type << std::endl;

	glm::vec3 color(0, 0, 0);

	
	if(intr.obj->txt) {

		return intr.obj->get_color_txt(r, intr);
	}
	



	if(recursionDepth <= max_reflection) {

		//std::cout << "Ambient + Diff" << std::endl;		
		color += intr.obj->mat.ke + intr.obj->mat.ka * glm::vec3(255,255,255);

		long n_lights = lights.size();

		//for each light source get the shadow ray and compute the shadows
		for (int i=0; i < n_lights; i++) {

			//std::cout << "shadows + phong" << std::endl;

			glm::vec3 sh_color(0,0,0);

			if(soft_shadows) { // if soft shadows is active

				// for each point generate #shadow_ray_number random shadow rays and for each one calculate color
				for(int j=0; j<shadow_ray_number; j++) { 

					ray shadow_ray = random_shadow_ray(intr.point, *lights[i]);

					// ligt point distance
					glm::vec3 l_p = (lights[i]->position - shadow_ray.o);
				
					float dist = sqrt( pow(l_p[0],2) + pow(l_p[1],2) + pow(l_p[2],2) );

					// get nearest intersection
					ObjIntersection near_int;
					near_int = intersect(shadow_ray);

					if(near_int.check) {
						// if the shadow ray intersect a light source compute phong
						if(dist <= near_int.distance || near_int.obj->mat.type == REFR || near_int.obj->mat.type == DIEL || near_int.obj->mat.type == GLOSS) {
							sh_color += Phong_illumination(intr, r, *lights[i], eye);
						}
					}
					else {
						sh_color += Phong_illumination(intr, r, *lights[i], eye);
					}
				}

				color += sh_color/ shadow_ray_number;
			
			}
			else {

				//std::cout << "shadows + phong" << std::endl;

				glm::vec3 lightd = lights[i]->position - intr.point;

				ray shadow_ray(intr.point + glm::normalize(lightd), lightd);

				// ligt point distance
				glm::vec3 l_p = (lights[i]->position - shadow_ray.o);
			
				float dist = sqrt( pow(l_p[0],2) + pow(l_p[1],2) + pow(l_p[2],2) );

				// get nearest intersection
				ObjIntersection near_int;
				near_int = intersect(shadow_ray);

				if(near_int.check) {
					// if the shadow ray intersect a light source compute phong
					if(dist <= near_int.distance || near_int.obj->mat.type == REFR || near_int.obj->mat.type == DIEL ) {
						color += Phong_illumination(intr, r, *lights[i], eye);
					}
				}
				else {
					color += Phong_illumination(intr, r, *lights[i], eye);
				}
			}


		}

		// if the obj is defined as Specular SPEC

		//std::cout << "Tipo: " << intr.obj->mat.type << " bounce: " << recursionDepth << std::endl;

		if(intr.obj->mat.type == SPEC) {

			//std::cout << "specular" << std::endl;

			color += reflection(intr, r, recursionDepth, n1);

		}

		if(intr.obj->mat.type == REFR){
			//std::cout << "refractive" << std::endl;

			color += refraction(intr, r, recursionDepth, n1);

		}

		if(intr.obj->mat.type == DIEL) {

			/// REFLECTIVE COMPONENT

			glm::vec3 color_r;
			//std::cout << "dielectric" << std::endl;

			color_r = reflection(intr, r, recursionDepth, n1);

			/// REFRACTIVE COMPONENT

			glm::vec3 color_t;


			// compute refraction ray

			float n2, n;
			glm::vec3 normal;


			glm::vec3 I = glm::normalize(intr.point - r.o);

			float cosI = glm::dot(I,intr.norm);

			//std::cout << "cos: " << cosI << " bounce: " << recursionDepth << std::endl;

			if (cosI < 0) { 
			    // we are outside the surface, we want cos(theta) to be positive
			    n2 = intr.obj->mat.ior;
			    cosI = -cosI; 
			    normal = intr.norm; 	
			} 
			else { 
			    // we are inside the surface, cos(theta) is already positive but reverse normal direction
			    normal = intr.norm; 
			    // swap the refraction indices
			    n2 = 1; 
			} 
			n = n1/n2;

			float c2 = sqrt(1- pow(n,2) * (1 -pow(cosI, 2)));

			glm::vec3 T =I*n + (n*cosI - c2) * normal;

			// compute new intersection

			ray new_rt(intr.point + glm::normalize(T) , T);

			ObjIntersection obj_int_rt = intersect(new_rt); // check intersection for each element in the scene

			// get color from new intersection

			if(obj_int_rt.check) {
				color_t = intr.obj->mat.kt * shade(obj_int_rt, new_rt, intr.point, recursionDepth + 1, n2);
			}
			else {
				color_t = glm::vec3(0,0,0);
			}

			// RESULTING COLOR 

			float R0 = pow((n2-n1)/(n2+n1),2);

			float Rt = R0 + (1-R0)*pow((1-cosI),5);

			color = Rt*color_r + (1-Rt)*color_t;

		}

		if(intr.obj->mat.type == GLOSS) {
			
			// compute reflection
			glm::vec3 R = glm::normalize(r.d - r.o);
			glm::vec3 N = intr.norm;

			glm::vec3 ref_ray = R - (2 * glm::dot(R, N)* N );

			//ray main_r(intr.point + glm::normalize(ref_ray) , ref_ray);

			float density = pow(glm::dot(glm::normalize(ref_ray), N), intr.obj->mat.opacity);

			glm::vec3 color_g(0,0,0);

			float g_ray_number = 20.0f;

			for(int j = 0; j<g_ray_number; j++) {

				ray glossy_ray = random_glossy_ray(intr.point, glm::normalize(ref_ray), density);

				float avg = glm::dot(glossy_ray.d ,N);

				ObjIntersection new_int = intersect(glossy_ray); // check intersection for each element in the scene

				// get color from new intersection 

				if(new_int.check) {
					color_g += (intr.obj->mat.ks * shade(new_int, glossy_ray, intr.point, recursionDepth + 1, n1));
				}

			}


			color_g = color_g / g_ray_number;
			//std::cout << "color: " << color_g[0] << " " << color_g[1] << " " << color_g[2] << std::endl;
			color += color_g;

		}





		return fix_color(color);
	}

	else {
		return color;
	}
};





glm::vec3 Scene::reflection(ObjIntersection intr, ray r, int recursionDepth, double n1) {

	// compute reflection
	glm::vec3 R = glm::normalize(r.d - r.o);
	glm::vec3 N = intr.norm;

	glm::vec3 ref_ray = R - (2 * glm::dot(R, N)* N );

	ray new_r(intr.point + glm::normalize(ref_ray) , ref_ray);
	// compute new intersection

	ObjIntersection obj_int = intersect(new_r); // check intersection for each element in the scene

	// get color from new intersection 

	if(obj_int.check) {
		return intr.obj->mat.ks * shade(obj_int, new_r, intr.point, recursionDepth + 1, n1);
	}
	else {
		return glm::vec3(0,0,0);
	}

};


glm::vec3 Scene::refraction(ObjIntersection intr, ray r, int recursionDepth, double n1) {

	// compute refraction ray

	float n2, n;
	glm::vec3 normal;

	glm::vec3 I = glm::normalize(intr.point - r.o);

	float cosI = glm::dot(I,intr.norm);

	//std::cout << "cos: " << cosI << " bounce: " << recursionDepth << std::endl;

	if (cosI < 0) { 
	    // we are outside the surface, we want cos(theta) to be positive
	    n2 = intr.obj->mat.ior;
	    cosI = -cosI; 
	    normal = intr.norm; 	
	} 
	else { 
	    // we are inside the surface, cos(theta) is already positive but reverse normal direction
	    normal = intr.norm; 
	    // swap the refraction indices
	    n2 = 1; 
	} 
	n = n1/n2;

	float c2 = sqrt(1- pow(n,2) * (1 -pow(cosI, 2)));

	glm::vec3 T =I*n + (n*cosI - c2) * normal;

	// compute new intersection

	ray new_r(intr.point + glm::normalize(T) , T);

	ObjIntersection obj_int = intersect(new_r); // check intersection for each element in the scene

	// get color from new intersection

	if(obj_int.check) {
		return intr.obj->mat.kt * shade(obj_int, new_r, intr.point, recursionDepth + 1, n2);
	}
	else {
		return glm::vec3(0,0,0);
	}

}

ray Scene::random_shadow_ray(glm::vec3 s_position, Light l) {

	unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
	std::mt19937 generator (seed);
	std::uniform_real_distribution<double> uniform01(0.0, 1.0);

	double theta = 2 * M_PI * uniform01(generator);
	double phi = M_PI * uniform01(generator);

	double R = uniform01(generator) * l.radius;

	float x = pow(R,2) * sin(phi) * cos(theta);
	float y = pow(R,2) * sin(phi) * sin(theta);
	float z = R * cos(phi);

	glm::vec3 lightd = (l.position + glm::vec3(x,y,z)) - s_position;


	return ray(s_position + glm::normalize(lightd) , lightd);

}



ray Scene::random_glossy_ray(glm::vec3 s_position, glm::vec3 ref_dir, float density) {

	unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
	std::mt19937 generator (seed);
	std::uniform_real_distribution<double> uniform01(0.0, 1.0);

	double theta = 2 * M_PI * uniform01(generator);
	double phi = M_PI * uniform01(generator);

	float R = density;

	float x = -R/2 + uniform01(generator)*density; //pow(R,2) * sin(phi) * cos(theta);
	float y = -R/2 + uniform01(generator)*density;//pow(R,2) * sin(phi) * sin(theta);
	float z = -R/2 + uniform01(generator)*density;//R * cos(phi);

	glm::vec3 ray_d = ref_dir * 2.0f + glm::vec3(x,y,z);


	return ray(s_position +2.0f* glm::normalize(ray_d) , ray_d);

}