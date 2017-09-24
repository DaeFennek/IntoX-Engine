#pragma once

#include "stdfax.h"

class FileHelper
{
public:
	FileHelper();
	~FileHelper();

	static bool LoadFile(const std::string filePath, std::string& content);

};

