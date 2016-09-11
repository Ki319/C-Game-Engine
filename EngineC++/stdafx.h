#pragma once

#include <vector>
#include <map>
#include <cmath>
#include <ctime>
#include <string>
#include <GL\glew.h>
#include <GLFW\glfw3.h>
#include <glm\vec2.hpp>
#include <glm\vec3.hpp>
#include <glm\vec4.hpp>

#include "IOUtil.h"
#include "MathUtil.h"
#include "Image.h"
#include "Settings.h"
#include "Color.h"

#ifdef _DEBUG
#define doDebug handleDebug();
#ifndef _LOGGER_HPP_
#define _LOGGER_HPP_
#include <iostream>
#include <sstream>

enum loglevel
{
	ERROR, WARNING, INFO, DEBUG, DEBUG1, DEBUG2, DEBUG3, DEBUG4
};

class Logger
{
public:
	Logger(loglevel _logLevel = ERROR)
	{
		_buffer << _logLevel << " :" << std::string(_logLevel > DEBUG ? (_logLevel - DEBUG) * 4 : 1, ' ');
	}

	template <typename T>
	Logger &operator<<(T const & value)
	{
		_buffer << value;
		return *this;
	}

	~Logger()
	{
		_buffer << std::endl;
		std::cerr << _buffer.str();
	}
private:
	std::ostringstream _buffer;
};

extern loglevel LogLevel;

#define log(level) \
if (level > LogLevel) ; \
else Logger(level);

#endif
#else
#define doDebug ;
#endif

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