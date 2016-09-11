#pragma once

#include <png.h>
#include <boost\filesystem.hpp>
#include <boost\algorithm\string.hpp>
#include "Image.h"

bool read(boost::filesystem::path file, std::string &content);

bool readLines(boost::filesystem::path file, std::vector<std::string> &lines);

bool readImage(boost::filesystem::path file, Image &image);

bool writeImage(boost::filesystem::path file, Image image);