#pragma once

#include "pch.h"

bool readImage(std::string file,  int &width, int &height, bool &hasAlpha, GLubyte **data);

bool writeImage(std::string file, int width, int height, GLubyte **data);