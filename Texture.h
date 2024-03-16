#pragma once
#include <string>
#include <iostream>
#include "glew-2.1.0/include/GL/glew.h"
#include "IL/il.h"
#include "IL/ilu.h"
#include "IL/ilut.h"

// ПЕРЕЧИСЛЕНИЕ ДЛЯ ОПРЕДЕЛЕНИЯ РЕЖИМА ФИЛЬТРАЦИИ
enum class TextureFilter {
	POINT, // ТОЧЕЧНАЯ
	BILINEAR, // БИЛИНЕЙНАЯ
	TRILINEAR, // ТРИЛИНЕЙНАЯ
	ANISOTROPIC // АНИЗТОРОПНАЯ
};

class Texture
{
public:
	Texture();
	// загрузка текстуры из внешнего файла
	void load(std::string filename);

	// применение текстуры (привзяка к текстурному блоку и установка параметров)
	void bind(GLenum texUnit = GL_TEXTURE0);
	// отключение текстурирования для всех текстурных блоков
	static void disableAll();
private:
	// идентификатор (индекс) текстурного объекта
	GLuint texIndex;
};
