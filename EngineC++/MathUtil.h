#include "pch.h"

static bool isCoordsInBounds(glm::vec2 coords, glm::vec4 bounds);

static bool isEqual(float valueToCompare, float valueToCompare1, float tolerance = .00001);

static int random(int max);
static float random(float max);
static int random(int min, int max);
static float random(float min, float max);

static int clamp(int value, int clampAtMin, int clampAtMax);
static float clamp(float value, float clampAtMin, float clampAtMax);

static bool isNegative(int value);
static bool isNegative(float value);

static float log(float base, float value);

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

static glm::vec2 center(glm::vec2 vertices, ...);
static glm::vec3 center(glm::vec3 vertices, ...);

static float toValueLinear(float currentValue, float toValue, float speed);
static float toValueLinear(float currentValue, float toValue, float speed, float delta);
static float toValueExponential(float currentValue, float toValue, float speed);
static float toValueExponential(float currentValue, float toValue, float speed, float delta);

static float toValueDistanceLinear(float currentValue, float toValue, float speed);
static float toValueDistanceLinear(float currentValue, float toValue, float speed, float delta);
static float toValueDistanceExponential(float currentValue, float toValue, float speed);
static float toValueDistanceExponential(float currentValue, float toValue, float speed, float delta);

static int locationInList(int currentLocation, int sizeOfList);
static bool areLocationsEqual(int location1, int location2, int sizeOfList);
