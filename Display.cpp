#include "Display.h"


void display(void)
{
	// очистка буфера кадра
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	// включение теста глубины (на всякий случай)
	glEnable(GL_DEPTH_TEST);
	// вывод полигонов в виде линий с отсечением нелицевых граней
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);

	// активация шейдера
	shader.activate();
	
	// устанавливаем матрицу проекции
	mat4& projectionMatrix = camera.getProjectionMatrix();
	shader.setUniform("projectionMatrix", projectionMatrix);

	// устанавливаем матрицу камеры
	mat4& viewMatrix = camera.getViewMatrix();

	//выводим все объекты
	for (auto& grObj : graphicObjects) {
		// устанавливаем матрицу наблюдения модели
		mat4 modelViewMatrix = viewMatrix * grObj.getModelMatrix();
		shader.setUniform("modelViewMatrix", modelViewMatrix);

		// устанавливаем цвет
		shader.setUniform("color", grObj.getColor());

		//выводим модель кубика
		drawBox();
	}

	// смена переднего и заднего буферов
	glutSwapBuffers();
	printFPS();
}
void printFPS() {
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
}