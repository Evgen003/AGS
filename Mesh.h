#pragma once
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
	// индекс VAO-объекта
	GLuint vao;
	// индекс VBO-буфера вершин
	GLuint vertexBuffer;
	// индекс VBO-буфера индексов
	GLuint indexBuffer;
	// количество вершин в меше
	int vertexCount;
};