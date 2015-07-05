#include <windows.h>
#include "GL/gl.h"
#include "glut.h"

#include "PointBonus.h"


PointBonus::PointBonus() : Bonus(1)
{
	Drawable::setMaterial(
		new GLfloat[4] { 1, 1, 1, 1 },
		new GLfloat[4] { 1, 1, 1, 1 },
		new GLfloat[4] { 1, 1, 1, 1 },
		100
		);
}

PointBonus::~PointBonus()
{
}

void PointBonus::draw() const
{
	glPushMatrix();
		Bonus::draw();
		glutSolidSphere(0.1, 10, 10);
	glPopMatrix();
}