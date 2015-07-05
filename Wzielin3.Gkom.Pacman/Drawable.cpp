#include <windows.h>
#include "GL/gl.h"
#include "glut.h"

#include "Drawable.h"

Drawable::Drawable()
{
	materialSet = false;
}

Drawable::~Drawable()
{
	if (materialSet)
	{
		removeMaterial();
	}
}

void Drawable::removeMaterial()
{
	delete _ambient;
	delete _specular;
	delete _diffuse;
	materialSet = false;
}

void Drawable::setMaterial(GLfloat *ambient, GLfloat * specular, GLfloat* diffuse, GLfloat shininess)
{
	if (materialSet)
	{
		removeMaterial();
	}

	_ambient = ambient;
	_specular = specular;
	_diffuse = diffuse;
	_shininess = shininess;
	materialSet = true;
}

void Drawable::draw() const
{
	if (materialSet)
	{
		glMaterialfv(GL_FRONT, GL_AMBIENT, _ambient);
		glMaterialfv(GL_FRONT, GL_SPECULAR, _specular);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, _diffuse);
		glMaterialf(GL_FRONT, GL_SHININESS, _shininess);
	}
}