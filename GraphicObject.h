#pragma once
#include "glew-2.1.0/include/GL/glew.h"
#include "GL/freeglut.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

using namespace glm;
using namespace std;

// КЛАСС ДЛЯ РАБОТЫ С ГРАФИЧЕСКИМ ОБЪЕКТОМ
class GraphicObject
{
public:
	// конструктор по умолчанию
	GraphicObject();
	// установить цвет объекта
	void setColor(glm::vec4& color);
	// установить позицию объекта
	void setPosition(glm::vec3& position);
	// установить угол поворота в градусах относительно оси OY по часовой стрелке
	void setAngle(float degree);
	// получить различные параметры
	glm::vec4& getColor();
	glm::mat4& getModelMatrix();
private:
	// цвет объекта
	glm::vec4 color;
	// матрица модели (задает позицию и ориентацию)
	glm::mat4 modelMatrix;
};
