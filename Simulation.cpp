#include "Simulation.h"

float simulationTime = 0.0;
unsigned int lastClock = clock();

void simulation() {
	// получениче времени симуляции
	simulationTime = float(clock() - lastClock) / CLOCKS_PER_SEC;
	lastClock = clock();
	// вычисление нового смещения и изменение прочих параметров
	
	// перерисовать окно
	glutPostRedisplay();
}