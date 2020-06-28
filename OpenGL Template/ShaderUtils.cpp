#include "ShaderUtils.h"

std::map<std::string, GLuint> ShaderUtils::ShaderMap;

void ShaderUtils::LoadAllShaders()
{
	ShaderMap.insert(std::make_pair("Player", Utils::createShaderProgram("vertShader.glsl", "fragShader.glsl")));
	ShaderMap.insert(std::make_pair("Asteroid", Utils::createShaderProgram("vertShader2.glsl", "fragShader2.glsl")));
	ShaderMap.insert(std::make_pair("Bullet", Utils::createShaderProgram("vertShader2.glsl", "fragShader2.glsl")));
	ShaderMap.insert(std::make_pair("Plane", Utils::createShaderProgram("vertShader2.glsl", "fragShader2.glsl")));
}
