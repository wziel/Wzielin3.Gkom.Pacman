#pragma once
#include<vector>

#include <windows.h>
#include "GL/gl.h"
#include "glut.h"

#include "Drawable.h"


class Hemisphere :
	public Drawable
{
private:
	std::vector<GLfloat> vertices;
	std::vector<GLfloat> normals;
	std::vector<GLfloat> texcoords;
	std::vector<GLushort> indices;

public:
	~Hemisphere();

	Hemisphere(float radius, unsigned int rings, unsigned int sectors);

	virtual void draw() const;
};

