#include "Display.h"
#define FPS_PRINT_TIMEOUT 0.2

void display(void)
{
	// для удобства определяем ссылку на RenderManager
	RenderManager& renderManager = RenderManager::instance();
	renderManager.setCamera(&camera);
	// начинаем вывод нового кадра
	renderManager.start();
	
	// добавляем в очередь все объекты, которые необходимо вывести
	for (auto& graphicObject : graphicObjects) {
		renderManager.addToRenderQueue(graphicObject);
	}

	// завершаем построение кадра
	renderManager.finish();

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

	if (float(clock() - timer) / CLOCKS_PER_SEC > FPS_PRINT_TIMEOUT) {
		sprintf_s(window_title, "OpenGL Application - FPS: %.2f", fps);
		glutSetWindowTitle(window_title);
		timer = clock();
	}
}