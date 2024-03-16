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
	void setColor(vec4 color);
	// установить позицию объекта
	void setPosition(vec3 position);
	// установить угол поворота в градусах относительно оси OY по часовой стрелке
	void setAngle(float degree);
	// установить идентификатор используемого меша
	void setMeshId(int id);
	// установить идентификатор используемой текстуры
	void setTextureId(int id);
	// установить идентификатор используемого материала
	void setMaterialId(int id);
	// получить различные параметры
	vec4& getColor();
	mat4& getModelMatrix();
	int getMeshId();
	int getTextureId();
	int getMaterialId();
private:
	// идентификатор используемого меша
	int meshId;
	// идентификатор используемой текстуры
	int textureId;
	// идентификатор используемого материала
	int materialId;
	// цвет объекта
	vec4 color;
	// матрица модели (задает позицию и ориентацию)
	mat4 modelMatrix;
};
