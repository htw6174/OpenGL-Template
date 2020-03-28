#include <GL\glew.h>
#include <iostream>
#include <string>
#include <fstream>


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

	std::string readShaderFile(const char* filePath)
	{
		std::string content;
		std::ifstream fileStream(filePath, std::ios::in);
		std::string line = "";
		while (!fileStream.eof())
		{
			std::getline(fileStream, line);
			content.append(line + "\n");
		}
		fileStream.close();
		return content;
	}

	GLuint prepareShader(int shaderTYPE, const char* shaderPath)
	{
		GLint shaderCompiled;
		std::string shaderStr = readShaderFile(shaderPath);
		const char* shaderSrc = shaderStr.c_str();
		GLuint shaderRef = glCreateShader(shaderTYPE);
		glShaderSource(shaderRef, 1, &shaderSrc, NULL);
		glCompileShader(shaderRef);
		checkOpenGLError();
		glGetShaderiv(shaderRef, GL_COMPILE_STATUS, &shaderCompiled);
		if (shaderCompiled != 1)
		{
			if (shaderTYPE == 35633) std::cout << "Vertex ";
			if (shaderTYPE == 36488) std::cout << "Tess Control ";
			if (shaderTYPE == 36487) std::cout << "Tess Eval ";
			if (shaderTYPE == 36313) std::cout << "Geometry ";
			if (shaderTYPE == 35632) std::cout << "Fragment ";
			std::cout << "shader compilation error." << std::endl;
			printShaderLog(shaderRef);
		}
		return shaderRef;
	}
	int finalizeShaderProgram(GLuint sprogram)
	{
		GLint linked;
		glLinkProgram(sprogram);
		checkOpenGLError();
		glGetProgramiv(sprogram, GL_LINK_STATUS, &linked);
		if (linked != 1)
		{
			std::cout << "linking failed" << std::endl;
			printProgramLog(sprogram);
		}
		return sprogram;
	}

	GLuint createShaderProgram(const char* vp, const char* fp) {
		GLuint vShader = prepareShader(GL_VERTEX_SHADER, vp);
		GLuint fShader = prepareShader(GL_FRAGMENT_SHADER, fp);
		GLuint vfprogram = glCreateProgram();
		glAttachShader(vfprogram, vShader);
		glAttachShader(vfprogram, fShader);
		finalizeShaderProgram(vfprogram);
		return vfprogram;
	}

	GLuint createShaderProgram(const char* vp, const char* gp, const char* fp) {
		GLuint vShader = prepareShader(GL_VERTEX_SHADER, vp);
		GLuint gShader = prepareShader(GL_GEOMETRY_SHADER, gp);
		GLuint fShader = prepareShader(GL_FRAGMENT_SHADER, fp);
		GLuint vgfprogram = glCreateProgram();
		glAttachShader(vgfprogram, vShader);
		glAttachShader(vgfprogram, gShader);
		glAttachShader(vgfprogram, fShader);
		finalizeShaderProgram(vgfprogram);
		return vgfprogram;
	}

	GLuint createShaderProgram(const char* vp, const char* tCS, const char* tES, const char* fp) {
		GLuint vShader = prepareShader(GL_VERTEX_SHADER, vp);
		GLuint tcShader = prepareShader(GL_TESS_CONTROL_SHADER, tCS);
		GLuint teShader = prepareShader(GL_TESS_EVALUATION_SHADER, tES);
		GLuint fShader = prepareShader(GL_FRAGMENT_SHADER, fp);
		GLuint vtfprogram = glCreateProgram();
		glAttachShader(vtfprogram, vShader);
		glAttachShader(vtfprogram, tcShader);
		glAttachShader(vtfprogram, teShader);
		glAttachShader(vtfprogram, fShader);
		finalizeShaderProgram(vtfprogram);
		return vtfprogram;
	}

	GLuint createShaderProgram(const char* vp, const char* tCS, const char* tES, char* gp, const char* fp) {
		GLuint vShader = prepareShader(GL_VERTEX_SHADER, vp);
		GLuint tcShader = prepareShader(GL_TESS_CONTROL_SHADER, tCS);
		GLuint teShader = prepareShader(GL_TESS_EVALUATION_SHADER, tES);
		GLuint gShader = prepareShader(GL_GEOMETRY_SHADER, gp);
		GLuint fShader = prepareShader(GL_FRAGMENT_SHADER, fp);
		GLuint vtgfprogram = glCreateProgram();
		glAttachShader(vtgfprogram, vShader);
		glAttachShader(vtgfprogram, tcShader);
		glAttachShader(vtgfprogram, teShader);
		glAttachShader(vtgfprogram, gShader);
		glAttachShader(vtgfprogram, fShader);
		finalizeShaderProgram(vtgfprogram);
		return vtgfprogram;
	}

}
