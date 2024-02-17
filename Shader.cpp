#include "Shader.h"
bool Shader::load(std::string veftexShaderFilename, std::string fragmentShaderFilename) {
	program = glCreateProgram();
	glAttachShader(program, createShaderObject(GL_VERTEX_SHADER, veftexShaderFilename));
	glAttachShader(program, createShaderObject(GL_FRAGMENT_SHADER, fragmentShaderFilename));
	glLinkProgram(program);
	return true;
}
// выбор шейдера в качестве текущего
void Shader::activate() {
	glUseProgram(program);
}
// отключение шейдера
void Shader::deactivate() {
	glUseProgram(0);
}
void Shader::getStrings(string filename) {
	fstream File;
	File.open(filename);
	if (!File) {
		cout << "Error shader file\n";
	}
	else {
		cout << "Shader file '" << filename << "' open\n";
	}
	string line;
	int count = 0;
	while (!File.eof()) {
		getline(File, line);
		count++;
		cout << line << endl;
	}
	File.close();
	cout << "Num: " << count << endl;
	const GLchar** lines;
	lines = new const GLchar*[count];
	GLint* str_size = new GLint[count];
	File.open(filename);
	int i = 0;
	while (!File.eof()) {
		getline(File, line);
		int size = line.size();
		cout << size << endl;
		lines[i] = new GLchar[size];
		lines[i] = line.c_str();
		str_size[i] = line.size();
		i++;
	}

}
// создание шейдерного объекта указанного типа
	// и загрузка исходного текста шейдера из указанного файла
GLuint Shader::createShaderObject(GLenum shaderType, std::string filename) {
	const int max_buffer_size = 1024 * 10;
	char buffer[max_buffer_size];

	ifstream file(filename);
	if (!file.is_open()) {
		cout << "Not found" << endl;
		return -1;
	}
	file.getline(buffer, max_buffer_size, 0);
	GLint shader = glCreateShader(shaderType);
	if (shader == 0) {
		cout << "Can't create shader\n";
		return -1;
	}
	const char* source_pointer[] = { buffer };
	glShaderSource(shader, 1, source_pointer, 0);
	cout << buffer;
	glCompileShader(shader);
	GLint compileStatus;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &compileStatus);
	if (compileStatus == GL_FALSE) {
		GLuint count;
		glGetShaderInfoLog(shader, max_buffer_size,
			(GLsizei*)&count, buffer);

		return -1;
	}
	return shader;
}