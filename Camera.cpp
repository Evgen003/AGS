#include "Camera.h"
Camera::Camera() {

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

}
// повернуть в горизонтальной и вертикальной плоскости (угол задается в градусах)
void Camera::rotate(float horizAngle, float vertAngle) {

}
// приблизить/удалить камеру к/от точки наблюдения
void Camera::zoom(float dR) {

}
// пересчитать матрицу вида
void Camera::recalculateViewMatrix() {
	viewMatrix = lookAt(cameraPosition, observationPoint, vec3(0, 1, 0));
}