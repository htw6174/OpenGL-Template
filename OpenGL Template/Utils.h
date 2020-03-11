#pragma once
#include <GL\glew.h>
#include <iostream>

namespace Utils
{
    void printShaderLog(GLuint);
    void printProgramLog(int);
    bool checkOpenGLError();
}