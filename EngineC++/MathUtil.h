#pragma once

#include <cmath>
#include <glm\vec2.hpp>
#include <glm\vec3.hpp>
#include <glm\vec4.hpp>

//find if a point given in a vector of two values is within a rectangle
//given by a x, y, width, and height.
bool isCoordsInBounds(glm::vec2 coords, glm::vec4 bounds);

//floating point equality function, tolerance is defaulted to .00001
bool isEqual(float valueToCompare, float valueToCompare1, float tolerance = .00001);

//recieve a random value from 0 to max - 1 in integer form
int random(int max);

//recieve a random value within the bounds of 0 <= value < max in floating point form.
float random(float max);

//recieve a random value from min to max in integer form.
int random(int min, int max);

//recieve a random value within the bounds of min <= value < max in floating point form.
float random(float min, float max);


//clmap a value (using math::min and math::max) to a minimum and a maximum.
int clamp(int value, int clampAtMin, int clampAtMax);

//clamp a value (using math::min and math::max) to a minimum and a maximum.
float clamp(float value, float clampAtMin, float clampAtMax);


//log function with a base value other than 10.
float logb(float base, float value);


//pythagoreon theorem with two values.
float pythagoreon(float x, float y);

//pythagoreon theorem with two values.
float pythagoreon(float x, float y, float z);


//distance of x components to a 2d vector.
float distanceOfX(glm::vec2 start, glm::vec2 end);

//distance of x components to a 3d vector.
float distanceOfX(glm::vec3 start, glm::vec3 end);

//distance of y components to a 2d vector.
float distanceOfY(glm::vec2 start, glm::vec2 end);

//distance of y components to a 3d vector.
float distanceOfY(glm::vec3 start, glm::vec3 end);

//distance of z components.
float distanceOfZ(glm::vec3 start, glm::vec3 end);


//returns a single float from two 2d vectors and their distances.
float distanceInFloat(glm::vec2 start, glm::vec2 end);

//returns a single float from two 3d vectors and their distances.
float distanceInFloat(glm::vec3 start, glm::vec3 end);


//returns a 2d vector from two 2d vectors and their distances.
glm::vec2 distanceInVec(glm::vec2 start, glm::vec2 end);

//returns a 3d vector from two 3d vectors and their distances.
glm::vec3 distanceInVec(glm::vec3 start, glm::vec3 end);


//distance of x components to a 2d vector.
float distanceOfXSquared(glm::vec2 start, glm::vec2 end);

//distance of x components to a 3d vector.
float distanceOfXSquared(glm::vec3 start, glm::vec3 end);


//distance of y components to a 2d vector.
float distanceOfYSquared(glm::vec2 start, glm::vec2 end);

//distance of y components to a 3d vector.
float distanceOfYSquared(glm::vec3 start, glm::vec3 end);


//distance of z components.
float distanceOfZSquared(glm::vec3 start, glm::vec3 end);


//returns a single float from two 2d vectors and their distances.
float distanceInFloatSquared(glm::vec2 start, glm::vec2 end);

//returns a single float from two 3d vectors and their distances.
float distanceInFloatSquared(glm::vec3 start, glm::vec3 end);


//returns a 2d vector from two 2d vectors and their distances.
glm::vec2 distanceInVecSquared(glm::vec2 start, glm::vec2 end);

//returns a 3d vector from two 3d vectors and their distances.
glm::vec3 distanceInVecSquared(glm::vec3 start, glm::vec3 end);


//finds the center vector from a given number of vertices.
glm::vec2 center(glm::vec2 vertices[]);

//finds the center vector from a given number of vertices.
glm::vec3 center(glm::vec3 vertices[]);


//linear growth or decay towards a destination.
float toValueLinear(float currentValue, float toValue, float speed, float delta = 1);

//returns time it will take to reach the specified value in a linear approach.
float toValueLinearTime(float currentValue, float toValue, float speed, float delta = 1);


//exponential growth or decay towards a destination. The growth or decay decays as it
//approaches the intended value.
float toValueExp(float currentValue, float toValue, float speed, float delta = 1);