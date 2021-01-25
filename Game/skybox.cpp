
#include "skybox.h"

Skybox::Skybox(GLfloat _size, const string& _texturePath) : Entity("skybox")
{
	vector<string> textures;

	textures.push_back(_texturePath+"ft.jpg");
	textures.push_back(_texturePath+"dn.jpg");
	textures.push_back(_texturePath+"bk.jpg");
	textures.push_back(_texturePath+"up.jpg");
	textures.push_back(_texturePath+"lf.jpg");
	textures.push_back(_texturePath+"rt.jpg");

	Primitive* skybox = Primitive::createSkybox(_size, textures);

	attachComponent<MeshComponent>();

	getComponent<MeshComponent>()->primitives()->push_back(skybox);
}
