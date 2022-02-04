#pragma once
#include <string>
#include <Windows.h>
using namespace std;
class Debug
{
public:
	static void LogVal(int value);
	static void LogVal(float value);
	static void LogString(string str);
	static void LogString(char* str);
};

