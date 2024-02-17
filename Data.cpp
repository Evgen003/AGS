#include "Data.h"

// используемые пространства имен
using namespace glm;
using namespace std;

LARGE_INTEGER frequency;        // частота счетчика производительности
LARGE_INTEGER current_time;     // текущее значение счетчика производительности
LARGE_INTEGER previous_time;    // значение счетчика производительности на предыдущем кадре
double elapsed_time;            // время, затраченное на отрисовку кадра
double fps;                     // количество кадров в секунду
char window_title[256];         // заголовок окна
unsigned int timer = 0;
Shader shader;
// функция для инициализации всех общих данных (камера, объекты и т.д.)
void initData() {

}
// функция для вывода квадрата с ребрами равными единице (от -0.5 до +0.5)
void drawObject()
{
	// переменные для вывода объекта (прямоугольника из двух треугольников)
	static bool init = true;
	static GLuint VAO_Index = 0;		// индекс VAO-буфера
	static GLuint VBO_Index = 0;		// индекс VBO-буфера
	static int VertexCount = 0;			// количество вершин

	// при первом вызове инициализируем VBO и VAO
	if (init) {
		init = false;
		// создание и заполнение VBO
		glGenBuffers(1, &VBO_Index);
		glBindBuffer(GL_ARRAY_BUFFER, VBO_Index);
		GLfloat	Verteces[] = {

			0.08, 0.07,
			0.15, 0.27,
			0.17, 0.27,
			0.23, 0.07,
			0.21, 0.07,
			0.19, 0.14,
			0.125, 0.14,
			0.10, 0.07
		};
		glBufferData(GL_ARRAY_BUFFER, sizeof(Verteces), Verteces, GL_STATIC_DRAW);

		// создание VAO
		glGenVertexArrays(1, &VAO_Index);
		glBindVertexArray(VAO_Index);
		// заполнение VAO
		glBindBuffer(GL_ARRAY_BUFFER, VBO_Index);
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(0);
		// "отвязка" буфера VAO, чтоб случайно не испортить
		glBindVertexArray(0);

		// указание количество вершин
		VertexCount = 3;
	}

	// выводим прямоугольник
	glBindVertexArray(VAO_Index);
	glDrawArrays(GL_TRIANGLES, 0, 8);
}