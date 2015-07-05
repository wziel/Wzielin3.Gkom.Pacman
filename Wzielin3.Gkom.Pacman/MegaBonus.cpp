#include <math.h>

#include <windows.h>
#include "GL/gl.h"
#include "glut.h"

#include "MegaBonus.h"


MegaBonus::MegaBonus(float radius) : Bonus(10),
_radius(radius)
{
	angle = 0;

	axis[0][0] = 1; axis[0][1] = 0; axis[0][2] = 0;
	axis[1][0] = 1; axis[1][1] = 0; axis[1][2] = 0;
	axis[2][0] = 0; axis[2][1] = 1; axis[2][2] = 0;
	axis[3][0] = 0; axis[3][1] = 1; axis[3][2] = 0;
	axis[4][0] = 0; axis[4][1] = 0; axis[4][2] = 1;
	axis[5][0] = 0; axis[5][1] = 0; axis[5][2] = 1;

	position[0][0] = 0;			position[0][1] = radius;	position[0][2] = 0;
	position[1][0] = 0;			position[1][1] = -radius;	position[1][2] = 0;
	position[2][0] = 0;			position[2][1] = 0;			position[2][2] = radius;
	position[3][0] = 0;			position[3][1] = 0;			position[3][2] = -radius;
	position[4][0] = radius;	position[4][1] = 0;			position[4][2] = 0;
	position[5][0] = -radius;	position[5][1] = 0;			position[5][2] = 0;

	Drawable::setMaterial(
		new GLfloat[4] { 1, 1, 1, 1 },
		new GLfloat[4] { 1, 1, 1, 1 },
		new GLfloat[4] { 1, 1, 1, 1 },
		100
		);
}


void MegaBonus::draw() const
{
	glPushMatrix();
		Bonus::draw();
		glTranslatef(0, _radius + 0.1, 0);
		glPushMatrix();
			glRotatef(angle, 1, 1, 1);
			glutSolidCube(_radius);
		glPopMatrix();
		for (int i = 0; i < _ballsCount; ++i)
		{
			glPushMatrix();
				glRotatef(angle, axis[i][0], axis[i][1], axis[i][2]);
				glTranslatef(position[i][0], position[i][1], position[i][2]);
				glutSolidSphere(0.05, 10, 10);
			glPopMatrix();
		}
	glPopMatrix();
}

void MegaBonus::update()
{
	Bonus::update();
	angle += 5;
}

MegaBonus::~MegaBonus()
{
}
