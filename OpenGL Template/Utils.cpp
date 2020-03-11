#include <GL\glew.h>
#include <iostream>
	

namespace Utils
{
	void printShaderLog(GLuint shader)
	{
		int len = 0;
		int chWritten = 0;
		char* log;
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &len);

		if (len > 0)
		{
			log = (char*)malloc(len);
			glGetShaderInfoLog(shader, len, &chWritten, log);
			std::cout << "Shader Info log: " << log << std::endl;
			free(log);
		}
	}

	void printProgramLog(int prog) 
	{
		int len = 0;
		int chWritten = 0;
		char* log;
		glGetProgramiv(prog, GL_INFO_LOG_LENGTH, &len);
		if (len > 0)
		{
			log = (char*)malloc(len);
			glGetProgramInfoLog(prog, len, &chWritten, log);
			std::cout << "Program Info Log:" << log << std::endl;
			free(log);
		}
	}

	bool checkOpenGLError() 
	{
		bool foundError = false;
		int glErr = glGetError();
		while (glErr != GL_NO_ERROR) 
		{
			std::cout << "glError: " << glErr << std::endl;
			foundError = true;
			glErr = glGetError();
		}
		return foundError;
	}
}
