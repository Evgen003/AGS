#include "Simulation.h"

float simulationTime = 0.0;
unsigned int lastClock = clock();
unsigned int mouseTimer = clock();
POINT previusMouseXY;
POINT MouseXY;

void simulation() {
	// получениче времени симуляции
	simulationTime = float(clock() - lastClock) / CLOCKS_PER_SEC;
	lastClock = clock();
	// вычисление нового смещения и изменение прочих параметров
	cameraSimulation();
	// перерисовать окно
	glutPostRedisplay();
}
void cameraSimulation() {
	glutMouseFunc(mouseWheel);
	if (GetAsyncKeyState(VK_RBUTTON)) {
		if (GetCursorPos(&MouseXY)) {
			//std::cout << MouseXY.x << "," << MouseXY.y << "\n";
			camera.rotate((320 - MouseXY.x) / 2, (240 - MouseXY.y) / 2);
			SetCursorPos(320, 240);
		}
	}
	float speed = 1 * simulationTime * 100;
	float camRot = 2;
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
	if (GetAsyncKeyState(VK_ADD))
	{
		camera.zoom(-0.02);
	}
	if (GetAsyncKeyState(VK_SUBTRACT))
	{
		camera.zoom(0.02);
	}
	if (GetAsyncKeyState(VK_UP))
	{
		camera.moveOXZ(-speed, 0);
	}
	if (GetAsyncKeyState(VK_DOWN))
	{
		camera.moveOXZ(speed, 0);
	}
	if (GetAsyncKeyState(VK_LEFT))
	{
		camera.moveOXZ(0, speed);
	}
	if (GetAsyncKeyState(VK_RIGHT))
	{
		camera.moveOXZ(0, -speed);
	}
}
void mouseWheel(int button, int dir, int x, int y) {
	if (button == 4) {
		/*std::cout << "Scroll Up\n";
		std::cout << "button = " << button << std::endl;
		std::cout << "dir = " << dir << std::endl;
		std::cout << "x = " << x << std::endl;
		std::cout << "y = " << y << std::endl;
		std::cout << std::endl;*/
		camera.zoom(0.5);
	}
	else if (button == 3) {
		/*std::cout << "Scroll Down\n";
		std::cout << "button = " << button << std::endl;
		std::cout << "dir = " << dir << std::endl;
		std::cout << "x = " << x << std::endl;
		std::cout << "y = " << y << std::endl;
		std::cout << std::endl;*/
		camera.zoom(-0.5);
	}
}
