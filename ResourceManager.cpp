#include "ResourceManager.h"

int ResourceManager::loadMesh(string filename) {
	if (meshes_id.count(filename)) {
		return meshes_id[filename];
	}
	else {
		Mesh mesh;
		mesh.load(filename);
		meshes.push_back(mesh);
		meshes_id.insert(pair<string, int>(filename, meshes.size() - 1));
		return meshes_id[filename];
	}
}
Mesh* ResourceManager::getMesh(int index) {
	if (index >= meshes.size()) {
		return nullptr;
	}
	else {
		return &(meshes[index]);
	}
}

int ResourceManager::loadTexture(string filename) {
	if (textures_id.count(filename)) {
		return textures_id[filename];
	}
	else {
		Texture texture;
		texture.load(filename);
		textures.push_back(texture);
		textures_id.insert(pair<string, int>(filename, textures.size() - 1));
		return textures_id[filename];
	}
}

Texture* ResourceManager::getTexture(int index) {
	if (index >= textures.size()) {
		return nullptr;
	}
	else {
		return &(textures[index]);
	}
}