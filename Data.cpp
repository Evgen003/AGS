#include "Data.h"

LARGE_INTEGER frequency;        // ������� �������� ������������������
LARGE_INTEGER current_time;     // ������� �������� �������� ������������������
LARGE_INTEGER previous_time;    // �������� �������� ������������������ �� ���������� �����
double elapsed_time;            // �����, ����������� �� ��������� �����
double fps;                     // ���������� ������ � �������
char window_title[256];         // ��������� ����
unsigned int timer = 0;

Shader shader;
Camera camera;
// ������ ����������� �������� ��� ������ �� �����
vector <GraphicObject>graphicObjects;
// ������� ��� ������������� ���� ����� ������ (������, ������� � �.�.)
void initData() {
	RenderManager::instance().init();
	initGraphicObjects();
}

// ��������������� ������� ��� ������������� ����������� ��������
void initGraphicObjects() {
	// ������ �� �������� �������� (��� ��������)
	ResourceManager& rm = ResourceManager::instance();
	// ��������� ���������� ��� �������� ��������������� ����
	int meshId = -1;
	// ��������� ���������� ��� �������� ��������������� ��������
	int textureId = -1;
	// ��������� ���������� ��� ������������� ������������ �������
	GraphicObject graphicObject;
	// ���������� ������������ �������
	meshId = rm.loadMesh("MESHES\\buildings\\house_2.obj");
	graphicObject.setMeshId(meshId);
	textureId = rm.loadTexture("TEXTURES\\buildings\\house_2_orange.png");
	graphicObject.setTextureId(textureId);
	graphicObject.setColor(vec4(0.2, 0.2, 0.2, 1));
	graphicObject.setPosition(vec3(0, 0, 0));
	graphicObject.setAngle(0.0);
	graphicObjects.push_back(graphicObject);
	// ���������� ������������ �������
	meshId = rm.loadMesh("MESHES\\natures\\big_tree.obj");
	graphicObject.setMeshId(meshId);
	textureId = rm.loadTexture("TEXTURES\\natures\\nature.png");
	graphicObject.setTextureId(textureId);
	graphicObject.setColor(vec4(0.2, 0.8, 0.2, 1));
	graphicObject.setPosition(vec3(7.5, -0.75, 2.5));
	graphicObject.setAngle(0.0);
	graphicObjects.push_back(graphicObject);
	// ���������� ������������ �������
	meshId = rm.loadMesh("MESHES\\natures\\big_tree.obj");
	graphicObject.setMeshId(meshId);
	textureId = rm.loadTexture("TEXTURES\\natures\\nature.png");
	graphicObject.setTextureId(textureId);
	graphicObject.setColor(vec4(0.2, 0.8, 0.2, 1));
	graphicObject.setPosition(vec3(-7.5, -0.75, 2.5));
	graphicObject.setAngle(0.0);
	graphicObjects.push_back(graphicObject);
	// ���������� ������������ �������
	meshId = rm.loadMesh("MESHES\\vehicles\\police_car.obj");
	graphicObject.setMeshId(meshId);
	textureId = rm.loadTexture("TEXTURES\\vehicles\\police_car.png");
	graphicObject.setTextureId(textureId);
	graphicObject.setColor(vec4(0.2, 0.2, 1.0, 1));
	graphicObject.setPosition(vec3(+4.5, -2.15, +6.5));
	graphicObject.setAngle(-115.0);
	graphicObjects.push_back(graphicObject);
	// ���������� ������������ �������
	meshId = rm.loadMesh("MESHES\\vehicles\\police_car.obj");
	graphicObject.setMeshId(meshId);
	textureId = rm.loadTexture("TEXTURES\\vehicles\\police_car.png");
	graphicObject.setTextureId(textureId);
	graphicObject.setColor(vec4(0.23, 0.23, 1.0, 1));
	graphicObject.setPosition(vec3(+4.25, -2.15, +10.5));
	graphicObject.setAngle(+105.0);
	graphicObjects.push_back(graphicObject);
	// ���������� ������������ �������
	meshId = rm.loadMesh("MESHES\\vehicles\\jeep.obj");
	graphicObject.setMeshId(meshId);
	textureId = rm.loadTexture("TEXTURES\\vehicles\\jeep_purple.png");
	graphicObject.setTextureId(textureId);
	graphicObject.setColor(vec4(0.95, 0.13, 0.13, 1));
	graphicObject.setPosition(vec3(-1.25, -2.15, +9.0));
	graphicObject.setAngle(+170.0);
	graphicObjects.push_back(graphicObject);
}

// ������� ��� ������ �������� � ������� ������� ������� (�� -0.5 �� +0.5)
void drawBox() {
	// ���������� ��� ������ ������� (�������������� �� ���� �������������)
	static GLuint VAO_Index = 0;	// ������ VAO-������
	static GLuint VBO_Index = 0;	// ������ VBO-������
	static int VertexCount = 0;		// ���������� ������
	static bool init = true;

	if (init) {
		// �������� � ���������� VBO
		glGenBuffers(1, &VBO_Index);
		glBindBuffer(GL_ARRAY_BUFFER, VBO_Index);
		GLfloat Verteces[] = {
			// �������� ����� (��� ������������)
			-0.5, +0.5, +0.5, -0.5, -0.5, +0.5, +0.5, +0.5, +0.5,
			+0.5, +0.5, +0.5, -0.5, -0.5, +0.5, +0.5, -0.5, +0.5,
			// ������ ����� (��� ������������)
			+0.5, +0.5,	-0.5, +0.5, -0.5, -0.5, -0.5, +0.5, -0.5,
			-0.5, +0.5,	-0.5, +0.5, -0.5, -0.5, -0.5, -0.5, -0.5,
			// ������ ����� (��� ������������) 
			+0.5, -0.5,	+0.5, +0.5, -0.5, -0.5, +0.5, +0.5, +0.5,
			+0.5, +0.5,	+0.5, +0.5, -0.5, -0.5, +0.5, +0.5, -0.5,
			// ����� ����� (��� ������������)
			-0.5, +0.5,	+0.5, -0.5, +0.5, -0.5, -0.5, -0.5, +0.5,
			-0.5, -0.5,	+0.5, -0.5, +0.5, -0.5, -0.5, -0.5, -0.5,
			// ������� ����� (��� ������������)
			-0.5, +0.5, -0.5, -0.5, +0.5, +0.5, +0.5, +0.5, -0.5,
			+0.5, +0.5, -0.5, -0.5, +0.5, +0.5, +0.5, +0.5, +0.5,
			// ������ ����� (��� ������������)
			-0.5, -0.5, +0.5, -0.5, -0.5, -0.5, +0.5, -0.5, +0.5,
			+0.5, -0.5, +0.5, -0.5, -0.5, -0.5, +0.5, -0.5, -0.5
		};
		glBufferData(GL_ARRAY_BUFFER, sizeof(Verteces), Verteces, GL_STATIC_DRAW);

		// �������� VAO
		glGenVertexArrays(1, &VAO_Index);
		glBindVertexArray(VAO_Index);

		// ������������� VAO
		glBindBuffer(GL_ARRAY_BUFFER, VBO_Index);
		int location = 0;
		glVertexAttribPointer(location, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(location);

		// "�������" ������ VAO �� ������ ������, ���� �������� �� ���������
		glBindVertexArray(0);

		// �������� ���������� ������
		VertexCount = 6 * 6;
		init = false;
	}

	// ����� ������ ������ �� �����
	glBindVertexArray(VAO_Index);
	glDrawArrays(GL_TRIANGLES, 0, VertexCount);
}