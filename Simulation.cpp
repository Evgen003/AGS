#include "Simulation.h"
#define CAMERA_MOVE_SPEED 10
#define CAMERA_ROTATE_SPEED 0.4
#define CAMERA_ZOOM_SPEED 0.5
float simulationTime = 0.0;
unsigned int lastClock = clock();
unsigned int mouseTimer = clock();
POINT previousMouseXY;
POINT currentMouseXY;
float dx = 0;
float dz = 0;

void simulation() {
	// получениче времени симуляции
	simulationTime = float(clock() - lastClock) / CLOCKS_PER_SEC;
	lastClock = clock();
	// работа камеры
	cameraSimulation();
	// перерисовать окно
	glutPostRedisplay();
}
void cameraSimulation() {
	float dx = 0;
	float dz = 0;
	float rx = 0;
	float ry = 0;
	keyboardSurvey(dx, dz);
	camera.moveOXZ(dx * simulationTime, dz * simulationTime);

	glutMouseFunc(mouseWheel);
	
	if (!GetAsyncKeyState(VK_RBUTTON)) {
		if (GetCursorPos(&currentMouseXY)) {
			previousMouseXY = currentMouseXY;
		}
	}
	if (GetAsyncKeyState(VK_RBUTTON)) {
		if (GetCursorPos(&currentMouseXY)) {
			//cout << currentMouseXY.x << " | " << currentMouseXY.y << "\n";
			if ((currentMouseXY.x != previousMouseXY.x)
				|| (currentMouseXY.y != previousMouseXY.y)) {
				rx = currentMouseXY.x - previousMouseXY.x;
				ry = currentMouseXY.y - previousMouseXY.y;
				previousMouseXY = currentMouseXY;
				//cout << rx << " | " << ry << "\n";
			}
		}
	}
	camera.rotate(rx * CAMERA_ROTATE_SPEED, ry * CAMERA_ROTATE_SPEED);
	if (GetAsyncKeyState(0x57)) {
		camera.rotate(0, -0.1);
	}
	if (GetAsyncKeyState(0x53)) {
		camera.rotate(0, 0.1);
	}
	if (GetAsyncKeyState(0x41)) {
		camera.rotate(0.1, 0);
	}
	if (GetAsyncKeyState(0x44)) {
		camera.rotate(-0.1, 0);
	}
}

void keyboardSurvey(float& dx, float& dz) {
	if (GetAsyncKeyState(VK_UP))
	{
		dx -= CAMERA_MOVE_SPEED;
	}
	if (GetAsyncKeyState(VK_DOWN))
	{
		dx += CAMERA_MOVE_SPEED;
	}
	if (GetAsyncKeyState(VK_LEFT))
	{
		dz += CAMERA_MOVE_SPEED;
	}
	if (GetAsyncKeyState(VK_RIGHT))
	{
		dz -= CAMERA_MOVE_SPEED;
	}
}
void mouseWheel(int button, int dir, int x, int y) {
	float delta = 0;
	if (button == 4) {
		delta += CAMERA_ZOOM_SPEED;
	}
	else if (button == 3) {
		delta -= CAMERA_ZOOM_SPEED;
	}
	camera.zoom(delta);
}
