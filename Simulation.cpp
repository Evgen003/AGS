#include "Simulation.h"

float simulationTime = 0.0;
unsigned int lastClock = clock();

void simulation() {
	// ���������� ������� ���������
	simulationTime = float(clock() - lastClock) / CLOCKS_PER_SEC;
	lastClock = clock();
	// ���������� ������ �������� � ��������� ������ ����������
	
	// ������������ ����
	glutPostRedisplay();
}