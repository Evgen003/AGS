#include "Display.h"
#define FPS_PRINT_TIMEOUT 0.2

void display(void)
{
	// ��� �������� ���������� ������ �� RenderManager
	RenderManager& renderManager = RenderManager::instance();
	renderManager.setCamera(&camera);
	// �������� ����� ������ �����
	renderManager.start();
	
	// ��������� � ������� ��� �������, ������� ���������� �������
	for (auto& graphicObject : graphicObjects) {
		renderManager.addToRenderQueue(graphicObject);
	}

	// ��������� ���������� �����
	renderManager.finish();

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

	if (float(clock() - timer) / CLOCKS_PER_SEC > FPS_PRINT_TIMEOUT) {
		sprintf_s(window_title, "OpenGL Application - FPS: %.2f", fps);
		glutSetWindowTitle(window_title);
		timer = clock();
	}
}