#pragma once
// КЛАСС ДЛЯ РАБОТЫ С ШЕЙДЕРОМ
#include <string>
#include <windows.h>
#include "stdio.h"
#include <iostream>
#include <fstream>

#include "glew-2.1.0/include/GL/glew.h"
#include "GL/freeglut.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
using namespace std;
class Shader
{
public:
	// загрузка шейдера из внешних файлов
	bool load(std::string veftexShaderFilename, std::string fragmentShaderFilename);
	// выбор шейдера в качестве текущего
	void activate();
	// отключение шейдера
	static void deactivate();
private:
	void getStrings(string);
	// создание шейдерного объекта указанного типа
	// и загрузка исходного текста шейдера из указанного файла
	GLuint createShaderObject(GLenum shaderType, std::string filename);
private:
	// шейдерная программа (шейдер)
	GLuint program;
};