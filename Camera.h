#pragma once
#include "glew-2.1.0/include/GL/glew.h"
#include "GL/freeglut.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

using namespace glm;
using namespace std;

class Camera
{
public:
	// конструктор по умолчанию
	Camera();
	// установить матрицу проекции
	void setProjectionMatrix(float fovy, float aspect, float zNear, float zFar);
	// получить матрицу проекции
	mat4& getProjectionMatrix();
	// получить матрицу вида
	mat4& getViewMatrix();
	// передвинуть камеру и точку наблюдения в горизонтальной плоскости (OXZ)
	void moveOXZ(float dx, float dz);
	// повернуть в горизонтальной и вертикальной плоскости (угол задается в градусах)
	void rotate(float horizAngle, float vertAngle);
	// приблизить/удалить камеру к/от точки наблюдения
	void zoom(float dR);
private:
	// пересчитать матрицу вида
	void recalculateViewMatrix();
private:
	mat4 projectionMatrix;
	mat4 viewMatrix;
	vec3 cameraPosition;
	vec3 observationPoint;
};
