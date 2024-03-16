#include "Display.h"
#define FPS_PRINT_TIMEOUT 0.2

void display(void)
{
	// ������� ������ �����
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	// ��������� ����� ������� (�� ������ ������)
	glEnable(GL_DEPTH_TEST);
	// ����� ��������� � ���� ����� � ���������� ��������� ������
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);

	// ��������� �������
	shader.activate();
	
	// ������������� ������� ��������
	mat4& projectionMatrix = camera.getProjectionMatrix();
	shader.setUniform("projectionMatrix", projectionMatrix);

	// �������� ������� ������
	mat4& viewMatrix = camera.getViewMatrix();

	//������� ��� �������
	for (auto& graphicObject : graphicObjects) {
		// ������������� ������� ���������� ������
		mat4 modelViewMatrix = viewMatrix * graphicObject.getModelMatrix();
		shader.setUniform("modelViewMatrix", modelViewMatrix);

		// ������������� ����
		shader.setUniform("color", graphicObject.getColor());

		// ������������� �������� (����������� � ����������� �����)
		int textureId = graphicObject.getTextureId();
		Texture* texture = ResourceManager::instance().getTexture(textureId);
		if (texture != nullptr) {
			texture->bind(GL_TEXTURE0);
		}

		//������� ���
		int meshId = graphicObject.getMeshId();
		Mesh* mesh = ResourceManager::instance().getMesh(meshId);
		if (mesh != nullptr) {
			mesh->drawOne();
		}
	}

	// ����� ��������� � ������� �������
	glutSwapBuffers();
	printFPS();
}
void printFPS() {
	// ������������� ������� �������� ������������������
	QueryPerformanceFrequency(&frequency);
	// ��������� �������� �������� �������� ������������������
	QueryPerformanceCounter(&current_time);
	// ���������� �������, ������������ �� ��������� �����
	elapsed_time = (double)(current_time.QuadPart - previous_time.QuadPart) / frequency.QuadPart;
	// ���������� ���������� ������ � �������
	fps = 1.0 / elapsed_time;
	// ���������� �������� �������� �������� ������������������ ��� ���������� �����
	previous_time = current_time;

	if (float(clock() - timer) / CLOCKS_PER_SEC > FPS_PRINT_TIMEOUT) {
		sprintf_s(window_title, "OpenGL Application - FPS: %.2f", fps);
		glutSetWindowTitle(window_title);
		timer = clock();
	}
}