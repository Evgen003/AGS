#pragma once
#include "glew-2.1.0/include/GL/glew.h"
#include "GL/freeglut.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <vector>

#include "Data.h"
#include "Shader.h"
#include "Camera.h"
#include "GraphicObject.h"

using namespace glm;
using namespace std;

// КЛАСС ДЛЯ ВЗАИМОДЕЙСТВИЯ С OPENGL
// ВЕСЬ ВЫВОД ОСУЩЕСТВЛЯЕТСЯ ЧЕРЕЗ ЕДИНСТВЕННЫЙ ЭКЗЕМПЛЯР ДАННОГО КЛАССА
class RenderManager
{
public:
	// Статик-метод для получения экземпляра менеджера ресурса.
	static RenderManager& instance()
	{
		static RenderManager renderManager;
		return renderManager;
	}
	// инициализация объекта RenderManager, выполняется после инициализации OpenGL:
	// загрузка шейдеров, установка неизменных параметров и прочая инициализация
	void init();
	// Начало вывода очередного кадра (подготовка, очистка вектора графических объектов)
	void start();
	// установка используемой камеры
	void setCamera(Camera* camera);
	// добавление в очередь рендеринга очередного объекта для вывода
	void addToRenderQueue(GraphicObject& graphicObject);
	// завершение вывода кадра (основная работа)
	void finish();
private:
	// конструктор по умолчанию (приватный)
	RenderManager() {};
	// конструктора копирования нет
	RenderManager(const RenderManager& root) = delete;
	// оператора присваивания нет
	RenderManager& operator=(const RenderManager&) = delete;
private:
	// используемые шейдеры
	std::vector<Shader> shaders;
	// указатель на камеру
	Camera* camera;
	// список графических объектов, которые необходимо вывести в данном кадре
	std::vector<GraphicObject> graphicObjects;
};