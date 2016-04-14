#include "pch.h"
#include "Color.h"
#include "Texture.h"

static void rect(double x, double y, double x1, double y1, double z);

static void rect(double x, double y, double x1, double y1, double z, double tickness);

static void rect(double x, double y, double x1, double y1, double z, double thickness, Color innerColor);

static void rect(double x, double y, double x1, double y1, double z, Color color0, Color color1, Color color2, Color color3);

static void colorHRect(double x, double y, double x1, double y1, double z, Color shiftToColor);
static void colorHRect(double x, double y, double x1, double y1, double z, double r, double g, double b, double a);

static void colorVRect(double x, double y, double x1, double y1, double z, Color shiftToColor);
static void colorVRect(double x, double y, double x1, double y1, double z, double r, double g, double b, double a);

static void rectUV(double x, double y, double x1, double y1, double z, Texture texture/*= getTexture()*/);
static void rectUV(double x, double y, double x1, double y1, double z, Texture texture/*= getTexture()*/, int animationID = 0);
static void rectUV(double x, double y, double x1, double y1, double z, double u = 0, double v = 0, double u1 = 1, double v1 = 1);

static void rectUV90(double x, double y, double x1, double y1, double z, Texture texture/*= getTexture()*/);
static void rectUV90(double x, double y, double x1, double y1, double z, Texture texture/*= getTexture()*/, int animationID = 0);
static void rectUV90(double x, double y, double x1, double y1, double z, double u = 0, double v = 0, double u1 = 1, double v1 = 1);

static void colorHRectUV(double x, double y, double x1, double y1, double z, Color shiftToColor, Texture texture/*= getTexture()*/);
static void colorHRectUV(double x, double y, double x1, double y1, double z, Color shiftToColor, Texture texture/*= getTexture()*/, int animationID = 0);
static void colorHRectUV(double x, double y, double x1, double y1, double z, Color shiftToColor, double u = 0, double v = 0, double u1 = 1, double v1 = 1);

static void colorHRectUV90(double x, double y, double x1, double y1, double z, Color shiftToColor, Texture texture/*= getTexture()*/);
static void colorHRectUV90(double x, double y, double x1, double y1, double z, Color shiftToColor, Texture texture/*= getTexture()*/, int animationID = 0);
static void colorHRectUV90(double x, double y, double x1, double y1, double z, Color shiftToColor, double u = 0, double v = 0, double u1 = 1, double v1 = 1);

static void colorVRectUV(double x, double y, double x1, double y1, double z, Color shiftToColor, Texture texture/*= getTexture()*/);
static void colorVRectUV(double x, double y, double x1, double y1, double z, Color shiftToColor, Texture texture/*= getTexture()*/, int animationID = 0);
static void colorVRectUV(double x, double y, double x1, double y1, double z, Color shiftToColor, double u = 0, double v = 0, double u1 = 1, double v1 = 1);

static void colorVRectUV90(double x, double y, double x1, double y1, double z, Color shiftToColor, Texture texture/*= getTexture()*/);
static void colorVRectUV90(double x, double y, double x1, double y1, double z, Color shiftToColor, Texture texture/*= getTexture()*/, int animationID = 0);
static void colorVRectUV90(double x, double y, double x1, double y1, double z, Color shiftToColor, double u = 0, double v = 0, double u1 = 1, double v1 = 1);

static void arc(double circleX, double circleY, double z, double radius, int lineCount, double thickness, double startAngle = 0, double endAngle = TWO_PI);
static void arc(double circleX, double circleY, double z, double radius, int lineCount, double thickness, Color endColor, double startAngle = 0, double endAngle = TWO_PI);

static void circle(double circleX, double circleY, double z, double radius, int lineCount, double startAngle = 0, double endAngle = TWO_PI);
static void circle(double circleX, double circleY, double z, double radius, int lineCount, Color innerColor, double startAngle = 0, double endAngle = TWO_PI);

static void circle(double circleX, double circleY, double z, double radius, double u, double v, double u1, double v1, int lineCount, Texture texture/*= getTexture()*/, double startAngle = 0, double endAngle = TWO_PI);
static void circle(double circleX, double circleY, double z, double radius, double u, double v, double u1, double v1, int lineCount, Texture texture/*= getTexture()*/, int animationID = 0, double startAngle = 0, double endAngle = TWO_PI);