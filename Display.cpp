#include "Display.h"


void display(void)
{
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

	// �������� ����� ����� � ����� �������
	glClearColor(1.00, 1.00, 0100, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	// �������� ���� �������
	glEnable(GL_DEPTH_TEST);
	// ���������� ������
	shader.activate();

	// ������� ������������� 
	drawObject();

	// ����� ��������� � ������� �������
	glutSwapBuffers();
}