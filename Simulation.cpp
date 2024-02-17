#include "Simulation.h"

float simulationTime = 0.0;
unsigned int lastClock = clock();

void simulation() {
	// получениче времени симуляции
	simulationTime = float(clock() - lastClock) / CLOCKS_PER_SEC;
	lastClock = clock();
	// вычисление нового смещения и изменение прочих параметров
	offset[0] += speed[0] * simulationTime;
	if (offset[0] >= 0.5) {
		offset[0] = 0.5;
		speed[0] *= -1;
	}
	if (offset[0] <= -0.5) {
		offset[0] = -0.5;
		speed[0] *= -1;
	}
	offset[1] += speed[1] * simulationTime;
	if (offset[1] >= 0.5) {
		offset[1] = 0.5;
		speed[1] *= -1;
	}
	if (offset[1] <= -0.5) {
		offset[1] = -0.5;
		speed[1] *= -1;
	}
	// перерисовать окно
	glutPostRedisplay();
}