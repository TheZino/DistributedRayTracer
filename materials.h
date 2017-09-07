#ifndef MATERIALS_H
#define MATERIALS_H

#include <glm/vec3.hpp>

/*
material.ke      // Emissive  reflectance
material.ka      // Ambient   reflectance
material.kd      // Diffusive reflectance
material.ks      // Specular  reflectance
material.ior		 // Refraction index
material.kt		 	 // Transparency
material.sh      // Shininess
material.opacity // Opacity
material.type
*/

enum MaterialType { DIFF, SPEC, REFR, DIEL, GLOSS };

struct material {
	glm::vec3 ke, ka, kd, ks;
	float ior, kt, sh, opacity;
	MaterialType type;
};

// Neutral material

const material material_neutral = {
	glm::vec3(0.0, 0.0, 0.0),
	glm::vec3(0.2, 0.2, 0.2),
	glm::vec3(0.454902, 0.454902, 0.454902),
	glm::vec3(0.0225, 0.0225, 0.0225),
	1,
	0,
	12.8,
	1.0,
	DIFF
};

const material light_bulb = {
	glm::vec3(1.0, 1.0, 1.0),
	glm::vec3(0.2, 0.2, 0.2),
	glm::vec3(1.0, 0.0, 0.0),
	glm::vec3(0.0225, 0.0225, 0.0225),
	1,
	0,
	12.8,
	1.0,
	DIFF
};

// Colors

const material Red = {
	glm::vec3(0.0, 0.0, 0.0),
	glm::vec3(0.0, 0.0, 0.0),
	glm::vec3(1.0, 0.0, 0.0),
	glm::vec3(0.0225, 0.0225, 0.0225),
	1,
	0,
	12.8,
	1.0,
	DIFF
};

const material Orange = {
	glm::vec3(0.0, 0.0, 0.0),
	glm::vec3(0.0, 0.0, 0.0),
	glm::vec3(0.992157, 0.513726, 0.0),
	glm::vec3(0.0225, 0.0225, 0.0225),
	1,
	0,
	12.8,
	1.0,
	DIFF
};

const material Yellow = {
	glm::vec3(0.0, 0.0, 0.0),
	glm::vec3(0.0, 0.0, 0.0),
	glm::vec3(1.0, 0.964706, 0.0),
	glm::vec3(0.0225, 0.0225, 0.0225),
	1,
	0,
	12.8,
	1.0,
	DIFF
};

const material Green = {
	glm::vec3(0.0, 0.0, 0.0),
	glm::vec3(0.0, 0.0, 0.0),
	glm::vec3(0.0, 1.0, 0.0),
	glm::vec3(0.0225, 0.0225, 0.0225),
	1,
	0,
	12.8,
	1.0,
	DIFF
};

const material Indigo = {
	glm::vec3(0.0, 0.0, 0.0),
	glm::vec3(0.0, 0.0, 0.0),
	glm::vec3(0.0980392, 0.0, 0.458824),
	glm::vec3(0.0225, 0.0225, 0.0225),
	1,
	0,
	12.8,
	1.0,
	DIFF
};
const material Blue = {
	glm::vec3(0.0, 0.0, 0.0),
	glm::vec3(0.0, 0.0, 0.0),
	glm::vec3(0.0, 0.0, 1.0),
	glm::vec3(0.0225, 0.0225, 0.0225),
	1,
	0,
	12.8,
	1.0,
	DIFF
};
const material Violet = {
	glm::vec3(0.0, 0.0, 0.0),
	glm::vec3(0.0, 0.0, 0.0),
	glm::vec3(0.635294, 0.0, 1.0),
	glm::vec3(0.0225, 0.0225, 0.0225),
	1,
	0,
	12.8,
	1.0,
	DIFF
};

const material White = {
	glm::vec3(0.0, 0.0, 0.0),
	glm::vec3(0.0, 0.0, 0.0),
	glm::vec3(0.992157, 0.992157, 0.992157),
	glm::vec3(0.0225, 0.0225, 0.0225),
	1,
	0,
	12.8,
	1.0,
	DIFF
};

const material Black = {
	glm::vec3(0.0, 0.0, 0.0),
	glm::vec3(0.0, 0.0, 0.0),
	glm::vec3(0.0, 0.0, 0.0),
	glm::vec3(0.0225, 0.0225, 0.0225),
	1,
	0,
	12.8,
	1.0,
	DIFF
};

const material medium_gray = {
	glm::vec3(0.0, 0.0, 0.0),
	glm::vec3(0.2, 0.2, 0.2),
	glm::vec3(0.454902, 0.454902, 0.454902),
	glm::vec3(0.0225, 0.0225, 0.0225),
	1,
	0,
	12.8,
	1.0,
	DIFF
};

const material light_gray = {
	glm::vec3(0.0, 0.0, 0.0),
	glm::vec3(0.0, 0.0, 0.0),
	glm::vec3(0.682353, 0.682353, 0.682353),
	glm::vec3(0.0225, 0.0225, 0.0225),
	1,
	0,
	12.8,
	1.0,
	DIFF
};




///////////////////////////////////////////////////////////////////

// GLASS

const material white_glass = {
	glm::vec3(0.0, 0.0, 0.0),
	glm::vec3(0.0, 0.0, 0.0),
	glm::vec3(0.1, 0.10, 0.10),
	glm::vec3(0.0, 0.0, 0.0),
	1.2,
	1,
	0,
	1.0,
	REFR
};

const material white_glass_diel = {
	glm::vec3(0.0, 0.0, 0.0),
	glm::vec3(0.0, 0.0, 0.0),
	glm::vec3(1.0, 1.0, 1.0),
	glm::vec3(0.8, 0.8, 0.8),
	1.2,
	1,
	12.8,
	1.0,
	DIEL
};

const material blue_glass = {
	glm::vec3(0.0, 0.0, 0.0),
	glm::vec3(1.0, 0.0, 0.0),
	glm::vec3(0.0, 0.0, 0.0),
	glm::vec3(0.0225, 0.0225, 0.0225),
	1.2,
	1,
	10000,
	1.0,
	REFR
};


// MIRROR

const material glossy_mirror = {
	glm::vec3(0.0, 0.0, 0.0),
	glm::vec3(0.0, 0.0, 0.0),
	glm::vec3(0, 0, 0),
	glm::vec3(0.8, 0.8, 0.8),
	1,
	0,
	100000,
	5,
	GLOSS
};

const material glossy_mirror_yellow = {
	glm::vec3(0.0, 0.0, 0.0),
	glm::vec3(0, 0, 0),
	glm::vec3(0.75164, 0.60648, 0.22648),
	glm::vec3(0.628281, 0.555802, 0.366065),
	1,
	0,
	100000,
	30,
	GLOSS
};


const material mirror = {
	glm::vec3(0.0, 0.0, 0.0),
	glm::vec3(0.0, 0.0, 0.0),
	glm::vec3(0, 0, 0),
	glm::vec3(0.8, 0.8, 0.8),
	1,
	0,
	12.8,
	1.0,
	SPEC
};


// GOLD
const material material_gold = {
	glm::vec3(0.0,0.0,0.0),
	glm::vec3(0.24725, 0.1995, 0.0745),
	glm::vec3(0.75164, 0.60648, 0.22648),
	glm::vec3(0.628281, 0.555802, 0.366065),
	1,
	0,
	51.2,
	1.0,
	DIFF
};

// EMERALD
const material material_emerald = {
	glm::vec3(0.0,0.0,0.0),
	glm::vec3(0.0215, 0.1745, 0.0215),
	glm::vec3(0.07568, 0.61424, 0.07568),
	glm::vec3(0.633, 0.727811, 0.633),
	1,
	0,
	76.8,
	0.55,
	DIFF
};

// CHROME
const material material_chrome = {
	glm::vec3(0.0,0.0,0.0),
	glm::vec3(0.25, 0.25, 0.25),
	glm::vec3(0.4, 0.4, 0.4),
	glm::vec3(0.774597, 0.774597, 0.774597),
	1,
	0,
	76.8,
	1.0,
	DIFF
};

// RED PLASTIC
const material material_redplastic = {
	glm::vec3(0.0,0.0,0.0),
	glm::vec3(0.0,0.0,0.0),
	glm::vec3(0.5,0.0,0.0),
	glm::vec3(0.7,0.6,0.6),
	1,
	0,
	32.0,
	1.0,
	DIFF
};

// BLUE PLASTIC
const material material_blueplastic = {
	glm::vec3(0.0,0.0,0.0),
	glm::vec3(0.0,0.0,0.0),
	glm::vec3(0.0,0.0,0.5),
	glm::vec3(0.7,0.6,0.6),
	1,
	0,
	32.0,
	1.0,
	DIFF
};

// GREEN PLASTIC
const material material_greenplastic = {
	glm::vec3(0.0,0.0,0.0),
	glm::vec3(0.0,0.0,0.0),
	glm::vec3(0.0,0.5,0.0),
	glm::vec3(0.7,0.6,0.6),
	1,
	0,
	32.0,
	1.0,
	DIFF
};

// WHITE PLASTIC
const material material_whiteplastic = {
	glm::vec3(0.0,0.0,0.0),
	glm::vec3(0.0,0.0,0.0),
	glm::vec3(0.992157, 0.992157, 0.992157),
	glm::vec3(0.7,0.6,0.6),
	1,
	0,
	32.0,
	1.0,
	DIFF
};

// RED RUBBER
const material material_redrubber = {
	glm::vec3(0.0,0.0,0.0),
	glm::vec3(0.05,0.0,0.0),
	glm::vec3(0.5,0.4,0.4),
	glm::vec3(0.7,0.04,0.04),
	1,
	0,
	10.0,
	1.0,
	DIFF
};

#endif
