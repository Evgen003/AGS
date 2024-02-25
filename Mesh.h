#pragma once
#include <string>
#include <windows.h>
#include "stdio.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <map>

#include "glew-2.1.0/include/GL/glew.h"
#include "GL/freeglut.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
using namespace std;
using namespace glm;

struct Vertex
{
	// геометрические координаты
	GLfloat coord[3];
	// вектор нормали
	GLfloat normal[3];
	// текстурные координаты нулевого текстурного блока
	GLfloat texCoord[2];
};

class Mesh
{
public:
	// конструктор
	Mesh();
	// загрузка меша из внешнего obj-файла
	bool load(string filename);
	// вывод меша
	void drawOne();
private:
	vec3 getVec3(string);
	ivec3* getPolygon(string);
private:
	// индекс VAO-объекта
	GLuint vao;
	// индекс VBO-буфера вершин
	GLuint vertexBuffer;
	// индекс VBO-буфера индексов
	GLuint indexBuffer;
	// количество вершин в меше
	int vertexCount;
};