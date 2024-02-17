#pragma once

#include <windows.h>
#include <memory>
#include <vector>
#include "glew-2.1.0/include/GL/glew.h"
#include <glm/glm.hpp>
#include "GL/freeglut.h"
#include "Shader.h"

extern LARGE_INTEGER frequency;        // ������� �������� ������������������
extern LARGE_INTEGER current_time;     // ������� �������� �������� ������������������
extern LARGE_INTEGER previous_time;    // �������� �������� ������������������ �� ���������� �����
extern double elapsed_time;            // �����, ����������� �� ��������� �����
extern double fps;                     // ���������� ������ � �������
extern char window_title[256]; // ��������� ����
extern unsigned int timer;

extern Shader shader;
void initData();
void drawObject();