#pragma once
#include <GL\glew.h>
#include <iostream>
#include <string>
#include <fstream>

namespace Utils
{
    void printShaderLog(GLuint);
    void printProgramLog(int);
    bool checkOpenGLError();
    std::string readShaderSource(const char*);
}