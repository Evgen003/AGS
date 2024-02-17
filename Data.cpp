#include "Data.h"

LARGE_INTEGER frequency;        // частота счетчика производительности
LARGE_INTEGER current_time;     // текущее значение счетчика производительности
LARGE_INTEGER previous_time;    // значение счетчика производительности на предыдущем кадре
double elapsed_time;            // время, затраченное на отрисовку кадра
double fps;                     // количество кадров в секунду
char window_title[256];         // заголовок окна
unsigned int timer = 0;
// ИСПОЛЬЗУЕМЫЙ ШЕЙДЕР (ПОКА ТОЛЬКО ОДИН)
Shader shader;
// ДАННЫЕ ДЛЯ ВЫВОДА ПРЯМОУГОЛЬНИКА
// текущее смещение прямоугольника
vec2 offset = vec2(0.25, 0);
// скорость (направление) перемещения прямоугольника
vec2 speed = vec2(+0.30, -0.25);
// первый цвет (для градиентной заливки)
vec4 color1 = vec4(1, 0, 0, 1);
// второй цвет (для градиентной заливки)
vec4 color2 = vec4(0, 0, 1, 1);

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

			-0.5, +0.5,
			-0.5, -0.5,
			+0.5, +0.5,
			+0.5, +0.5,
			-0.5, -0.5,
			+0.5, -0.5
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