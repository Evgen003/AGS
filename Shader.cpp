#include "Shader.h"
unsigned int Shader::currentProgram = 0;
bool Shader::load(std::string veftexShaderFilename, std::string fragmentShaderFilename) {
	program = glCreateProgram();
	glAttachShader(program, createShaderObject(GL_VERTEX_SHADER, veftexShaderFilename));
	glAttachShader(program, createShaderObject(GL_FRAGMENT_SHADER, fragmentShaderFilename));
	glLinkProgram(program);
	return true;
}
// выбор шейдера в качестве текущего
void Shader::activate() {
	if (currentProgram != program) {
		glUseProgram(program);
		currentProgram = program;
	}
}
// отключение шейдера
void Shader::deactivate() {
	glUseProgram(0);
	currentProgram = 0;
}
// установка uniform-переменных
void Shader::setUniform(std::string name, int value) {

}
void Shader::setUniform(std::string name, float value) {

}
void Shader::setUniform(std::string name, glm::vec2& value) {
	GLint location = getUniformLocation(name);
	glUniform2f(location, value.x, value.y);
}
void Shader::setUniform(std::string name, glm::vec4& value) {
	GLint location = getUniformLocation(name);
	glUniform4f(location, value[0], value[1], value[2], value[3]);
}
void Shader::setUniform(std::string name, glm::mat4& value) {

}

// создание шейдерного объекта указанного типа
	// и загрузка исходного текста шейдера из указанного файла
GLuint Shader::createShaderObject(GLenum shaderType, std::string filename) {
	const int max_buffer_size = 1024 * 10;
	char buffer[max_buffer_size];

	ifstream file(filename);
	if (!file.is_open()) {
		cout << "Not found" << filename << endl;
		return -1;
	}
	else {
		cout << filename << " open success\n";
	}
	
	file.getline(buffer, max_buffer_size, 0);
	GLint shader = glCreateShader(shaderType);
	if (shader == 0) {
		cout << "Can't create shader\n";
		return -1;
	}
	const char* source_pointer[] = { buffer };
	glShaderSource(shader, 1, source_pointer, 0);
	//cout << buffer;
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
// получение индекса (location) uniform-переменной
GLuint Shader::getUniformLocation(std::string name) {
	GLuint a;
	if (uniforms.count(name) == 0) {
		a = glGetUniformLocation(program, name.c_str());
		uniforms[name] = a;
		return a;
	}
	return uniforms[name];
}
