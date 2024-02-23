#include "Data.h"

LARGE_INTEGER frequency;        // ������� �������� ������������������
LARGE_INTEGER current_time;     // ������� �������� �������� ������������������
LARGE_INTEGER previous_time;    // �������� �������� ������������������ �� ���������� �����
double elapsed_time;            // �����, ����������� �� ��������� �����
double fps;                     // ���������� ������ � �������
char window_title[256];         // ��������� ����
unsigned int timer = 0;

Camera camera;
// ������������ ������ (���� ������ ����)
Shader shader;
// ������ ����������� �������� ��� ������ �� �����
vector <GraphicObject>graphicObjects;
// ������� ��� ������������� ���� ����� ������ (������, ������� � �.�.)
void initData() {
	float ang = 0;
	for (int i = 0; i < 9; i++) {
		vec4 color = vec4(1, 0, 0, 1);
		GraphicObject obj;
		obj.setColor(color);
		vec3 pos = vec3((i % 3) * 2, 0, ((int)i / 3) * 2);
		obj.setPosition(pos);
		obj.setAngle(ang);
		ang += 10;
		graphicObjects.push_back(obj);
	}
}
// ������� ��� ������ �������� � ������� ������� ������� (�� -0.5 �� +0.5)
void drawBox() {
	// ���������� ��� ������ ������� (�������������� �� ���� �������������)
	static GLuint VAO_Index = 0;	// ������ VAO-������
	static GLuint VBO_Index = 0;	// ������ VBO-������
	static int VertexCount = 0;		// ���������� ������
	static bool init = true;

	if (init) {
		// �������� � ���������� VBO
		glGenBuffers(1, &VBO_Index);
		glBindBuffer(GL_ARRAY_BUFFER, VBO_Index);
		GLfloat Verteces[] = {
			// �������� ����� (��� ������������)
			-0.5, +0.5, +0.5, -0.5, -0.5, +0.5, +0.5, +0.5, +0.5,
			+0.5, +0.5, +0.5, -0.5, -0.5, +0.5, +0.5, -0.5, +0.5,
			// ������ ����� (��� ������������)
			+0.5, +0.5,	-0.5, +0.5, -0.5, -0.5, -0.5, +0.5, -0.5,
			-0.5, +0.5,	-0.5, +0.5, -0.5, -0.5, -0.5, -0.5, -0.5,
			// ������ ����� (��� ������������) 
			+0.5, -0.5,	+0.5, +0.5, -0.5, -0.5, +0.5, +0.5, +0.5,
			+0.5, +0.5,	+0.5, +0.5, -0.5, -0.5, +0.5, +0.5, -0.5,
			// ����� ����� (��� ������������)
			-0.5, +0.5,	+0.5, -0.5, +0.5, -0.5, -0.5, -0.5, +0.5,
			-0.5, -0.5,	+0.5, -0.5, +0.5, -0.5, -0.5, -0.5, -0.5,
			// ������� ����� (��� ������������)
			-0.5, +0.5, -0.5, -0.5, +0.5, +0.5, +0.5, +0.5, -0.5,
			+0.5, +0.5, -0.5, -0.5, +0.5, +0.5, +0.5, +0.5, +0.5,
			// ������ ����� (��� ������������)
			-0.5, -0.5, +0.5, -0.5, -0.5, -0.5, +0.5, -0.5, +0.5,
			+0.5, -0.5, +0.5, -0.5, -0.5, -0.5, +0.5, -0.5, -0.5
		};
		glBufferData(GL_ARRAY_BUFFER, sizeof(Verteces), Verteces, GL_STATIC_DRAW);

		// �������� VAO
		glGenVertexArrays(1, &VAO_Index);
		glBindVertexArray(VAO_Index);

		// ������������� VAO
		glBindBuffer(GL_ARRAY_BUFFER, VBO_Index);
		int location = 0;
		glVertexAttribPointer(location, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(location);

		// "�������" ������ VAO �� ������ ������, ���� �������� �� ���������
		glBindVertexArray(0);

		// �������� ���������� ������
		VertexCount = 6 * 6;
		init = false;
	}

	// ����� ������ ������ �� �����
	glBindVertexArray(VAO_Index);
	glDrawArrays(GL_TRIANGLES, 0, VertexCount);
}