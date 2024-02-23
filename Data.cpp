#include "Data.h"

LARGE_INTEGER frequency;        // частота счетчика производительности
LARGE_INTEGER current_time;     // текущее значение счетчика производительности
LARGE_INTEGER previous_time;    // значение счетчика производительности на предыдущем кадре
double elapsed_time;            // время, затраченное на отрисовку кадра
double fps;                     // количество кадров в секунду
char window_title[256];         // заголовок окна
unsigned int timer = 0;

Camera camera;
// ИСПОЛЬЗУЕМЫЙ ШЕЙДЕР (ПОКА ТОЛЬКО ОДИН)
Shader shader;
// СПИСОК ГРАФИЧЕСКИХ ОБЪЕКТОВ ДЛЯ ВЫВОДА НА ЭКРАН
vector <GraphicObject>graphicObjects;
// функция для инициализации всех общих данных (камера, объекты и т.д.)
void initData() {
	float ang = 0;
	for (int i = 0; i < 9; i++) {
		vec4 color = vec4(1, 0, 0, 1);
		GraphicObject obj;
		obj.setColor(color);
		vec3 pos = vec3((i % 3) * 2, 0, ((int)i / 3) * 2);
		obj.setPosition(pos);
		obj.setAngle(ang);
		ang += 10;
		graphicObjects.push_back(obj);
	}
}
// функция для вывода квадрата с ребрами равными единице (от -0.5 до +0.5)
void drawBox() {
	// переменные для вывода объекта (прямоугольника из двух треугольников)
	static GLuint VAO_Index = 0;	// индекс VAO-буфера
	static GLuint VBO_Index = 0;	// индекс VBO-буфера
	static int VertexCount = 0;		// количество вершин
	static bool init = true;

	if (init) {
		// создание и заполнение VBO
		glGenBuffers(1, &VBO_Index);
		glBindBuffer(GL_ARRAY_BUFFER, VBO_Index);
		GLfloat Verteces[] = {
			// передняя грань (два треугольника)
			-0.5, +0.5, +0.5, -0.5, -0.5, +0.5, +0.5, +0.5, +0.5,
			+0.5, +0.5, +0.5, -0.5, -0.5, +0.5, +0.5, -0.5, +0.5,
			// задняя грань (два треугольника)
			+0.5, +0.5,	-0.5, +0.5, -0.5, -0.5, -0.5, +0.5, -0.5,
			-0.5, +0.5,	-0.5, +0.5, -0.5, -0.5, -0.5, -0.5, -0.5,
			// правая грань (два треугольника) 
			+0.5, -0.5,	+0.5, +0.5, -0.5, -0.5, +0.5, +0.5, +0.5,
			+0.5, +0.5,	+0.5, +0.5, -0.5, -0.5, +0.5, +0.5, -0.5,
			// левая грань (два треугольника)
			-0.5, +0.5,	+0.5, -0.5, +0.5, -0.5, -0.5, -0.5, +0.5,
			-0.5, -0.5,	+0.5, -0.5, +0.5, -0.5, -0.5, -0.5, -0.5,
			// верхняя грань (два треугольника)
			-0.5, +0.5, -0.5, -0.5, +0.5, +0.5, +0.5, +0.5, -0.5,
			+0.5, +0.5, -0.5, -0.5, +0.5, +0.5, +0.5, +0.5, +0.5,
			// нижняя грань (два треугольника)
			-0.5, -0.5, +0.5, -0.5, -0.5, -0.5, +0.5, -0.5, +0.5,
			+0.5, -0.5, +0.5, -0.5, -0.5, -0.5, +0.5, -0.5, -0.5
		};
		glBufferData(GL_ARRAY_BUFFER, sizeof(Verteces), Verteces, GL_STATIC_DRAW);

		// создание VAO
		glGenVertexArrays(1, &VAO_Index);
		glBindVertexArray(VAO_Index);

		// инициализация VAO
		glBindBuffer(GL_ARRAY_BUFFER, VBO_Index);
		int location = 0;
		glVertexAttribPointer(location, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(location);

		// "отвязка" буфера VAO на всякий случай, чтоб случайно не испортить
		glBindVertexArray(0);

		// указание количество вершин
		VertexCount = 6 * 6;
		init = false;
	}

	// вывод модели кубика на экран
	glBindVertexArray(VAO_Index);
	glDrawArrays(GL_TRIANGLES, 0, VertexCount);
}