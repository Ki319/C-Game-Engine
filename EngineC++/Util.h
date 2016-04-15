#include "pch.h"

static bool isCoordsInBounds(glm::vec2 coords, glm::vec4 bounds);

static float pythagoreon(float x, float y);
static float pythagoreon(float x, float y, float z);

static float distanceOfX(glm::vec2 start, glm::vec2 end);
static float distanceOfX(glm::vec3 start, glm::vec3 end);
static float distanceOfY(glm::vec2 start, glm::vec2 end);
static float distanceOfY(glm::vec3 start, glm::vec3 end);
static float distanceOfZ(glm::vec3 start, glm::vec3 end);

static float distanceInFloat(glm::vec2 start, glm::vec2 end);
static float distanceInFloat(glm::vec3 start, glm::vec3 end);

static glm::vec2 distanceInVec(glm::vec2 start, glm::vec2 end);
static glm::vec3 distanceInVec(glm::vec3 start, glm::vec3 end);

static float distanceOfXSquared(glm::vec2 start, glm::vec2 end);
static float distanceOfXSquared(glm::vec3 start, glm::vec3 end);
static float distanceOfYSquared(glm::vec2 start, glm::vec2 end);
static float distanceOfYSquared(glm::vec3 start, glm::vec3 end);
static float distanceOfZSquared(glm::vec3 start, glm::vec3 end);

static float distanceInFloatSquared(glm::vec2 start, glm::vec2 end);
static float distanceInFloatSquared(glm::vec3 start, glm::vec3 end);

static glm::vec2 distanceInVecSquared(glm::vec2 start, glm::vec2 end);
static glm::vec3 distanceInVecSquared(glm::vec3 start, glm::vec3 end);
