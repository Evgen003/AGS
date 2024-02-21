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

	// формируем матрицу проекции
	mat4 projectionMatrix;
	projectionMatrix = perspective(radians(35.0), 800.0 / 600.0, 1.0, 100.0);
	// генерирование матрицы камеры
	mat4 viewMatrix;
	// позиция камеры - (0, 3, 5)
	vec3 eye = vec3(0.0, 3.0, 5.0);
	// точка, в которую направлена камера - (0, 0, 0);
	vec3 center = vec3(0, 0, 0);
	// примерный вектор "вверх" (0, 1, 0)
	vec3 up = vec3(0, 1, 0);
	// матрица камеры
	viewMatrix = lookAt(eye, center, up);
	// матрица модели
	mat4 modelMatrix;
	// модель располагается в точке (1,0,0) без поворота
	modelMatrix = mat4(
		vec4(1, 0, 0, 0), // 1-ый столбец: направление оси X
		vec4(0, 1, 0, 0), // 2-ой столбец: направление оси Y
		vec4(0, 0, 1, 0), // 3-ий столбец: направление оси Z
		vec4(1, 0, 0, 1)); // 4-ый столбец: позиция объекта (начала координат)
	   // вычисляем матрицу наблюдения модели
	mat4 modelViewMatrix = viewMatrix * modelMatrix;
	// активация шейдера
	shader.activate();
	// устанавливаем uniform-переменные для матриц проекции и наблюдения модели
	shader.setUniform("projectionMatrix", projectionMatrix);
	shader.setUniform("modelViewMatrix", modelViewMatrix);
	// устанавливаем значение uniform-переменной для цвета каждого фрагмента
	vec4 color = vec4(0, 0, 1, 1);
	shader.setUniform("color", color);
	// выводим прямоугольник 
	drawObject();
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