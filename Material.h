#pragma once
#include "glew-2.1.0/include/GL/glew.h"
#include "GL/freeglut.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <string>
#include <fstream>
#include <iostream>
#include "rapidjson/document.h"

using namespace std;
using namespace glm;
using namespace rapidjson;

// КЛАСС ДЛЯ РАБОТЫ С МАТЕРИАЛОМ
class Material
{
public:
	// конструктор по умолчанию
	Material();
	// загрузка параметров материала из json-файла
	bool loadFromJson(std::string filename);
	// получение различных параметров материала
	glm::vec4& getAmbient();
	glm::vec4& getDiffuse();
	glm::vec4& getSpecular();
	float getShininess();
private:
	// фоновая составляющая
	glm::vec4 ambient;
	// диффузная составляющая
	glm::vec4 diffuse;
	// зеркальная составляющая
	glm::vec4 specular;
	// степень отполированности
	GLfloat shininess;
};