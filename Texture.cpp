#include "Texture.h"
using namespace std;
Texture::Texture() {

}
// загрузка текстуры из внешнего файла
void Texture::load(std::string filename) {
	// создаем новое "изображение"
	ILuint imageID = ilGenImage();
	// задаем текущее "изображение"
	ilBindImage(imageID);
	// загружаем изображение
	wchar_t unicodeString[256];
	wsprintf(unicodeString, L"%S", filename.c_str());
	bool result = ilLoadImage(unicodeString);
	cout << "BindIMG\n";
	if (result) {
		cout << "Texture " << filename << " open success\n";
	}
	else {
		cout << "Texture " << filename << " ERROR\n";
		return;
	}
	int width = ilGetInteger(IL_IMAGE_WIDTH);
	int	height = ilGetInteger(IL_IMAGE_HEIGHT);
	int	format = ilGetInteger(IL_IMAGE_FORMAT);
	int type = ilGetInteger(IL_IMAGE_TYPE);
	cout << width << ' ' << height << ' ' << format << ' ' << type << endl;
	char* pixels = new char[width * height * 4];
	ilCopyPixels(0, 0, 0, width, height, 1, IL_RGBA, IL_UNSIGNED_BYTE, pixels);

	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glActiveTexture(GL_TEXTURE0);
	glGenTextures(1, &texIndex);
	glBindTexture(GL_TEXTURE_2D, texIndex);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixels);
	delete[] pixels;
	glGenerateMipmap(GL_TEXTURE_2D);
	//glTexParameteri
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glBindTexture(GL_TEXTURE_2D, 0);

}

// применение текстуры (привзяка к текстурному блоку и установка параметров)
void Texture::bind(GLenum texUnit) {
	glActiveTexture(texUnit);
	glBindTexture(GL_TEXTURE_2D, texIndex);
}
// отключение текстурирования для всех текстурных блоков
void Texture::disableAll() {
	glBindTexture(GL_TEXTURE_2D, 0);
}