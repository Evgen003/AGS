#include "GraphicObject.h"
// конструктор по умолчанию
GraphicObject::GraphicObject() {
	modelMatrix = mat4(
		vec4(1, 0, 0, 0), // 1-ый столбец: направление оси X
		vec4(0, 1, 0, 0), // 2-ой столбец: направление оси Y
		vec4(0, 0, 1, 0), // 3-ий столбец: направление оси Z
		vec4(0, 0, 0, 1)); // 4-ый столбец: позиция объекта (начала координат)
	color = vec4(1, 1, 1, 1);
	meshId = 0;
	textureId = 0;
	materialId = 0;
}
// установить цвет объекта
void GraphicObject::setColor(vec4 color) {
	this->color = color;
}
// установить позицию объекта
void GraphicObject::setPosition(vec3 position) {
	modelMatrix[3][0] = position.x;
	modelMatrix[3][1] = position.y;
	modelMatrix[3][2] = position.z;	
}
// установить угол поворота в градусах относительно оси OY по часовой стрелке
void GraphicObject::setAngle(float degree) {
	float rad = radians(degree);
	modelMatrix[0][0] = cos(rad);
	modelMatrix[0][2] = sin(rad);
	modelMatrix[2][0] = -sin(rad);
	modelMatrix[2][2] = cos(rad);
}
// установить идентификатор используемого меша
void GraphicObject::setMeshId(int id) {
	meshId = id;
}
// установить идентификатор используемой текстуры
void GraphicObject::setTextureId(int id) {
	textureId = id;
}
// установить идентификатор используемого материала
void GraphicObject::setMaterialId(int id) {
	materialId = id;
}
// получить различные параметры
vec4& GraphicObject::getColor() {
	return color;
}
mat4& GraphicObject::getModelMatrix() {
	return modelMatrix;
}
int GraphicObject::getMeshId() {
	return meshId;
}
int GraphicObject::getTextureId() {
	return textureId;
}
int GraphicObject::getMaterialId() {
	return materialId;
}