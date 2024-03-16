#include "Material.h"

Material::Material() {

}

bool Material::loadFromJson(string filename) {
	fstream File(filename);
	if (!File) {
		cout << "Material file " << filename << " error\n";
		return false;
	}
	else {
		cout << "Material file " << filename << " open\n";
	}
	string line;
	getline(File, line, static_cast<char>(0));
	File.close();
	cout << line << endl;
	Document document;
	document.Parse(line.c_str());
	if (document.GetParseError() != 0) {
		cout << filename << " parse error\n";
		return false;
	}
	if (document.HasMember("ambient")) {
		auto array = document["ambient"].GetArray();
		for (int i = 0; i < 4; i++) {
			ambient[i] = array[i].GetFloat();
		}
	}
	if (document.HasMember("diffuse")) {
		auto array = document["diffuse"].GetArray();
		for (int i = 0; i < 4; i++) {
			diffuse[i] = array[i].GetFloat();
		}
	}
	if (document.HasMember("specular")) {
		auto array = document["specular"].GetArray();
		for (int i = 0; i < 4; i++) {
			specular[i] = array[i].GetFloat();
		}
	}
	if (document.HasMember("shineness")) {
		shininess = document["shininess"].GetFloat();
	}
}
vec4& Material::getAmbient() {
	return ambient;
}
vec4& Material::getDiffuse() {
	return diffuse;
}
vec4& Material::getSpecular() {
	return specular;
}
float Material::getShininess() {
	return shininess;
}