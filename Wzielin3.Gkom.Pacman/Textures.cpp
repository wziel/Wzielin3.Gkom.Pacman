
#include <stdio.h>
#include <string>
#include "Textures.h"
#include "soil/soil/src/SOIL.h"


GLuint Textures::_texWall = 0;
GLuint Textures::_texGround = 0;
GLuint Textures::_texFire[50];

void Textures::init()
{
	_texWall = Textures::LoadTexture("wall-texture.bmp");
	_texGround = Textures::LoadTexture("ground-texture.bmp");
	for (int i = 0; i < 50; ++i)
	{
		char num[3];
		itoa(i, num, 10);
		std::string filename = std::string("fire/") + std::string(num) + ".bmp";
		_texFire[i] = Textures::LoadTexture(filename.c_str());
	}
}


GLuint Textures::LoadTexture(const char* filename)
{
	GLuint tex_2d = SOIL_load_OGL_texture
		(
		filename,
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
		);

	return tex_2d;
}

GLuint Textures::getTexGround()
{
	return _texGround;
}

GLuint Textures::getTexWall()
{
	return _texWall;
}

GLuint Textures::getTexFire(int frame)
{
	return _texFire[frame];
}