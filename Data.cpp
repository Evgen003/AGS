#include "Data.h"

// ������������ ������������ ����
using namespace glm;
using namespace std;

LARGE_INTEGER frequency;        // ������� �������� ������������������
LARGE_INTEGER current_time;     // ������� �������� �������� ������������������
LARGE_INTEGER previous_time;    // �������� �������� ������������������ �� ���������� �����
double elapsed_time;            // �����, ����������� �� ��������� �����
double fps;                     // ���������� ������ � �������
char window_title[256];         // ��������� ����
unsigned int timer = 0;
Shader shader;
// ������� ��� ������������� ���� ����� ������ (������, ������� � �.�.)
void initData() {

}
// ������� ��� ������ �������� � ������� ������� ������� (�� -0.5 �� +0.5)
void drawObject()
{
	// ���������� ��� ������ ������� (�������������� �� ���� �������������)
	static bool init = true;
	static GLuint VAO_Index = 0;		// ������ VAO-������
	static GLuint VBO_Index = 0;		// ������ VBO-������
	static int VertexCount = 0;			// ���������� ������

	// ��� ������ ������ �������������� VBO � VAO
	if (init) {
		init = false;
		// �������� � ���������� VBO
		glGenBuffers(1, &VBO_Index);
		glBindBuffer(GL_ARRAY_BUFFER, VBO_Index);
		GLfloat	Verteces[] = {

			0.08, 0.07,
			0.15, 0.27,
			0.17, 0.27,
			0.23, 0.07,
			0.21, 0.07,
			0.19, 0.14,
			0.125, 0.14,
			0.10, 0.07
		};
		glBufferData(GL_ARRAY_BUFFER, sizeof(Verteces), Verteces, GL_STATIC_DRAW);

		// �������� VAO
		glGenVertexArrays(1, &VAO_Index);
		glBindVertexArray(VAO_Index);
		// ���������� VAO
		glBindBuffer(GL_ARRAY_BUFFER, VBO_Index);
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(0);
		// "�������" ������ VAO, ���� �������� �� ���������
		glBindVertexArray(0);

		// �������� ���������� ������
		VertexCount = 3;
	}

	// ������� �������������
	glBindVertexArray(VAO_Index);
	glDrawArrays(GL_TRIANGLES, 0, 8);
}