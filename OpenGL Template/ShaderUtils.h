#pragma once

#include "Utils.h"

#include <map>
#include <string>

#include <GL/glew.h>

class ShaderUtils
{
public:
	static std::map<std::string, GLuint> ShaderMap;
	static void LoadAllShaders();
};

