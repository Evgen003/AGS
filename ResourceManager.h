#pragma once
#include <string>
#include <windows.h>
#include "stdio.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <map>

#include "glew-2.1.0/include/GL/glew.h"
#include "GL/freeglut.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Mesh.h"
#include "Texture.h"
#include "Material.h"
using namespace std;
using namespace glm;

// КЛАСС ДЛЯ РАБОТЫ С МЕНЕДЖЕРОМ РЕСУРСОВ (РЕАЛИЗОВАН НА ОСНОВЕ ШАБЛОНА SINGLTON)
class ResourceManager
{
public:
	// Статик-метод для получения экземпляра менеджера ресурса.
	// Всегда будет возвращена ссылка на объект, хранящийся в единственном экземпляре.
	static ResourceManager& instance()
	{
		static ResourceManager ResourceManager;
		return ResourceManager;
	}
	// Загрузка одного меша из указанного obj-файла
	// Возвращаемое значение - индекс меша в менеджере ресурсов
	int loadMesh(std::string filename);
	// Получение меша по его индексу
	// Если такого меша нет (недействительный индекс) возвращается nullptr
	Mesh* getMesh(int index);

	int loadTexture(string);
	Texture* getTexture(int);

	int loadMaterial(string);
	Material* getMaterial(int);
private:
	// конструктор по умолчанию (объявлен приватным)
	// в результате нельзя создать ни одного объекта данного класса вне самого класса
	ResourceManager() {};
	// конструктора копирования нет (удален)
	ResourceManager(const ResourceManager& v) = delete;
	// оператора присваивания нет (удален)
	ResourceManager& operator=(const ResourceManager& v) = delete;
private:
	// вектор для хранения всех мешей
	vector<Mesh> meshes;
	// map для хранения соответствия между именем запрашиваемого файла
	// и индексом в контейнере meshes
	map <std::string, int> meshes_id;
	
	vector<Texture> textures;
	map<string, int> textures_id;

	vector<Material> materials;
	map<string, int> materials_id;
};