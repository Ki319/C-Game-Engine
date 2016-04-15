#include "Util.h"

bool isCoordsInBounds(glm::vec2 coords, glm::vec4 bounds)
{
	return bounds.x <= coords.x && bounds.y <= coords.y && bounds.x + bounds.z >= coords.x && bounds.y + bounds.w >= coords.y;
}

float pythagoreon(float x, float y)
{
	return sqrt(x * x + y * y);
}

float pythagoreon(float x, float y, float z)
{
	return sqrt(x * x + y * y + z * z);
}

float distanceOfX(glm::vec2 start, glm::vec2 end)
{
	return abs(start.x - end.x);
}

float distanceOfX(glm::vec3 start, glm::vec3 end)
{
	return abs(start.x - end.x);
}

float distanceOfY(glm::vec2 start, glm::vec2 end)
{
	return abs(start.y - end.y);
}

float distanceOfY(glm::vec3 start, glm::vec3 end)
{
	return abs(start.y - end.y);
}

float distanceOfZ(glm::vec3 start, glm::vec3 end)
{
	return abs(start.z - end.z);
}

float distanceInFloat(glm::vec2 start, glm::vec2 end)
{
	return pythagoreon(start.x - end.x, start.y - start.y);
}

float distanceInFloat(glm::vec3 start, glm::vec3 end)
{
	return pythagoreon(start.x - end.x, start.y - end.y, start.z - end.z);
}

glm::vec2 distanceInVec(glm::vec2 start, glm::vec2 end)
{
	return glm::vec2(distanceOfX(start, end), distanceOfY(start, end));
}

glm::vec3 distanceInVec(glm::vec3 start, glm::vec3 end)
{
	return glm::vec3(distanceOfX(start, end), distanceOfY(start, end), distanceOfZ(start, end));
}

float distanceOfXSquared(glm::vec2 start, glm::vec2 end)
{
	return abs(start.x - end.x);
}

float distanceOfXSquared(glm::vec3 start, glm::vec3 end)
{
	return abs(start.x - end.x);
}

float distanceOfYSquared(glm::vec2 start, glm::vec2 end)
{
	return abs(start.y - end.y);
}

float distanceOfYSquared(glm::vec3 start, glm::vec3 end)
{
	return abs(start.y - end.y);
}

float distanceOfZSquared(glm::vec3 start, glm::vec3 end)
{
	return abs(start.z - end.z);
}

float distanceInFloatSquared(glm::vec2 start, glm::vec2 end)
{
	float x = start.x - end.x;
	float y = start.y - end.y;
	return x * x + y * y;
}

float distanceInFloatSquared(glm::vec3 start, glm::vec3 end)
{
	float x = start.x - end.x;
	float y = start.y - end.y;
	float z = start.z - end.z;
	return x * x + y * y + z * z;
}

glm::vec2 distanceInVecSquared(glm::vec2 start, glm::vec2 end)
{
	return glm::vec2(distanceOfXSquared(start, end), distanceOfYSquared(start, end));
}

glm::vec3 distanceInVecSquared(glm::vec3 start, glm::vec3 end)
{
	return glm::vec3(distanceOfXSquared(start, end), distanceOfYSquared(start, end), distanceOfZSquared(start, end));
}