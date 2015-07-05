#include <windows.h>
#include "GL/gl.h"
#include "glut.h"

#include "Ghost.h"


Ghost::Ghost()
{
	GLfloat red = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
	GLfloat green = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
	GLfloat blue = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);

	sphere = new Sphere(1, 20, 20);
	rosette = new Rosette(0.5, 0.5, 10, 6);

	Drawable::setMaterial(
		new GLfloat[4] {red, green, blue, 1},
		new GLfloat[4] {red, green, blue, 1},
		new GLfloat[4] {red, green, blue, 1},
		100
		);
}


Ghost::~Ghost()
{
}

void Ghost::draw() const
{
	static float frame_no = 0;
	static float frame_dif = 0.5;
	if (frame_no > 360) frame_no -= 360;
	frame_no += frame_dif;

	glPushMatrix();
		Drawable::draw();
		glTranslatef(0.5 + getX(), 0.5, -0.5 + getY());
		glPushMatrix();
			glRotatef(frame_no, 0, 1, 0);
			rosette->draw();
		glPopMatrix();
		glRotatef(180, 1, 0, 0);
		sphere->draw();
		glTranslatef(0, 5, 0);
	glPopMatrix();
}

void Ghost::update()
{
	//change direction if stopped or if random event occurs
	if (getSpeed() == 0 || rand()%10 < 1)
	{
		Direction newDir = Direction(rand() % 4);
		setRequestedDirection(newDir);
	}

	//call this function in basic form
	Creature::update();
}