#include "Camera.h"
Camera::Camera() {

}
// ���������� ������� ��������
void Camera::setProjectionMatrix(float fovy, float aspect, float zNear, float zFar) {
	projectionMatrix = perspective(radians(fovy), aspect, zNear, zFar);
}
// �������� ������� ��������
mat4& Camera::getProjectionMatrix() {
	return projectionMatrix;
}
// �������� ������� ����
mat4& Camera::getViewMatrix() {
	return viewMatrix;
}
// ����������� ������ � ����� ���������� � �������������� ��������� (OXZ)
void Camera::moveOXZ(float dx, float dz) {

}
// ��������� � �������������� � ������������ ��������� (���� �������� � ��������)
void Camera::rotate(float horizAngle, float vertAngle) {

}
// ����������/������� ������ �/�� ����� ����������
void Camera::zoom(float dR) {

}
// ����������� ������� ����
void Camera::recalculateViewMatrix() {
	viewMatrix = lookAt(cameraPosition, observationPoint, vec3(0, 1, 0));
}