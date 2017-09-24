#include "FileHelper.h"
#include <fstream>


FileHelper::FileHelper()
{
}


FileHelper::~FileHelper()
{
}

bool FileHelper::LoadFile(const std::string filePath, std::string& content)
{	
	std::ifstream fileStream(filePath, std::ios::in);

	if (fileStream.is_open())
	{		
		std::string line = "";
		while (!fileStream.eof())
		{
			std::getline(fileStream, line);
			content.append(line + "\n");
		}

		fileStream.close();
	}
	else
	{
		DebugLog::Print("Loader: Could not read file " + filePath, DebugLog::WARNING_LOG);
		return false;
	}

	return true;	
}
