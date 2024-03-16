#include "Light.h"

Light::Light() {
	this->direction.x = 0;
	this->direction.y = 20;
	this->direction.z = 0;
	this->ambient = vec4(0.1, 0.1, 0.1, 1);
	this->diffuse = vec4(0.1, 0.1, 0.1, 1);
	this->specular = vec4(0.1, 0.1, 0.1, 1);
}
void Light::setDirection(vec3& direction) {
	this->direction.x = direction.x;
	this->direction.y = direction.y;
	this->direction.z = direction.z;
	this->direction.w = 1;
}
void Light::setAmbient(vec4& ambient) {
	this->ambient = ambient;
}
void Light::setDiffuse(vec4& diffuse) {
	this->diffuse = diffuse;
}
void Light::setSpecular(vec4& specular) {
	this->specular = specular;
}
vec4& Light::getDirection() {
	return direction;
}
vec4& Light::getAmbient() {
	return ambient;
}
vec4& Light::getDiffuse() {
	return diffuse;
}
vec4& Light::getSpecular() {
	return specular;
}