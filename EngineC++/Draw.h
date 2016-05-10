#include "pch.h"
#include "Color.h"
#include "Texture.h"

static void rect(double topLeftX, double topLeftY, double bottomRightX, double bottomRightY, double z);

static void rect(double topLeftX, double topLeftY, double bottomRightX, double bottomRightY, double z, double tickness);

static void rect(double topLeftX, double topLeftY, double bottomRightX, double bottomRightY, double z, double thickness, Color innerColor);

static void rect(double topLeftX, double topLeftY, double bottomRightX, double bottomRightY, double z, Color topLeftColor, Color bottomLeftColor, Color bottomRightColor, Color topRightColor);

static void colorHRect(double topLeftX, double topLeftY, double bottomRightX, double bottomRightY, double z, Color rightColor);

static void colorVRect(double topLeftX, double topLeftY, double bottomRightX, double bottomRightY, double z, Color bottomColor);

static void rectUV(double topLeftX, double topLeftY, double bottomRightX, double bottomRightY, double z, Texture texture/*= getTexture()*/);
static void rectUV(double topLeftX, double topLeftY, double bottomRightX, double bottomRightY, double z, Texture texture/*= getTexture()*/, int animationID = 0);
static void rectUV(double topLeftX, double topLeftY, double bottomRightX, double bottomRightY, double z, double u = 0, double v = 0, double u1 = 1, double v1 = 1);

static void rectUV90(double topLeftX, double topLeftY, double bottomRightX, double bottomRightY, double z, Texture texture/*= getTexture()*/);
static void rectUV90(double topLeftX, double topLeftY, double bottomRightX, double bottomRightY, double z, Texture texture/*= getTexture()*/, int animationID = 0);
static void rectUV90(double topLeftX, double topLeftY, double bottomRightX, double bottomRightY, double z, double u = 0, double v = 0, double u1 = 1, double v1 = 1);

static void colorHRectUV(double topLeftX, double topLeftY, double bottomRightX, double bottomRightY, double z, Color rightColor, Texture texture/*= getTexture()*/);
static void colorHRectUV(double topLeftX, double topLeftY, double bottomRightX, double bottomRightY, double z, Color rightColor, Texture texture/*= getTexture()*/, int animationID = 0);
static void colorHRectUV(double topLeftX, double topLeftY, double bottomRightX, double bottomRightY, double z, Color rightColor, double u = 0, double v = 0, double u1 = 1, double v1 = 1);

static void colorHRectUV90(double topLeftX, double topLeftY, double bottomRightX, double bottomRightY, double z, Color rightColor, Texture texture/*= getTexture()*/);
static void colorHRectUV90(double topLeftX, double topLeftY, double bottomRightX, double bottomRightY, double z, Color rightColor, Texture texture/*= getTexture()*/, int animationID = 0);
static void colorHRectUV90(double topLeftX, double topLeftY, double bottomRightX, double bottomRightY, double z, Color rightColor, double u = 0, double v = 0, double u1 = 1, double v1 = 1);

static void colorVRectUV(double topLeftX, double topLeftY, double bottomRightX, double bottomRightY, double z, Color bottomColor, Texture texture/*= getTexture()*/);
static void colorVRectUV(double topLeftX, double topLeftY, double bottomRightX, double bottomRightY, double z, Color bottomColor, Texture texture/*= getTexture()*/, int animationID = 0);
static void colorVRectUV(double topLeftX, double topLeftY, double bottomRightX, double bottomRightY, double z, Color bottomColor, double u = 0, double v = 0, double u1 = 1, double v1 = 1);

static void colorVRectUV90(double topLeftX, double topLeftY, double bottomRightX, double bottomRightY, double z, Color bottomColor, Texture texture/*= getTexture()*/);
static void colorVRectUV90(double topLeftX, double topLeftY, double bottomRightX, double bottomRightY, double z, Color bottomColor, Texture texture/*= getTexture()*/, int animationID = 0);
static void colorVRectUV90(double topLeftX, double topLeftY, double bottomRightX, double bottomRightY, double z, Color bottomColor, double u = 0, double v = 0, double u1 = 1, double v1 = 1);

static void arc(double circleX, double circleY, double z, double radius, int lineCount, double thickness, double startAngle = 0, double endAngle = TWO_PI);
static void arc(double circleX, double circleY, double z, double radius, int lineCount, double thickness, Color endColor, double startAngle = 0, double endAngle = TWO_PI);

static void circle(double circleX, double circleY, double z, double radius, int lineCount, double startAngle = 0, double endAngle = TWO_PI);
static void circle(double circleX, double circleY, double z, double radius, int lineCount, Color innerColor, double startAngle = 0, double endAngle = TWO_PI);

static void circle(double circleX, double circleY, double z, double radius, double u, double v, double u1, double v1, int lineCount, Texture texture/*= getTexture()*/, double startAngle = 0, double endAngle = TWO_PI);
static void circle(double circleX, double circleY, double z, double radius, double u, double v, double u1, double v1, int lineCount, Texture texture/*= getTexture()*/, int animationID = 0, double startAngle = 0, double endAngle = TWO_PI);