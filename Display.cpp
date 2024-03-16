#include "Display.h"
#define FPS_PRINT_TIMEOUT 0.2

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

	// получаем матрицу камеры
	mat4& viewMatrix = camera.getViewMatrix();

	//выводим все объекты
	for (auto& graphicObject : graphicObjects) {
		// устанавливаем матрицу наблюдения модели
		mat4 modelViewMatrix = viewMatrix * graphicObject.getModelMatrix();
		shader.setUniform("modelViewMatrix", modelViewMatrix);

		// устанавливаем цвет
		shader.setUniform("color", graphicObject.getColor());

		// устанавливаем текстуру (привязываем к текстурному блоку)
		int textureId = graphicObject.getTextureId();
		Texture* texture = ResourceManager::instance().getTexture(textureId);
		if (texture != nullptr) {
			texture->bind(GL_TEXTURE0);
		}

		//выводим меш
		int meshId = graphicObject.getMeshId();
		Mesh* mesh = ResourceManager::instance().getMesh(meshId);
		if (mesh != nullptr) {
			mesh->drawOne();
		}
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

	if (float(clock() - timer) / CLOCKS_PER_SEC > FPS_PRINT_TIMEOUT) {
		sprintf_s(window_title, "OpenGL Application - FPS: %.2f", fps);
		glutSetWindowTitle(window_title);
		timer = clock();
	}
}