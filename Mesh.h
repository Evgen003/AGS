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
	// �����������
	Mesh();
	// �������� ���� �� �������� obj-�����
	bool load(string filename);
	// ����� ����
	void drawOne();
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