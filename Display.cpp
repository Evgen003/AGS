#include "Display.h"


void display(void)
{
	// инициализация частоты счетчика производительности
	QueryPerformanceFrequency(&frequency);

	// получение текущего значения счетчика производительности
	QueryPerformanceCounter(&current_time);

	// вычисление времени, затраченного на отрисовку кадра
	elapsed_time = (double)(current_time.QuadPart - previous_time.QuadPart) / frequency.QuadPart;
	// вычисление количества кадров в секунду
	fps = 1.0 / elapsed_time;

	// сохранение текущего значения счетчика производительности для следующего кадра
	previous_time = current_time;

	if (float(clock() - timer) / CLOCKS_PER_SEC > 0.1) {
		sprintf_s(window_title, "OpenGL Application - FPS: %.2f", fps);
		glutSetWindowTitle(window_title);
		timer = clock();
	}

	// отчищаем буфер цвета и буфер глубины
	glClearColor(1.00, 1.00, 0100, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	// включаем тест глубины
	glEnable(GL_DEPTH_TEST);
	// активируем шейдер
	shader.activate();

	// выводим прямоугольник 
	drawObject();

	// смена переднего и заднего буферов
	glutSwapBuffers();
}