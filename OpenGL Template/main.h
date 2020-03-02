#include <string>
#include <iostream>
#include <fstream>

string ReadShaderSource(const char* filepath) {
	string content;
	ifstream fileStream(filepath, ios::in);
	string line = "";
	while (!fileStream.eof()) {
		getline(fileStream, line);
		content.append(line + "\n");
	}
	fileStream.close();
	return content;
}
