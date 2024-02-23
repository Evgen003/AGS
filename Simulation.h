#pragma once

#include <windows.h>
#include <ctime>
#include <vector>
#include "glew-2.1.0/include/GL/glew.h"
#include "GL/freeglut.h"
#include <glm/glm.hpp>
#include "Data.h"

using namespace std;
using namespace glm;

extern float simulationTime;
extern unsigned int lastClock;
void simulation(void);
void cameraSimulation();
void keyboard(float&, float&);
void mouse(float&, float&);
void mouseWheel(int, int, int, int);