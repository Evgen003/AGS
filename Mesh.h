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
	// �������������� ����������
	GLfloat coord[3];
	// ������ �������
	GLfloat normal[3];
	// ���������� ���������� �������� ����������� �����
	GLfloat texCoord[2];
};

class Mesh
{
public:
	// �����������
	Mesh();
	// �������� ���� �� �������� obj-�����
	bool load(string filename);
	// ����� ����
	void drawOne();
private:
	vec3 getVec3(string);
	ivec3* getPolygon(string);
private:
	// ������ VAO-�������
	GLuint vao;
	// ������ VBO-������ ������
	GLuint vertexBuffer;
	// ������ VBO-������ ��������
	GLuint indexBuffer;
	// ���������� ������ � ����
	int vertexCount;
};