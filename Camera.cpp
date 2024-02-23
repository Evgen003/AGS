#include "Camera.h"
Camera::Camera() {
	cameraPosition = vec3(2, 5, 7);
	observationPoint = vec3(0, 0, 0);
	radius = length(cameraPosition - observationPoint);
	viewMatrix = lookAt(cameraPosition, observationPoint, vec3(0, 1, 0));
	vec3 v1 = cameraPosition;
	vec3 v2 = vec3(v1.x, 0, v1.z);
	float cos_y = dot(normalize(v1), normalize(v2));
	vertAng = degrees(acos(cos_y));
	float cos_x = dot(normalize(v2), vec3(1, 0, 0));
	horizAng = degrees(acos(cos_x));
	//cout << vertAng << "   " << horizAng << endl;
}
// установить матрицу проекции
void Camera::setProjectionMatrix(float fovy, float aspect, float zNear, float zFar) {
	projectionMatrix = perspective(radians(fovy), aspect, zNear, zFar);
}
// получить матрицу проекции
mat4& Camera::getProjectionMatrix() {
	return projectionMatrix;
}
// получить матрицу вида
mat4& Camera::getViewMatrix() {
	return viewMatrix;
}
// передвинуть камеру и точку наблюдения в горизонтальной плоскости (OXZ)
void Camera::moveOXZ(float dx, float dz) {
	dx *= 0.1;
	dz *= 0.1;
	//cout << vertAng << ' ' << horizAng << endl;
	float angle = radians(horizAng);
	float angle2 = radians(90 + horizAng);
	
	cameraPosition.x += dx * cos(angle);
	cameraPosition.z += dx * sin(angle);
	observationPoint.x += dx * cos(angle);
	observationPoint.z += dx * sin(angle);
	
	cameraPosition.x += dz * cos(angle2);
	cameraPosition.z += dz * sin(angle2);
	observationPoint.x += dz * cos(angle2);
	observationPoint.z += dz * sin(angle2);
	cout << "Move func: " << horizAng << ' ' << vertAng << ' ' << radius << endl;
	cout << "CamPos: " << cameraPosition.x << ' ' << cameraPosition.y << ' ' << cameraPosition.z << endl;
	cout << "ObsPoi: " << observationPoint.x << ' ' << observationPoint.y << ' ' << observationPoint.z << endl << endl;
	recalculateViewMatrix();
}
// повернуть в горизонтальной и вертикальной плоскости (угол задается в градусах)
void Camera::rotate(float horizAngle, float vertAngle) {
	horizAng += horizAngle;
	vertAng += vertAngle;
	if (vertAng > 85) {
		vertAng = 85;
	}
	if (vertAng < 5) {
		vertAng = 5;
	}
	float rad_v = radians(vertAng);
	float rad_h = radians(horizAng);
	cameraPosition.x = radius * sin(rad_v) * cos(rad_h);
	cameraPosition.y = radius * cos(rad_v);
	cameraPosition.z = radius * sin(rad_v) * sin(rad_h);
	recalculateViewMatrix();
	cout << "Rotate func: " << horizAng << ' ' << vertAng << ' ' << radius << endl;
	cout << "CamPos: " << cameraPosition.x << ' ' << cameraPosition.y << ' ' << cameraPosition.z << endl;
	cout << "ObsPoi: " << observationPoint.x << ' ' << observationPoint.y << ' ' << observationPoint.z << endl << endl;
}
// приблизить/удалить камеру к/от точки наблюдения
void Camera::zoom(float dR) {
	radius += dR;
	if (radius > 50) {
		radius = 50;
	}
	if (radius < 5) {
		radius = 5;
	}
	float rad_v = radians(vertAng);
	float rad_h = radians(horizAng);
	cameraPosition.x = radius * sin(rad_v) * cos(rad_h);
	cameraPosition.y = radius * cos(rad_v);
	cameraPosition.z = radius * sin(rad_v) * sin(rad_h);
	cout << "Zoom func: " << horizAng << ' ' << vertAng << ' ' << radius << endl;
	cout << "CamPos: " << cameraPosition.x << ' ' << cameraPosition.y << ' ' << cameraPosition.z << endl;
	cout << "ObsPoi: " << observationPoint.x << ' ' << observationPoint.y << ' ' << observationPoint.z << endl << endl;
	recalculateViewMatrix();
}
// пересчитать матрицу вида
void Camera::recalculateViewMatrix() {
	viewMatrix = lookAt(cameraPosition, observationPoint, vec3(0, 1, 0));
}