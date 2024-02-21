#pragma once
#include "glew-2.1.0/include/GL/glew.h"
#include "GL/freeglut.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

using namespace glm;
using namespace std;

// ����� ��� ������ � ����������� ��������
class GraphicObject
{
public:
	// ����������� �� ���������
	GraphicObject();
	// ���������� ���� �������
	void setColor(glm::vec4& color);
	// ���������� ������� �������
	void setPosition(glm::vec3& position);
	// ���������� ���� �������� � �������� ������������ ��� OY �� ������� �������
	void setAngle(float degree);
	// �������� ��������� ���������
	glm::vec4& getColor();
	glm::mat4& getModelMatrix();
private:
	// ���� �������
	glm::vec4 color;
	// ������� ������ (������ ������� � ����������)
	glm::mat4 modelMatrix;
};
