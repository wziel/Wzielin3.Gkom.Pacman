#pragma once

#include <windows.h>
#include "GL/gl.h"
#include "glut.h"
class Drawable
{
private:
	 GLfloat *_ambient;
	 GLfloat *_specular;
	 GLfloat *_diffuse;
	 GLfloat _shininess;
	 bool materialSet;

	 void removeMaterial();
public:
	Drawable();
	virtual ~Drawable();

	void setMaterial(GLfloat *ambient, GLfloat * specular, GLfloat* diffuse, GLfloat shininess);
	virtual void draw() const = 0;
};

