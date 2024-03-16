#include "RenderManager.h"

// инициализация объекта RenderManager, выполняется после инициализации OpenGL:
// загрузка шейдеров, установка неизменных параметров и прочая инициализация
void RenderManager::init() {
	// ИСПОЛЬЗУЕМЫЙ ШЕЙДЕР (ПОКА ТОЛЬКО ОДИН)
	Shader shader;
	// загрузка шейдера
	shader.load("SHADER\\Example.vsh", "SHADER\\Example.fsh");
	shaders.push_back(shader);
}
// Начало вывода очередного кадра (подготовка, очистка вектора графических объектов)
void RenderManager::start() {
	// очистка буфера кадра
	glClearColor(0.7, 0.7, 0.7, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	// включение теста глубины (на всякий случай)
	glEnable(GL_DEPTH_TEST);
	// вывод полигонов в виде линий с отсечением нелицевых граней
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	//glEnable(GL_CULL_FACE);
	//glCullFace(GL_BACK);

	// активация шейдера
	shaders[0].activate();
	// устанавливаем матрицу проекции
	mat4& projectionMatrix = camera->getProjectionMatrix();
	shaders[0].setUniform("projectionMatrix", projectionMatrix);

	//устанавливаем параметры света
	shaders[0].setUniform("lAmbient", light.getAmbient());
	shaders[0].setUniform("lDiffuse", light.getDiffuse());
	shaders[0].setUniform("lSpecular", light.getSpecular());
	shaders[0].setUniform("lPosition", light.getDirection());
	
	//очистка вектора объектов
	graphicObjects.clear();
}
// установка используемой камеры
void RenderManager::setCamera(Camera* camera) {
	this->camera = camera;
}
// добавление в очередь рендеринга очередного объекта для вывода
void RenderManager::addToRenderQueue(GraphicObject& graphicObject) {
	graphicObjects.push_back(graphicObject);
}
// завершение вывода кадра (основная работа)
void RenderManager::finish() {
	// получаем матрицу камеры
	mat4& viewMatrix = camera->getViewMatrix();
	for (auto& graphicObject : graphicObjects) {
		// устанавливаем матрицу наблюдения модели
		mat4 modelViewMatrix = viewMatrix * graphicObject.getModelMatrix();
		shaders[0].setUniform("modelViewMatrix", modelViewMatrix);

		int materialId = graphicObject.getMaterialId();
		Material* mater = ResourceManager::instance().getMaterial(materialId);
		if (mater != nullptr) {
			shaders[0].setUniform("mAmbient", mater->getAmbient());
			shaders[0].setUniform("mDiffuse", mater->getDiffuse());
			shaders[0].setUniform("mSpecular", mater->getSpecular());
			shaders[0].setUniform("mShininess", mater->getShininess());
		}

		// устанавливаем текстуру (привязываем к текстурному блоку)
		int textureId = graphicObject.getTextureId();
		Texture* texture = ResourceManager::instance().getTexture(textureId);
		if (texture != nullptr) {
			texture->bind(GL_TEXTURE0);
		}

		// uniform-переменная texture_0 связанна с нулевым текстурным блоком
		shaders[0].setUniform("texture_0", 0);

		//выводим меш
		int meshId = graphicObject.getMeshId();
		Mesh* mesh = ResourceManager::instance().getMesh(meshId);
		if (mesh != nullptr) {
			mesh->drawOne();
		}
		Texture::disableAll();
	}
}