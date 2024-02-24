#pragma once

#include <windows.h>
#include <memory>
#include <vector>
#include "glew-2.1.0/include/GL/glew.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "GL/freeglut.h"
#include "Shader.h"

// используемые пространства имен
using namespace glm;
using namespace std;

extern LARGE_INTEGER frequency;        // частота счетчика производительности
extern LARGE_INTEGER current_time;     // текущее значение счетчика производительности
extern LARGE_INTEGER previous_time;    // значение счетчика производительности на предыдущем кадре
extern double elapsed_time;            // врем€, затраченное на отрисовку кадра
extern double fps;                     // количество кадров в секунду
extern char window_title[256]; // заголовок окна
extern unsigned int timer;

extern Shader shader;
// ƒјЌЌџ≈ ƒЋя ¬џ¬ќƒј ѕ–яћќ”√ќЋ№Ќ» ј
// текущее смещение пр€моугольника
extern vec2 offset;
// скорость (направление) перемещени€ пр€моугольника
extern vec2 speed;
// первый цвет (дл€ градиентной заливки)
extern vec4 color1;
// второй цвет (дл€ градиентной заливки)
extern vec4 color2;

void initData();
void drawObject();