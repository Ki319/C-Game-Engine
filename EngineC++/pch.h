#pragma once

#include <vector>
#include <map>
#include <string>
#include <cmath>
#include <ctime>
#include <GL\glew.h>
#include <GLFW\glfw3.h>
#include <glm\vec2.hpp>
#include <glm\vec4.hpp>
#include <glm\vec3.hpp>
#include <boost\filesystem.hpp>
#include <png.h>

#define TWO_PI 6.28318530718f
#define PI 3.14159265358f
#define HALF_PI 1.57079632679f
#define QUARTER_PI 0.785398163f

namespace fs = boost::filesystem;

template<typename Base, typename T>
inline bool instanceof(const T *ptr)
{
	return dynamic_cast<const Base*>(ptr) != nullptr;
}