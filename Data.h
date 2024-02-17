#pragma once

#include <windows.h>
#include <memory>
#include <vector>
#include "glew-2.1.0/include/GL/glew.h"
#include <glm/glm.hpp>
#include "GL/freeglut.h"
#include "Shader.h"

extern LARGE_INTEGER frequency;        // частота счетчика производительности
extern LARGE_INTEGER current_time;     // текущее значение счетчика производительности
extern LARGE_INTEGER previous_time;    // значение счетчика производительности на предыдущем кадре
extern double elapsed_time;            // время, затраченное на отрисовку кадра
extern double fps;                     // количество кадров в секунду
extern char window_title[256]; // заголовок окна
extern unsigned int timer;

extern Shader shader;
void initData();
void drawObject();