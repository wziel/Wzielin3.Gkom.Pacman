#pragma once
#include <windows.h>
#include "GL/gl.h"
#include "glut.h"

class Textures
{
private:
	static GLuint _texWall;
	static GLuint _texGround;
	static GLuint _texFire[50];
	static GLuint LoadTexture(const char* filename);
public:
	static void init();
	static GLuint getTexWall();
	static GLuint getTexGround();
	static GLuint getTexFire(int frame);
};

