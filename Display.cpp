#include "Display.h"


void display(void)
{
	// ������� ������ �����
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	// ��������� ����� ������� (�� ������ ������)
	glEnable(GL_DEPTH_TEST);
	// ����� ��������� � ���� ����� � ���������� ��������� ������
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);

	// ��������� ������� ��������
	mat4 projectionMatrix;
	projectionMatrix = perspective(radians(35.0), 800.0 / 600.0, 1.0, 100.0);
	// ������������� ������� ������
	mat4 viewMatrix;
	// ������� ������ - (0, 3, 5)
	vec3 eye = vec3(0.0, 3.0, 5.0);
	// �����, � ������� ���������� ������ - (0, 0, 0);
	vec3 center = vec3(0, 0, 0);
	// ��������� ������ "�����" (0, 1, 0)
	vec3 up = vec3(0, 1, 0);
	// ������� ������
	viewMatrix = lookAt(eye, center, up);
	// ������� ������
	mat4 modelMatrix;
	// ������ ������������� � ����� (1,0,0) ��� ��������
	modelMatrix = mat4(
		vec4(1, 0, 0, 0), // 1-�� �������: ����������� ��� X
		vec4(0, 1, 0, 0), // 2-�� �������: ����������� ��� Y
		vec4(0, 0, 1, 0), // 3-�� �������: ����������� ��� Z
		vec4(1, 0, 0, 1)); // 4-�� �������: ������� ������� (������ ���������)
	   // ��������� ������� ���������� ������
	mat4 modelViewMatrix = viewMatrix * modelMatrix;
	// ��������� �������
	shader.activate();
	// ������������� uniform-���������� ��� ������ �������� � ���������� ������
	shader.setUniform("projectionMatrix", projectionMatrix);
	shader.setUniform("modelViewMatrix", modelViewMatrix);
	// ������������� �������� uniform-���������� ��� ����� ������� ���������
	vec4 color = vec4(0, 0, 1, 1);
	shader.setUniform("color", color);
	// ������� ������������� 
	drawObject();
	// ����� ��������� � ������� �������
	glutSwapBuffers();
	printFPS();
}
void printFPS() {
	// ������������� ������� �������� ������������������
	QueryPerformanceFrequency(&frequency);
	// ��������� �������� �������� �������� ������������������
	QueryPerformanceCounter(&current_time);
	// ���������� �������, ������������ �� ��������� �����
	elapsed_time = (double)(current_time.QuadPart - previous_time.QuadPart) / frequency.QuadPart;
	// ���������� ���������� ������ � �������
	fps = 1.0 / elapsed_time;
	// ���������� �������� �������� �������� ������������������ ��� ���������� �����
	previous_time = current_time;

	if (float(clock() - timer) / CLOCKS_PER_SEC > 0.1) {
		sprintf_s(window_title, "OpenGL Application - FPS: %.2f", fps);
		glutSetWindowTitle(window_title);
		timer = clock();
	}
}