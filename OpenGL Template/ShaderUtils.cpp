#include "ShaderUtils.h"

std::map<std::string, GLuint> ShaderUtils::ShaderMap;

void ShaderUtils::LoadAllShaders()
{
	ShaderMap.insert(std::make_pair("Player", Utils::createShaderProgram("default.vert", "player.frag")));
	ShaderMap.insert(std::make_pair("Asteroid", Utils::createShaderProgram("asteroid.vert", "asteroid.frag")));
	ShaderMap.insert(std::make_pair("Bullet", Utils::createShaderProgram("default.vert", "bullet.frag")));
	ShaderMap.insert(std::make_pair("Plane", Utils::createShaderProgram("default.vert", "default.frag")));
}
