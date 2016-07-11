#pragma once
#include "pch.h"

char *convertToBytes(std::vector<char> byteList);

std::string readCompressedFile(fs::path file);

void createFileSafely(fs::path file);

char *readStreamFully();