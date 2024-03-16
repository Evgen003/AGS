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

// ����� ��� ������ � ���������� �������� (���������� �� ������ ������� SINGLTON)
class ResourceManager
{
public:
	// ������-����� ��� ��������� ���������� ��������� �������.
	// ������ ����� ���������� ������ �� ������, ���������� � ������������ ����������.
	static ResourceManager& instance()
	{
		static ResourceManager ResourceManager;
		return ResourceManager;
	}
	// �������� ������ ���� �� ���������� obj-�����
	// ������������ �������� - ������ ���� � ��������� ��������
	int loadMesh(std::string filename);
	// ��������� ���� �� ��� �������
	// ���� ������ ���� ��� (���������������� ������) ������������ nullptr
	Mesh* getMesh(int index);

	int loadTexture(string);
	Texture* getTexture(int);

	int loadMaterial(string);
	Material* getMaterial(int);
private:
	// ����������� �� ��������� (�������� ���������)
	// � ���������� ������ ������� �� ������ ������� ������� ������ ��� ������ ������
	ResourceManager() {};
	// ������������ ����������� ��� (������)
	ResourceManager(const ResourceManager& v) = delete;
	// ��������� ������������ ��� (������)
	ResourceManager& operator=(const ResourceManager& v) = delete;
private:
	// ������ ��� �������� ���� �����
	vector<Mesh> meshes;
	// map ��� �������� ������������ ����� ������ �������������� �����
	// � �������� � ���������� meshes
	map <std::string, int> meshes_id;
	
	vector<Texture> textures;
	map<string, int> textures_id;

	vector<Material> materials;
	map<string, int> materials_id;
};