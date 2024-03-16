#include "Data.h"

LARGE_INTEGER frequency;        // частота счетчика производительности
LARGE_INTEGER current_time;     // текущее значение счетчика производительности
LARGE_INTEGER previous_time;    // значение счетчика производительности на предыдущем кадре
double elapsed_time;            // время, затраченное на отрисовку кадра
double fps;                     // количество кадров в секунду
char window_title[256];         // заголовок окна
unsigned int timer = 0;

Shader shader;
Camera camera;
// СПИСОК ГРАФИЧЕСКИХ ОБЪЕКТОВ ДЛЯ ВЫВОДА НА ЭКРАН
vector <GraphicObject>graphicObjects;
// функция для инициализации всех общих данных (камера, объекты и т.д.)
void initData() {
	RenderManager::instance().init();
	initGraphicObjects();
}

// вспомогательная функция для инициализации графических объектов
void initGraphicObjects() {
	// ссылка на менеджер ресурсов (для удобства)
	ResourceManager& rm = ResourceManager::instance();
	// временная переменная для хранения идентификаторов меша
	int meshId = -1;
	// временная переменная для хранения идентификаторов текстуры
	int textureId = -1;
	// временная переменная для представления графического объекта
	GraphicObject graphicObject;
	// добавление графического объекта
	meshId = rm.loadMesh("MESHES\\buildings\\house_2.obj");
	graphicObject.setMeshId(meshId);
	textureId = rm.loadTexture("TEXTURES\\buildings\\house_2_orange.png");
	graphicObject.setTextureId(textureId);
	graphicObject.setColor(vec4(0.2, 0.2, 0.2, 1));
	graphicObject.setPosition(vec3(0, 0, 0));
	graphicObject.setAngle(0.0);
	graphicObjects.push_back(graphicObject);
	// добавление графического объекта
	meshId = rm.loadMesh("MESHES\\natures\\big_tree.obj");
	graphicObject.setMeshId(meshId);
	textureId = rm.loadTexture("TEXTURES\\natures\\nature.png");
	graphicObject.setTextureId(textureId);
	graphicObject.setColor(vec4(0.2, 0.8, 0.2, 1));
	graphicObject.setPosition(vec3(7.5, -0.75, 2.5));
	graphicObject.setAngle(0.0);
	graphicObjects.push_back(graphicObject);
	// добавление графического объекта
	meshId = rm.loadMesh("MESHES\\natures\\big_tree.obj");
	graphicObject.setMeshId(meshId);
	textureId = rm.loadTexture("TEXTURES\\natures\\nature.png");
	graphicObject.setTextureId(textureId);
	graphicObject.setColor(vec4(0.2, 0.8, 0.2, 1));
	graphicObject.setPosition(vec3(-7.5, -0.75, 2.5));
	graphicObject.setAngle(0.0);
	graphicObjects.push_back(graphicObject);
	// добавление графического объекта
	meshId = rm.loadMesh("MESHES\\vehicles\\police_car.obj");
	graphicObject.setMeshId(meshId);
	textureId = rm.loadTexture("TEXTURES\\vehicles\\police_car.png");
	graphicObject.setTextureId(textureId);
	graphicObject.setColor(vec4(0.2, 0.2, 1.0, 1));
	graphicObject.setPosition(vec3(+4.5, -2.15, +6.5));
	graphicObject.setAngle(-115.0);
	graphicObjects.push_back(graphicObject);
	// добавление графического объекта
	meshId = rm.loadMesh("MESHES\\vehicles\\police_car.obj");
	graphicObject.setMeshId(meshId);
	textureId = rm.loadTexture("TEXTURES\\vehicles\\police_car.png");
	graphicObject.setTextureId(textureId);
	graphicObject.setColor(vec4(0.23, 0.23, 1.0, 1));
	graphicObject.setPosition(vec3(+4.25, -2.15, +10.5));
	graphicObject.setAngle(+105.0);
	graphicObjects.push_back(graphicObject);
	// добавление графического объекта
	meshId = rm.loadMesh("MESHES\\vehicles\\jeep.obj");
	graphicObject.setMeshId(meshId);
	textureId = rm.loadTexture("TEXTURES\\vehicles\\jeep_purple.png");
	graphicObject.setTextureId(textureId);
	graphicObject.setColor(vec4(0.95, 0.13, 0.13, 1));
	graphicObject.setPosition(vec3(-1.25, -2.15, +9.0));
	graphicObject.setAngle(+170.0);
	graphicObjects.push_back(graphicObject);
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