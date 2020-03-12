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
    std::string readShaderFile(const char*);
    GLuint prepareShader(int, const char*);
    int finalizeShaderProgram(GLuint);
    GLuint createShaderProgram(const char* vp, const char* fp);
    GLuint createShaderProgram(const char* vp, const char* gp, const char* fp);
    GLuint createShaderProgram(const char* vp, const char* tCS, const char* tES, const char* fp);
    GLuint createShaderProgram(const char* vp, const char* tCS, const char* tES, char* gp, const char* fp);
}