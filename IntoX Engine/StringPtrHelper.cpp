#include "StringPtrHelper.h"


char* ConnectStr(const char* str1, const char* str2)
{
	size_t connectedStrSize = strlen(str1) + 1 + strlen(str2) + 1;
	char* connectedString = (char*) malloc(connectedStrSize); // alloc on heap
	strcpy_s(connectedString, strlen(str1) + 1, str1);
	strcat_s(connectedString, strlen(str2) + 1, str2);	
	return connectedString;
}